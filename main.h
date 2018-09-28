#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <ctype.h>
#include <syscall.h>
#include <fcntl.h>

char* readCommand ();
char** parseCommandIntoSubCommands (char *command, char *delimiter);
char* getCurrentDirectory ();
void shellLoop ();
int executeCommand (char **tokens);
void getCurrentUserName (char *currentUserName, int length);
int getSystemName (char *systemName, int length);
char* generateNewDirectoryPathFromRoot (char *rootDirectory, char *currentWorkingDirectory);
int listNormalDirectories (char* directoryPath);
int listAllDirectories (char* directoryPath);
int listNormalDirectoriesL (char* directoryPath);
int listNormalDirectoriesLA (char* directoryPath);
int printNumber (int number, int size);
int runSystemCommandInBackground (char **tokens);
int runSystemCommandInForeground (char **tokens);
int clockCommand (char **tokens);
void pinfo2 (char **tokens);
void remindME (char message[], int duration);
int ExecutePipingWithoutRedirection (char *subcommandsFromColon);
int countPipes (char *subcommandsFromColon);
int checkForRedirection (char *subcommandsFromColon);
// int numberOfSpaceSeperatedCommands (char **subcommandsFromSpaces);
// int ExecutePipingWithRedirection (char *subcommandsFromColon, int numberOfCommands);
// int ExecutePipingWithRedirection2 (char *subcommandsFromColon);
void pinfo3 (pid_t processID);
int countPipes (char *subcommandsFromColon);
int onlyRedirect (char **tokens);
// int onlyRedirection (char *subcommandsFromColon);

#define MAX 1000000
#define LARGE 1000
#define LINELENGTH 300
#define HUNDRED 100
#define TOKENSIZE 75
extern char* rootDirectory;
extern char** systemCommands;
extern pid_t backgroundProcesses[1000];
extern char backgroundProcessesCommand[100][100];
extern char backgroundProcessesState[100];
extern int numberOfBackgroundProcesses;

#define DELIMITER1 ";"
#define DELIMITER2 " \t\n"
#define DELIMITER3 "|"

#define RED "\033[0;31m"
#define RESET "\033[0m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"

