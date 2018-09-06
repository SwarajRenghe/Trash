#include "main.h"

char* generateNewDirectoryPathFromRoot (char *rootDirectory, char *currentWorkingDirectory) {
	int i = 0, count = 0;
	char *newDirectoryFromRoot = malloc(LARGE * sizeof(char));
	if (strlen(currentWorkingDirectory) < strlen(rootDirectory)) {
		return currentWorkingDirectory;
	}
	while (rootDirectory[i] != '\0') {
		i++;
	}
	if (currentWorkingDirectory[i] == '\0') {
		return "~";
	}
	newDirectoryFromRoot[count] = '~';
	count++;
	while (currentWorkingDirectory[i] != '\0') {
		newDirectoryFromRoot[count] = currentWorkingDirectory[i];
		count++;
		i++;
	}
	return newDirectoryFromRoot;
}
