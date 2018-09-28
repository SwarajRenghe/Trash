#include "main.h"

int runSystemCommandInBackground (char **tokens) {
	int processID, status=0, wpid;

	if ((processID = fork()) < 0) {
		printf("TRAsh: Error forking a child process\n");
		return 1;
	}
	if (processID == 0) { // Child
		signal (SIGTSTP, SIG_IGN);
		signal (SIGINT, SIG_IGN);
		if (execvp(tokens[0], tokens) == 0) {
			return 1;
		}
		else {
			printf("TRAsh: Error executing system Command. Command might not exist.\n");
			return 1;
		}
	} 

	backgroundProcesses[numberOfBackgroundProcesses] = processID;
	backgroundProcessesState[numberOfBackgroundProcesses] = 'F';

	strcpy (backgroundProcessesCommand[numberOfBackgroundProcesses], tokens[0]);
	for (int i = 1; tokens[i] != NULL; ++i) {
		strcat (backgroundProcessesCommand[numberOfBackgroundProcesses], tokens[i]);
		strcat (backgroundProcessesCommand[numberOfBackgroundProcesses], " ");
	}

	numberOfBackgroundProcesses++;

	while ((wpid = wait(&status)) > 0);

	return 1;
}