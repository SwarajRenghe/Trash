#include "main.h"

char** parseCommandIntoSubCommands (char *command, char *delimiter) {
	char *copy = command;
	int count = 0;
	char *token;
	char *savedPointer1;
	char **commands = malloc (64 * sizeof(char*));

	if (!commands) {
		fprintf(stderr, "shell: Memory Allocation Error\n");
		exit (0);
	}

	while (token = strtok_r (copy, delimiter, &copy)) {
		commands[count] = token;
		count++;
	}

	commands[count] = NULL;
	return commands;
}