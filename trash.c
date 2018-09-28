#include "main.h" 
char *rootDirectory;
pid_t backgroundProcesses[1000];
int numberOfBackgroundProcesses = 0;
char backgroundProcessesCommand[100][100];
char backgroundProcessesState[100];

int main(int argc, char const *argv[]) {

	rootDirectory = getCurrentDirectory ();
	
	shellLoop ();
}