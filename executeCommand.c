#include "main.h"

void CtrlZHandler (int sig) {
	for (int i = 0; i < numberOfBackgroundProcesses; ++i) {
		if (backgroundProcessesState[i] == 'F') {
			kill (backgroundProcesses[i], SIGSTOP);
			backgroundProcessesState[i] = 'S';
		}
	}
}

void CtlrCHandler (int sig) {
	for (int i = 0; i < numberOfBackgroundProcesses; ++i) {
		if (backgroundProcessesState[i] == 'F') {
			kill (backgroundProcesses[i], SIGKILL);
			backgroundProcessesState[i] == 'S';
		}
	}
}


int executeCommand (char **tokens) {
	signal (SIGTSTP, CtrlZHandler);
	signal (SIGINT, CtlrCHandler);
	if (tokens[0] == NULL) {
		return 1;
	}
	if (strcmp(tokens[0], "cd") == 0) {
		if (tokens[1] == NULL) {
			chdir (rootDirectory);
			return 1;
		}
		if (tokens[2] != NULL) {
			fprintf(stderr, "Usage:  cd [directoryPath]/\n");
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
			if (chdir(subTokens[i]) == 1) {
				return 1;
			}
			else {
				return 1;
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
		pinfo2 (tokens);
		return 1;		
	} 
	else if (strcmp(tokens[0], "exit") == 0) {
		return 0;		
	} 
	else if (strcmp(tokens[0], "quit") == 0) {
		return 0;		
	} 
	else if (strcmp(tokens[0], "jobs") == 0) {
		if (tokens[1] != NULL) {
			fprintf(stderr, "Usage: jobs\n");
			return 1;
		}
		if (numberOfBackgroundProcesses == 0) {
			fprintf(stderr, "No background processes running currently\n");
			return 1;
		}
		for (int i = 0; i < numberOfBackgroundProcesses; ++i) {
			printf("[%d]", i+1);
			// pinfo3 (backgroundProcesses[i]);
			if (backgroundProcessesState[i] == 'S') {
				printf(" Stopped\n");
			}
			else if (backgroundProcessesState[i] == 'R') {
				printf(" Running\n");
			}
			else {
				printf(" %c", backgroundProcessesState[i]);
			}
			printf(" %s", backgroundProcessesCommand[i]);
			printf(" [%d]\n", backgroundProcesses[i]);
		}
		return 1;
	}
	else if (strcmp(tokens[0], "setenv") == 0) {
		if (tokens[1] == NULL) {
			fprintf(stderr, "Usage: setenv var [value]\n");
			return 1;
		}
		if (tokens[3] != NULL) {
			fprintf(stderr, "Usage: setenv var [value]\n");
			return 1;
		}
		if (tokens[2] == NULL) {
			if (setenv(tokens[1], "", 1) != 0) {
				fprintf(stderr, "Trash: Could not set environment variable \n");
				return 1;
			}
			return 1;
		}
		else {
			if (setenv(tokens[1], tokens[2], 1) != 0) {
				fprintf(stderr, "Trash: Could not set environment variable \n");
				return 1;
			}
			return 1;
		}
	}
	else if (strcmp(tokens[0], "unsetenv") == 0) {
		if (tokens[1] == NULL) {
			fprintf(stderr, "Usage: unsetenv [var]\n");
			return 1;
		}
		if (tokens[2] != NULL) {
			fprintf(stderr, "Usage: unsetenv [var]\n");
			return 1;
		}
		unsetenv(tokens[1]);
		return 1;
	}
	else if (strcmp(tokens[0], "kjob") == 0) {
		if (tokens[1] == NULL) {
			fprintf(stderr, "Usage: kjob [jobNumber] [signalNumber]\n");
			return 1;
		}
		if (tokens[2] == NULL) {
			fprintf(stderr, "Usage: kjob [jobNumber] [signalNumber]\n");
			return 1;
		}
		if (tokens[3] != NULL) {
			fprintf(stderr, "Usage: kjob [jobNumber] [signalNumber]\n");
			return 1;
		}
		int jobNumber = atoi (tokens[1]-1);
		int signalNumber = atoi (tokens[2]);

		if (signalNumber == 9) {
			kill (backgroundProcesses[jobNumber], signalNumber);
			int positionToBeRemoved;
			int flagFound = 0;
			// for (int i = 0; i < numberOfBackgroundProcesses; ++i) {
			// 	if (jobNumber == backgroundProcesses[i]) {
			// 		flagFound = 1;
			// 		positionToBeRemoved = i;
			// 		break;
			// 	}
			// }
			if (jobNumber < numberOfBackgroundProcesses) {
				flagFound = 1;
			}
			if (flagFound == 0) {
				fprintf(stderr, "Did not find jobnumber %d\n", jobNumber);
				return 1;
			}

			for (int i = positionToBeRemoved; i < numberOfBackgroundProcesses-1; ++i) {
				backgroundProcesses[i] = backgroundProcesses[i+1];
				backgroundProcessesState[i] = backgroundProcessesState[i+1];
				strcpy (backgroundProcessesCommand[i], backgroundProcessesCommand[i+1]);
			}

			numberOfBackgroundProcesses--;
		}
		else {
			kill (backgroundProcesses[jobNumber], signalNumber);
		}
		return 1;
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
	else if (strcmp(tokens[0], "fg") == 0) {
		if (tokens[1] == NULL) {
			fprintf(stderr, "Usage: fb [jobNumber]\n");
			return 1;
		}
		int jobNumber = atoi (tokens[1]);
		printf("jobnumer->%d\n", jobNumber);
		if (jobNumber > 20) {
			fprintf(stderr, "Did not find jobnumber %d\n", jobNumber);
			return 1;
		}
		pid_t tempPid = backgroundProcesses[jobNumber];

		// kill (tempPid, SIGSTOP);
		// kill (tempPid, SIGCONT);

		int positionToBeRemoved;
		int flagFound = 0;
		// for (int i = 0; i < numberOfBackgroundProcesses; ++i) {
		// 	if (jobNumber == backgroundProcesses[i]) {
		// 		flagFound = 1;
		// 		positionToBeRemoved = i;
		// 		break;
		// 	}
		// }
		// if (flagFound == 0) {
		// 	fprintf(stderr, "Did not find jobnumber %d\n", jobNumber);
		// 	return 1;
		// }
		// for (int i = 0; i < numberOfBackgroundProcesses; ++i) {
		// 	if (backgroundProcessesState[i] == 'S' || backgroundProcessesState[i] == 'R') {

		// 	}
		// }
		printf("jopbunerer->%d\n", jobNumber);
		backgroundProcessesState[jobNumber-1] = 'F';
		kill (backgroundProcesses[jobNumber-1], SIGCONT);
		waitpid (backgroundProcesses[jobNumber-1], NULL, WUNTRACED);
		// numberOfBackgroundProcesses--;
		return 1;
	}
	else if (strcmp(tokens[0], "bg") == 0) {
		if (tokens[1] == NULL) {
			fprintf(stderr, "Usage: fb [jobNumber]\n");
			return 1;
		}
		int jobNumber = atoi (tokens[1]);
		if (jobNumber > 20) {
			fprintf(stderr, "Did not find jobnumber %d\n", jobNumber);
			return 1;
		}
		pid_t tempPid = backgroundProcesses[jobNumber];

		// kill (tempPid, SIGSTOP);
		// kill (tempPid, SIGCONT);

		int positionToBeRemoved;
		int flagFound = 0;
		// for (int i = 0; i < numberOfBackgroundProcesses; ++i) {
		// 	if (jobNumber == backgroundProcesses[i]) {
		// 		flagFound = 1;
		// 		positionToBeRemoved = i;
		// 		break;
		// 	}
		// }
		// if (flagFound == 0) {
		// 	fprintf(stderr, "Did not find jobnumber %d\n", jobNumber);
		// 	return 1;
		// }
		// for (int i = 0; i < numberOfBackgroundProcesses; ++i) {
		// 	if (backgroundProcessesState[i] == 'S' || backgroundProcessesState[i] == 'R') {

		// 	}
		// }
		backgroundProcessesState[jobNumber-1] = 'R';
		kill (backgroundProcesses[jobNumber-1], SIGCONT);

		// numberOfBackgroundProcesses--;
		return 1;
	}
	else if (strcmp(tokens[0], "overkill") == 0) {
		if (tokens[1] != NULL) {
			fprintf(stderr, "Usage: overkill\n");
			return 1;
		}
		for (int i = 0; i < numberOfBackgroundProcesses; ++i) {
			kill (backgroundProcesses[i], SIGKILL);
		}
		numberOfBackgroundProcesses = 0;
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