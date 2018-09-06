#include "main.h"

int getSystemName (char *systemName, int length) {
	return gethostname (systemName, length);
}