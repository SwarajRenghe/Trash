#include "main.h"

int runSystemCommandInForeground (char **tokens) {
	int processID, status;

	if ((processID = fork()) < 0) {
		printf("TRAsh: Error forking a child process\n");
		return 1;
	}
	if (processID == 0) { // Child
		if (execvp (tokens[0], tokens) == -1) {
			printf("TRAsh: Error executing system Command. Command might not exist.\n");
			return 1;
		}
		else {
			printf("TRAsh: Error executing system Command. Command might not exist.\n");
			return 1;
		}
	}
	return 1; 
}