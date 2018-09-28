#include "main.h"

void pinfo2 (char **tokens) {
	pid_t currentProcessPID;
	char processPath[LARGE], processInfo[LARGE], processExecutable[LARGE];
	int getPid = getpid ();

	if (tokens[2] != NULL) {
		fprintf(stderr, "Usage:  pinfo [optional: processNumber]/\n");
		return;
	}

	if (tokens[1] == NULL) {
		currentProcessPID = getpid ();
	}
	else {
		currentProcessPID = atoi (tokens[1]);
	}
	sprintf (processPath, "/proc/%d/status", currentProcessPID);
	int fileDescriptor = 0;
	fileDescriptor = open (processPath, O_RDONLY); 

	printf("pid -- %d\n", currentProcessPID);

	if (fileDescriptor < 0) {
		// printf("TRAsh: Could not detect process status\n");
		return;
	} 
	else {
		char processState[100];
		char processStateChar;
		read (fileDescriptor, processState, 50);
		close (fileDescriptor);


		for (int i = 0; i < 48; ++i) {
			if (processState[i] == 'S' && processState[i+1] == 't' && processState[i+2] == 'a') {
				processStateChar = processState[i+7];
				break;
			}
		}

		printf ("Process Status -- {%c}\n", processStateChar);
	}

	sprintf (processPath, "/proc/%d/statm", currentProcessPID);
	fileDescriptor = open (processPath, O_RDONLY);

	if (fileDescriptor < 0) {
		printf("TRAsh: Could not detect process virtual memory size\n");
		return;
	} 
	else {
		char count[5];
		read (fileDescriptor, count, 15);
		close (fileDescriptor);
		printf("- ");
		for (int i = 0; count[i] != ' ' && count[i] != '\0'; ++i) {
			printf("%c", count[i]);
		}
		printf(" {Virtual Memory}\n");
	}

	printf("- Executable Path -- ");

	sprintf (processPath, "/proc/%d/exe", currentProcessPID);
	int links = readlink (processPath, processInfo, LARGE - 1);

	if (links == -1) {
		printf("TRAsh: Could not detect process executable path\n");
		return;
	}
	else {
		processInfo [links] = '\0';
		char *newProcessInfo = malloc (LARGE * sizeof(char));
		newProcessInfo = generateNewDirectoryPathFromRoot (rootDirectory, processInfo);
		printf("%s\n", newProcessInfo);
	}
}