#include "main.h"

int runSystemCommandInBackground (char **tokens) {
	int processID, status=0, wpid;

	if ((processID = fork()) < 0) {
		printf("TRAsh: Error forking a child process\n");
		return 1;
	}
	if (processID == 0) { // Child
		if (execvp(tokens[0], tokens) == 0) {
			return 1;
		}
		else {
			printf("TRAsh: Error executing system Command. Command might not exist.\n");
			return 1;
		}
	} 
	while ((wpid = wait(&status)) > 0);

	return 1;
}