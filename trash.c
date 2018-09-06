#include "main.h" 
char *rootDirectory;

int main(int argc, char const *argv[]) {

	rootDirectory = getCurrentDirectory ();
	
	shellLoop ();
}