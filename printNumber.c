#include "main.h"

int printNumber (int number, int size) {
	int digits = 0;
	int copy = number;
	while (copy % 10 > 0) {
		digits++;
		copy /= 10;
	}
	printf("%d ", number);
	for (int i = 0; i < (size-digits); ++i) {
		printf(" ");
	}
}