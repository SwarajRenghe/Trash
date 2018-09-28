#include "main.h"

void pinfo3 (pid_t processID) {
	char processPath[LARGE], processInfo[LARGE], processExecutable[LARGE];

	sprintf (processPath, "/proc/%d/status", processID);
	int fileDescriptor = 0;
	fileDescriptor = open (processPath, O_RDONLY); 


	if (fileDescriptor < 0) {
		// printf("TRAsh: Could not detect process status\n");
		return;
	} 
	else {
		char processState[200];
		char processStateChar;
		char processStateString[100];
		read (fileDescriptor, processState, 100);
		close (fileDescriptor);
		int count = 0;

		for (int i = 0; i < 48; ++i) {
			if (processState[i] == 'S' && processState[i+1] == 't' && processState[i+2] == 'a') {
				processStateChar = processState[i+7];
				break;
			}
		}
	}

	printf("%d \n", processID);

}