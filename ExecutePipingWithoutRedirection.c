#include "main.h"


int ExecutePipingWithoutRedirection (char *subcommandsFromColon) {
	int numberOfPipes = countPipes (subcommandsFromColon);
	int numberOfCommands = numberOfPipes + 1;

	char **subcommandsFromPipe;
	subcommandsFromPipe = parseCommandIntoSubCommands (subcommandsFromColon, DELIMITER3);
	int pipeSubcommandCount = 0;

	int pipeFileDescriptors[2];

	int actualSTDIN = dup (0);
	int actualSTDOUT = dup (1);

	int success;

	int pipeIN = 0;
	int pipeOUT = 1;
	int test;
	int flagRedirect;


	for (int i = 0; i < numberOfCommands; ++i) {
		char **subcommandsFromSpaces = parseCommandIntoSubCommands (subcommandsFromPipe[i], DELIMITER2);

		flagRedirect = 0;
		test = dup2 (pipeIN, 0);
		// if (test == -1) {
		//     perror("TRAsh: Could not create pipe\n");
		//     return;
		// }
		test = pipe (pipeFileDescriptors);
		// if (test) {
		//     perror("TRAsh: Could not create pipe\n");
		//     return;
		// }
		close (pipeIN);

		dup2 (pipeFileDescriptors[1], 1);
		close (pipeFileDescriptors[1]);

		if (i == numberOfCommands-1) {
			test = dup2 (actualSTDOUT, 1); 
			// if (test == -1) {
			// 	perror("TRAsh: Could not create pipe\n");
			// 	return;
			// }
		}

		for (int j = 0; subcommandsFromSpaces[j] != NULL; ++j) {
			if (strcmp(subcommandsFromSpaces[j], ">") == 0 ||
				 strcmp(subcommandsFromSpaces[j], "<") == 0 || 
				  strcmp(subcommandsFromSpaces[j], ">>") == 0) {
				flagRedirect = 1;
				break;
			} 
		}

		if (flagRedirect == 0) {
			success = executeCommand (subcommandsFromSpaces);
		}
		else {
			success = onlyRedirect (subcommandsFromSpaces);
		}

		pipeIN = pipeFileDescriptors[0];
	}
	dup2 (actualSTDIN, 0);
	dup2 (actualSTDOUT, 1);
	close (actualSTDIN);
	close (actualSTDOUT);

	return success;
}