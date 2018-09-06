#include "main.h"

int listAllDirectories (char* directoryPath) {
	DIR *directory;
	struct dirent *directoryElement;

	directory = opendir (directoryPath);

	if (directory != NULL) {
		while (directoryElement = readdir (directory)) {
			if (directoryElement->d_type == DT_DIR) {
				printf(GREEN "%s " RESET, directoryElement->d_name);
			}
			else {
				printf("%s ", directoryElement->d_name);
			}
		}
		printf("\n\n");
		closedir (directory);
	}
	else {
		printf("TRAsh: Could not open directory. Please check directory path.\n");
		return 0;
	}
	return 1;
} 