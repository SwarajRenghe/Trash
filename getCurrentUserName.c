#include "main.h"

void getCurrentUserName (char *currentUserName, int length) {
	getlogin_r (currentUserName, length);
}