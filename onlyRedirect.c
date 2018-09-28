#include "main.h"

int onlyRedirect (char **tokens) {
	int inputFileDescriptor, outputFileDescriptor, doubleOutputFileDescriptor;
	int inputFlag = 0;
	int outputFlag = 0;
	int doubleOutputFlag = 0;

	int actualSTDIN = dup (0);
	int actualSTDOUT = dup (1);

	int success;
	
	int subcommandCount = 0;
	char inputFile[100];
	char outputFile[100];
	char DoubleOutputFile[100];

	while (tokens[subcommandCount] != NULL) {
		if (strcmp(tokens[subcommandCount], "<") == 0) {
			inputFlag = 1;
			strcpy (inputFile, tokens[subcommandCount+1]);
			strcpy (tokens[subcommandCount], " ");
			strcpy (tokens[subcommandCount+1], " ");
		}
		if (strcmp(tokens[subcommandCount], ">") == 0) {
			outputFlag = 1;
			strcpy (outputFile, tokens[subcommandCount+1]);
			strcpy (tokens[subcommandCount], " ");
			strcpy (tokens[subcommandCount+1], " ");
		}
		if (strcmp(tokens[subcommandCount], ">>") == 0) {
			doubleOutputFlag = 1;
			strcpy (DoubleOutputFile, tokens[subcommandCount+1]);
			strcpy (tokens[subcommandCount], " ");
			strcpy (tokens[subcommandCount+1], " ");
		}
		subcommandCount++;
	}

	char newCommand[10024];
	subcommandCount = 0;
	int count = 0;

	while (tokens[subcommandCount] != NULL) {
		strcat (newCommand, tokens[subcommandCount]);
		strcat (newCommand, " ");
		subcommandCount++;	
		count++;
	}

	if (inputFlag == 1) {
		inputFileDescriptor = open (inputFile, O_RDONLY, 0);
		if (inputFileDescriptor < 0) {
			fprintf(stderr, "TRAsh: Could not find file");
			return 1;
		}
		dup2 (inputFileDescriptor, 0);
		close (inputFileDescriptor);
	}

	if (outputFlag == 1) {
		outputFileDescriptor = open (outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0755);
		if (outputFileDescriptor < 0) {
			fprintf(stderr, "TRAsh: Could not create file");
			return 1;
		}
		dup2 (outputFileDescriptor, 1);
		close (outputFileDescriptor);
	}

	if (doubleOutputFlag == 1) {
		doubleOutputFileDescriptor = open (DoubleOutputFile, O_CREAT | O_APPEND | O_WRONLY , 0755);
		if (doubleOutputFileDescriptor < 0) {
			fprintf(stderr, "TRAsh: Could not find file");
			return 1;
		}
		dup2 (doubleOutputFileDescriptor, 1);
		close (doubleOutputFileDescriptor);
	}

	char **newCommands = parseCommandIntoSubCommands (newCommand, DELIMITER2);

	success = executeCommand (newCommands);

	// if (inputFileDescriptor = 1);

	dup2 (actualSTDOUT, 1);
	dup2 (actualSTDIN, 0);
	close (actualSTDOUT);
	close (actualSTDIN);

	return success;
}