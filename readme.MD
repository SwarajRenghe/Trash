# Trash

Trash is a shell made for the Linux Operating System, for interacting with the file system. It is made in C.


### Main Features!

  - Efficiently access files and directories, and information relating to them
  - Common shell commands (echo, ls, pwd, cd) are present, with limited flag support

### File Structure
The entire shell is very modular, and each function is divided into separate files, each file with the name of the funtion. They are tied together by the user-defined header file "main.h". The file names themselves are very verbose.

`trash.c is the file containing main().`

makefile 
main.h
clockCommand.c                      
getCurrentUserName.c  
listNormalDirectories.c                          
runSystemCommandInBackground.c
executeCommand.c                    
getSystemName.c       
listNormalDirectoriesLA.c  
parseCommandIntoSubCommands.c  
runSystemCommandInForeground.c
generateNewDirectoryPathFromRoot.c  
listNormalDirectoriesL.c   
printNumber.c                 
shellLoop.c
getCurrentDirectory.c               
listAllDirectories.c                       
readCommand.c                  
trash.c



### Installation
Trash requires the GCC compiler to be installed. There are no dependencies.
Open your favorite Terminal and run these commands.

```sh
$ make
$ ./trash
```

### Todos

 - Implement --help for each command to be more verbose and helpful
 - Add piping and extra features

### Author
>Swaraj Renghe
>IIIT Hyderabad

