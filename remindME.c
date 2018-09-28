#include "main.h"

void remindME (char message[], int duration) {
	int processID, status=0, wpid;
	
	if ((processID = fork()) < 0) {
		printf("TRAsh: Error forking a child process\n");
		return;
	}
	if (processID == 0) { // Child
		sleep (duration);
		printf("Reminder: %s\n", message);
	}
}