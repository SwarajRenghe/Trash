trash: trash.c shellLoop.c readCommand.c getCurrentDirectory.c parseCommandIntoSubCommands.c executeCommand.c getCurrentUserName.c getSystemName.c generateNewDirectoryPathFromRoot.c listNormalDirectories.c listAllDirectories.c listNormalDirectoriesL.c listNormalDirectoriesLA.c printNumber.c runSystemCommandInBackground.c runSystemCommandInForeground.c clockCommand.c
	gcc -o trash trash.c shellLoop.c readCommand.c getCurrentDirectory.c parseCommandIntoSubCommands.c executeCommand.c getCurrentUserName.c getSystemName.c generateNewDirectoryPathFromRoot.c listNormalDirectories.c listAllDirectories.c listNormalDirectoriesL.c listNormalDirectoriesLA.c printNumber.c runSystemCommandInBackground.c runSystemCommandInForeground.c clockCommand.c -I . 