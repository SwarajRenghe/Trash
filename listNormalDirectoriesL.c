#include "main.h"

int listNormalDirectoriesL (char* directoryPath) {
	DIR *directory;
	int filePathLength = 0;
	struct dirent *directoryElement;
	long long int a = 0;

	directory = opendir (directoryPath);

	if (directory != NULL) {
		while (directoryElement = readdir (directory)) {
			char* filePath = malloc (LARGE * sizeof(char));
			filePath[0] = '.';
			filePath[1] = '/';
			for (filePathLength = 2; directoryPath[filePathLength-2] != '\0'; ++filePathLength) {
				filePath[filePathLength] = directoryPath[filePathLength-2];
			}
			int count = 0;
			while (directoryElement->d_name[count] != '\0') {
				filePath[filePathLength] = directoryElement->d_name[count];
				count++;
				filePathLength++;
			}

			if (directoryElement->d_name[0] == '.') {
				continue;
			}
			else {
				struct stat *fileData = malloc(1 * sizeof(struct stat));
				struct passwd *ownerData = getpwuid (fileData->st_uid);
				struct group *groupData = getgrgid (fileData->st_gid);
				
				stat (filePath, fileData);
				char timeString[200];

				directoryElement->d_type == DT_DIR ? printf("d") : printf("-");
				fileData->st_mode & S_IRUSR ? printf("r") : printf("-");
				fileData->st_mode & S_IWUSR ? printf("w") : printf("-");
				fileData->st_mode & S_IXUSR ? printf("x") : printf("-");
				printf("-");
				fileData->st_mode & S_IRGRP ? printf("r") : printf("-");
				fileData->st_mode & S_IWGRP ? printf("w") : printf("-");
				fileData->st_mode & S_IXGRP ? printf("x") : printf("-");
				printf("-");
				fileData->st_mode & S_IROTH ? printf("r") : printf("-");
				fileData->st_mode & S_IWOTH ? printf("w") : printf("-");
				fileData->st_mode & S_IXOTH ? printf("x") : printf("-");
				printf(" ");

				printf("%ld ", fileData->st_nlink);
					
				printf("%s ", ownerData->pw_name);
				printf("%s ", groupData->gr_name);	

				printNumber (fileData->st_size, 10);
				// timespec_get(&timeOfLastModification, a);
				strftime (timeString, sizeof(timeString), "%b %d %R", localtime(&(fileData->st_ctim.tv_sec)));
				// printf("%ld ", timeOfLastModification.tv_sec);
				// printf("%lld ", a);
				printf("%s ", timeString);

				if (directoryElement->d_type == DT_DIR) {
					printf(GREEN "\t%s\n" RESET, directoryElement->d_name);
				}
				else {
					printf("\t%s\n", directoryElement->d_name);
				}
				filePath = NULL;
				free (filePath);
			}
		}
		closedir (directory);
	}
	else {
		printf("TRAsh: Could not open directory. Please check directory path.\n");
		return 0;
	}
	return 1;
} 