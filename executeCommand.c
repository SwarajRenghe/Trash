#include "main.h"

void pinfo2 (char **tokens) {
	pid_t currentProcessPID;
	char processPath[LARGE], processInfo[LARGE], processExecutable[LARGE];
	int getPid = getpid ();

	if (tokens[1] == NULL) {
		currentProcessPID = getpid ();
	}
	else {
		currentProcessPID = atoi (tokens[1]);
	}
	sprintf (processPath, "/proc/%d/status", currentProcessPID);
	int fileDescriptor = 0;
	fileDescriptor = open (processPath, O_RDONLY); 
	// printf("%s\n", processPath);

	printf("pid -- %d\n", currentProcessPID);

	if (fileDescriptor < 0) {
		printf("TRAsh: Could not detect process status\n");
		return;
	} 
	else {
		char processState[100];
		char processStateChar;
		read (fileDescriptor, processState, 50);
		close (fileDescriptor);


		for (int i = 0; i < 48; ++i) {
			if (processState[i] == 'S' && processState[i+1] == 't' && processState[i+2] == 'a') {
				processStateChar = processState[i+7];
				break;
			}
		}

		printf ("Process Status -- {%c}\n", processStateChar);
	}

	sprintf (processPath, "/proc/%d/statm", currentProcessPID);
	fileDescriptor = open (processPath, O_RDONLY);

	if (fileDescriptor < 0) {
		printf("TRAsh: Could not detect process virtual memory size\n");
		return;
	} 
	else {
		char count[5];
		read (fileDescriptor, count, 15);
		close (fileDescriptor);
		printf("- ");
		for (int i = 0; count[i] != ' ' && count[i] != '\0'; ++i) {
			printf("%c", count[i]);
		}
		printf(" {Virtual Memory}\n");
	}

	printf("- Executable Path -- ");

	sprintf (processPath, "/proc/%d/exe", currentProcessPID);
	int links = readlink (processPath, processInfo, LARGE - 1);

	if (links == -1) {
		printf("TRAsh: Could not detect process executable path\n");
		return;
	}
	else {
		processInfo [links] = '\0';
		char *newProcessInfo = malloc (LARGE * sizeof(char));
		newProcessInfo = generateNewDirectoryPathFromRoot (rootDirectory, processInfo);
		printf("%s\n", newProcessInfo);
	}
}

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

int executeCommand (char **tokens) {
	if (tokens[0] == NULL) {
		return 1;
	}
	else if (strcmp(tokens[0], "cd") == 0) {
		if (tokens[1] == NULL) {
			chdir (rootDirectory);
			return 1;
		}
		if (tokens[2] != NULL) {
			printf("Usage:  cd [directoryPath]\n");
			return 1;
		}
		char **subTokens;
		int len = strlen (tokens[1]);
		tokens[1][len-1] = '\0';

		subTokens = parseCommandIntoSubCommands (tokens[1], "/");
		for (int i = 0; subTokens[i] != NULL; ++i) {
			if (subTokens[i] == "\n") {
				return 1;
			}
			if (chdir(subTokens[i]) == 0) {
				return 1;
			}
			else {
				printf("Usage: cd [directoryPath]/ \n");
			}
		}
		return 1;
	}
	else if (strcmp(tokens[0], "pwd") == 0) {
		// printf("Usage: pwd \n\n");
		char *systemCurrentWorkingDirectory = getCurrentDirectory ();
		char* shellCurrentWorkingDirectory =  generateNewDirectoryPathFromRoot (rootDirectory, systemCurrentWorkingDirectory);
		printf("Shell Current Working Directory - %s\n", shellCurrentWorkingDirectory);
		printf("System Current Working Directory - %s\n\n", systemCurrentWorkingDirectory);
		return 1;
	} 
	else if (strcmp(tokens[0], "ls") == 0) {
		if (tokens[1] == NULL) {
			listNormalDirectories ("./");
		}
		int numberOfDirectoryCommands = 0;
		int flagA = 0, flagL = 0, flagAL = 0;
		char *directoryPath = malloc (LARGE * sizeof(char));
		directoryPath = NULL; 
		for (int i = 1; tokens[i] != NULL; ++i) {
			if (tokens[i][0] == '-') {
				for (int j = 1; tokens[i][j] != '\0'; ++j) {
					if (tokens[i][j] == 'a') {
						flagA = 1;
					}
					if (tokens[i][j] == 'l') {
						flagL = 1;
					}
				}	
			}
			else {
				numberOfDirectoryCommands++;
				if (numberOfDirectoryCommands > 1) {
					printf("Usage: ls -[flags] ./[directoryPath]. Only one directoryPath field.\n");
				}
				directoryPath = tokens[i];
				int stringLength = strlen (directoryPath);
				if (directoryPath[stringLength-1] == '\n') {
					directoryPath[stringLength-1] = '\0';
				}
			}
		}

		if (flagA == 1 && flagL == 1) {
			flagAL = 1;
		}

		// printf("flagA = %d flagL = %d flagAL = %d directoryPath = %s\n", flagA, flagL, flagAL, directoryPath);

		if (flagAL == 0 && flagA == 1) {
			if (directoryPath == NULL) {
				listAllDirectories ("./");
			}
			else {
				if (listAllDirectories (directoryPath) == 0) {
					printf("Usage: ls -[flags] ./[directoryPath]. Only one directoryPath field.\n");
				}
			}
		}
		else if (flagAL == 0 && flagL == 1) {
			if (directoryPath == NULL) {
				listNormalDirectoriesL ("./");
			}
			else {
				if (listNormalDirectoriesL (directoryPath) == 0) {
					printf("Usage: ls -[flags] ./[directoryPath]. Only one directoryPath field.\n");
				}
			}
		}
		else if (flagAL == 1) {
			if (directoryPath == NULL) {
				listNormalDirectoriesLA ("./");
			}
			else {
				if (listNormalDirectoriesLA (directoryPath) == 0) {
					printf("Usage: ls -[flags] ./[directoryPath]. Only one directoryPath field.\n");
				}
			}
		}

		return 1;
 	}
	else if (strcmp(tokens[0], "echo") == 0) {
		for (int i = 1; tokens[i] != NULL; ++i) {
			printf("%s ", tokens[i]);
		}
		printf("\n");
		return 1;
	} 
	else if (strcmp(tokens[0], "clock") == 0) {
		clockCommand (tokens);
	}
	else if (strcmp(tokens[0], "pinfo") == 0) {
		// pinfo ();
		pinfo2 (tokens);
		return 1;		
	} 
	else if (strcmp(tokens[0], "exit") == 0) {
		return 0;		
	} 
	else if (strcmp(tokens[0], "remindme") == 0) {
		char message[LARGE];
		if (tokens[1] == NULL) {
			printf("Usage: remindme [time duration] [message]\n");
			return 1;
		}
		if (tokens[2] == NULL) {
			printf("Usage: remindme [time duration] [message]\n");
			return 1;
		}
		int duration = atoi (tokens[1]);
		strcpy (message, tokens[2]);
		for (int i = 3; tokens[i] != NULL; ++i) {
			strcat (message, " ");
			strcat (message, tokens[i]);
		}
		remindME (message, duration);
		return 1;
	} 
	else {
		int count, isBackGroundProcess = 0, track = 0;
		for (int i = 0; tokens[i] != NULL; ++i) {
			count = 0;
			while (tokens[i][count] != '\0') {
				if (tokens[i][count] == '&') {
					isBackGroundProcess = 1;
				}
				count++;
			}
			track++;
		}
		if (isBackGroundProcess == 0) {
			runSystemCommandInBackground (tokens);
		}
		else {
			tokens[track-1] = NULL;
			runSystemCommandInForeground (tokens);
		}

		return 1;
	}
}