#include "main.h"

void shellLoop () {
	char *command, *currentWorkingDirectory;
	char *newDirectoryFromRoot;
	char *currentUser = malloc (LARGE * sizeof(char));
	char *systemName = malloc (LARGE * sizeof(char));
	char **subcommands, **tokens;
	int success = 1, subcommandCount, tokenCount;

	do {
		subcommandCount = 0;
		currentWorkingDirectory = getCurrentDirectory ();
		getCurrentUserName (currentUser, LINELENGTH);
		getSystemName (systemName, LINELENGTH);
		newDirectoryFromRoot = generateNewDirectoryPathFromRoot (rootDirectory, currentWorkingDirectory);
		printf(CYAN "<%s@%s: " RESET, currentUser, systemName);
		printf(YELLOW "%s>\n" RESET, newDirectoryFromRoot);
		printf(RED "TRAsh > " RESET);
		command = readCommand ();
		subcommands = parseCommandIntoSubCommands (command, DELIMITER1);
		while (subcommands[subcommandCount] != NULL && success == 1) {
			tokenCount = 0;
			tokens = parseCommandIntoSubCommands (subcommands[subcommandCount], DELIMITER2);
			success = executeCommand (tokens);
			subcommandCount++;
			free (tokens);
		}


		// free (currentUser);
		// free (systemName);
		// free (subcommands);
		// free (command);

	} while (success);
}
