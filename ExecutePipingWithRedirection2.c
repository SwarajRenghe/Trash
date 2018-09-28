#include "main.h"

int numberOfSpaceSeperatedCommands (char **subcommandsFromSpaces) {
	int count = 0;
	for (int i = 0; subcommandsFromSpaces[i] != NULL; ++i) {
		count++;
	}
	return count;
}

int Redirection2 (char *subcommandsFromColon) {
	int numberOfPipes = countPipes (subcommandsFromColon);
	int numberOfCommands = numberOfPipes + 1;

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

	char **subcommandsFromSpace = parseCommandIntoSubCommands (subcommandsFromColon, DELIMITER3);
	int numberOfSpaceSeperatedCommands = numberOfSpaceSeperatedCommands (subcommandsFromSpace);

	char **newSubCommands
	
	int spaceSubcommandCount = 0;

	while (subcommandsFromSpace[spaceSubcommandCount] != NULL) {

		if (spaceSubcommandCount == 0) {
			
		}


		// if (strcmp(subcommandsFromSpace[spaceSubcommandCount], "<") == 0) {
		// 	flagOutput = 1;
		// 	if (spaceSubcommandCount < numberOfSpaceSeperatedCommands-1) {
		// 		int fileInput = open (subcommandsFromSpace[spaceSubcommandCount+1], O_WRONLY, 0755);
		// 		if (fileInput == -1) {
		// 			fprintf(stderr, "TRAsh: Could not find file\n");
		// 			return 1;
		// 		}
		// 	}
		// 	else {
		// 		fprintf(stderr, "TRAsh: Input file not defined. Usage: [command] < [filename]\n");
		// 		return 1;
		// 	}
		// }
		// if (strcmp(subcommandsFromSpace[spaceSubcommandCount], ">") == 0) {
		// 	flagInput = 1;
		// 	if (spaceSubcommandCount <  numberOfSpaceSeperatedCommands-1){
		// 		int fileOutput = open (subcommandsFromSpace[spaceSubcommandCount+1], O_WRONLY | O_CREAT, 0755);
		// 		if (fileOutput == -1) {
		// 			fprintf(stderr, "TRAsh: Could not find file\n");
		// 			return 1;
		// 		}
		// 	}
		// 	else {
		// 		perror("TRAsh: Output file not defined. Usage: [command with output] > [filename]");
		// 		return 1;
		// 	}
		// }
		// if (strcmp(subcommandsFromSpace[spaceSubcommandCount], ">>") == 0) {
		// 	if (spaceSubcommandCount <  numberOfSpaceSeperatedCommands-1){
		// 		int fileOutput = open (subcommandsFromSpace[spaceSubcommandCount+1], O_WRONLY | O_APPEND | O_CREAT, 0755);
		// 		if (fileOutput == -1) {
		// 			fprintf(stderr, "TRAsh: Could not find file\n");
		// 			return 1;
		// 		}
		// 	}
		// 	else {
		// 		perror("TRAsh: Output file not defined. Usage: [command with output] >> [filename]");
		// 		return 1;
		// 	}
		// }




		spaceSubcommandCount++;
	}

}