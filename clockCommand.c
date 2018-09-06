#include "main.h"

int returnNumber (char asciiCharacter) {
	switch (asciiCharacter) {
		case 48 : return 0;
		case 49 : return 1;
		case 50 : return 2;
		case 51 : return 3;
		case 52 : return 4;
		case 53 : return 5;
		case 54 : return 6;
		case 55 : return 7;
		case 56 : return 8;
		case 57 : return 9;
	}
}

void printTime () {
	char fileName[] = "/proc/driver/rtc";
	char output[50];
	int length = 50, timeCount = 0, dateCount = 0;
	int fileDescriptor = 0;
	char *time = malloc (TOKENSIZE * sizeof(char));
	fileDescriptor = open (fileName, O_RDONLY); 

	if (fileDescriptor < 0) {
		printf("TRAsh: Could not open RTC file\n");
		return;
	}

	read (fileDescriptor, output, length);

	for (int i = 11; i <= 18; ++i) {
		time[timeCount] = output[i];
		timeCount++;
	}
	for (int i = 31; i <= 40; ++i) {
		printf("%c", output[i]);
	}
	printf(", ");
	printf("%s\n", time);

	close (fileDescriptor);
	free (time);
}

int clockCommand (char **tokens) {
	int a, b;
	if (tokens[1] == NULL) {
		printTime ();
	}
	else {
		if (tokens[2] == NULL || tokens[3] == NULL || tokens[4] == NULL) {
			printf("Usage: clock -t [interval] -n [count] \n");
			return 1;
		}
		if (strcmp(tokens[1], "-t") != 0) {
			printf("Usage: clock -t [interval] -n [count] \n");
			return 1;
		}

		if (isdigit(tokens[2][0]) == 0) {
			printf("Usage: clock -t [interval] -n [count] \n");
			return 1;
		}
		if (strcmp(tokens[3], "-n") != 0) {
			printf("Usage: clock -t [interval] -n [count] \n");
			return 1;
		}
		if (tokens[4] == NULL) {
			printf("Usage: clock -t [interval] -n [count] \n");
			return 1;
		}
		if (isdigit(tokens[4][0]) == 0) {
			printf("Usage: clock -t [interval] -n [count] \n");
			return 1;
		}

		a = atoi (tokens[2]);
		b = atoi (tokens[4]);

		while (b > 0) {
			printTime ();
			sleep (a);
			b -= a;
		}
	}
	return 1;
}