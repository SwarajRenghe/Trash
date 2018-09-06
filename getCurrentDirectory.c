#include "main.h"

char* getCurrentDirectory () {
	char *currentWorkingDirectory = malloc (LARGE * sizeof(char));
	getcwd (currentWorkingDirectory, LARGE);
	return currentWorkingDirectory;
}
