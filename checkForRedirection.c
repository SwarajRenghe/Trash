#include "main.h"

int checkForRedirection (char *subcommandsFromColon) {
	if (subcommandsFromColon == NULL) {
		printf("false\n");
		return 0;
	}

	char **subcommandsFromSpaces = parseCommandIntoSubCommands (subcommandsFromColon, DELIMITER2);
	for (int i = 0; subcommandsFromSpaces[i] != NULL; ++i) {
		if (!strcmp(subcommandsFromSpaces[i], ">") || !strcmp(subcommandsFromSpaces[i], "<") || !strcmp(subcommandsFromSpaces[i], ">>")) {
			printf("found %s\n", subcommandsFromSpaces[i]);
			return 1;
		}
	}
	
	return 0;
}