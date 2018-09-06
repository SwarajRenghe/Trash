#include "main.h"

char* readCommand () {
	char *command = NULL;
	ssize_t size = 0;
	getline (&command, &size, stdin);
	return command;
}
