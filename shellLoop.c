#include "main.h"

void ChildEndedHandler (int sig) {
	for (int i = 0; i < numberOfBackgroundProcesses; ++i) {
		int flag = 0;
		if (waitpid(backgroundProcesses[i], NULL, WNOHANG) != 0) {
			printf("Background process %s with pid %d exited normally\n", backgroundProcessesCommand[i], backgroundProcesses[i]);
			int positionToBeRemoved;
			int flagFound = 0;

			for (int j = positionToBeRemoved; j < numberOfBackgroundProcesses-1; ++j) {
				backgroundProcesses[i] = backgroundProcesses[i+1];
				backgroundProcessesState[i] = backgroundProcessesState[i+1];
				strcpy (backgroundProcessesCommand[i], backgroundProcessesCommand[i+1]);
			}

			numberOfBackgroundProcesses--;
		}
	}
}

void shellLoop () {
	char *command, *currentWorkingDirectory;
	char *newDirectoryFromRoot;
	char *currentUser = malloc (LARGE * sizeof(char));
	char *systemName = malloc (LARGE * sizeof(char));
	char **subcommandsFromColon, **subcommandsFromPipe, **subcommandsFromSpaces;
	int success = 1, colonSubcommandCount, pipeSubcommandCount, spacesSubcommandCount, tokenCount, count, pidCount = 0;

	signal (SIGTSTP, SIG_IGN);
	signal (SIGINT, SIG_IGN);
	signal (SIGCHLD, ChildEndedHandler);

	do {

		colonSubcommandCount = 0;
		currentWorkingDirectory = getCurrentDirectory ();
		getCurrentUserName (currentUser, LINELENGTH);
		getSystemName (systemName, LINELENGTH);
		newDirectoryFromRoot = generateNewDirectoryPathFromRoot (rootDirectory, currentWorkingDirectory);
		printf(CYAN "<%s@%s: " RESET, currentUser, systemName);
		printf(YELLOW "%s>\n" RESET, newDirectoryFromRoot);
		printf(RED "TRAsh > " RESET);
		command = readCommand ();
		subcommandsFromColon = parseCommandIntoSubCommands (command, DELIMITER1);

		while (subcommandsFromColon[colonSubcommandCount] != NULL) {
			int numberOfPipes = countPipes (subcommandsFromColon[colonSubcommandCount]);
			int numberOfCommands = numberOfPipes + 1;
			int inputWithoutRedirection = 0;

			// success = executeCommand (subcommandsFromSpaces);


			// onlyRedirection (subcommandsFromColon[colonSubcommandCount]);

			for (int i = 0; subcommandsFromColon[colonSubcommandCount][i] != '\0'; ++i) {
				if (subcommandsFromColon[colonSubcommandCount][i] == '>' || subcommandsFromColon[colonSubcommandCount][i] == '<') {
					inputWithoutRedirection = 1;
					break;
				}
			}

			if (inputWithoutRedirection == 0) {
				if (numberOfPipes == 0) {
					subcommandsFromSpaces = parseCommandIntoSubCommands (subcommandsFromColon[colonSubcommandCount], DELIMITER2);
					success = executeCommand (subcommandsFromSpaces);
				}
				else {
					success = ExecutePipingWithoutRedirection (subcommandsFromColon[colonSubcommandCount]);
				}
			}
			else {
				if (numberOfPipes != 0) {
					printf("one of thoseeeee\n");
					success = ExecutePipingWithoutRedirection (subcommandsFromColon[colonSubcommandCount]);
				}
				else {
					subcommandsFromSpaces = parseCommandIntoSubCommands (subcommandsFromColon[colonSubcommandCount], DELIMITER2);
					onlyRedirect (subcommandsFromSpaces);
				}
			}	
			colonSubcommandCount++;
		}

	} while (success);
}
