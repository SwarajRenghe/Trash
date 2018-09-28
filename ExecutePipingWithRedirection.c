#include "main.h"

int countPipes (char *subcommandsFromColon) {
	int count = 0;
	for (int i = 0; subcommandsFromColon[i] != '\0'; ++i) {
		if (subcommandsFromColon[i]== '|') {
			count++;
		}
	}
	return count;
}

int numberOfSpaceSeperatedCommands (char **subcommandsFromSpaces) {
	int count = 0;
	for (int i = 0; subcommandsFromSpaces[i] != NULL; ++i) {
		count++;
	}
	return count;
}

int ExecutePipingWithRedirection (char *subcommandsFromColon, int numberOfCommands) {

	int flagInput = 0;
	int flagOutput = 0;
	int fileInput = 0;
	int fileOutput = 0;

	int pipeFileDescriptors[2];

	int actualSTDIN = dup (0);
	int actualSTDOUT = dup (1);

	int success;
	int pipeIN = 0;
	int pipeOUT = 1;
	int test;

	char **subcommandsFromPipe;
	char **new = malloc (1024 * sizeof(char*));
	subcommandsFromPipe = parseCommandIntoSubCommands (subcommandsFromColon, DELIMITER3);
	int pipeSubcommandCount = 0;


	for (int i = 0; i < numberOfCommands; ++i) {
		
		char **subcommandsFromSpaces = parseCommandIntoSubCommands (subcommandsFromPipe[i], DELIMITER2);
		int spaceNumberOfCommands = numberOfSpaceSeperatedCommands (subcommandsFromSpaces);

		test = dup2 (pipeIN, 0);

		test = pipe (pipeFileDescriptors);

		close (pipeIN);

		dup2 (pipeFileDescriptors[1], 1);
		close (pipeFileDescriptors[1]);

		if (i == numberOfCommands-1) {
			test = dup2 (actualSTDOUT, 1); 
		}

		if (checkForRedirection(subcommandsFromPipe[i])) {

			for (int i = 0; subcommandsFromSpaces[i] != NULL; ++i) {
				if (!strcmp(subcommandsFromSpaces[i], ">")) {
					flagOutput = 1;
					if (i >= spaceNumberOfCommands) {
						perror("TRAsh: Output file not defined. Usage: [command with output] > [filename]");
						return 1;
					}
					else {
						fileOutput = open (subcommandsFromSpaces[i+1], O_WRONLY | O_CREAT, 0755);
						if (fileOutput == -1) {
							perror("TRAsh: Could not create file");
							return 1;
						}
					}
				}
				if (!strcmp(subcommandsFromSpaces[i], "<")) {
					flagInput = 1;
					if (i >= spaceNumberOfCommands) {
						perror("TRAsh: Input file not defined. Usage: [filename] > [command with output]");
						return 1;
					}
					else {
						fileInput = open (subcommandsFromSpaces[i+1], O_WRONLY, 0755);
						if (fileInput == -1) {
							perror("TRAsh: Could not find file");
							return 1;
						}
					}
				}
				if (!strcmp(subcommandsFromSpaces[i], ">>")) {
					flagOutput = 1;
					if (i >= spaceNumberOfCommands) {
						perror("TRAsh: Output file not defined. Usage: [filename] > [command with output]");
						return 1;
					}
					else {
						fileInput = open (subcommandsFromSpaces[i+1], O_WRONLY | O_APPEND | O_CREAT, 0755);
						if (fileInput == -1) {
							perror("TRAsh: Could not create file");
							return 1;
						}
					}
				}
			}

			if (flagOutput) {
				actualSTDOUT = dup (1);
				dup2 (fileOutput, 1);
			}
			if (flagInput) {
				actualSTDIN = dup (0);
				dup2 (fileInput, 0);
			}

			success = executeCommand (subcommandsFromSpaces);

			if (flagInput) {
				dup2 (actualSTDIN, 0);
			}
			if (flagOutput) {
				dup2 (actualSTDOUT, 1);
			}
		}
		else {
			success = executeCommand (subcommandsFromSpaces);
		}

	}
}
