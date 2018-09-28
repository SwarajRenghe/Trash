#include "main.h"

int countPipes (char *subcommandsFromColon) {
	int count = 0;
	for (int i = 0; subcommandsFromColon[i] != '\0'; ++i) {
		if (subcommandsFromColon[i] == '|') {
			count++;
		}
	}
	return count;
}