# Trash

Trash is a shell made for the Linux Operating System, for interacting with the file system. It is made in C, with only standard libraries used. It makes extensive use of linux system calls, and the signals library in C.
It has complete support for multiple file redirections, piping and setting environment variables. 

Common shell commands implemented  from scratch (including ls, fg, bg, jobs etc), and other user commands are forwarded to the system for execution.

Also allows to keep track of all proccess started by the shell using the command `jobs`, each of which can be stopped, sent to the background or brought back to the foreground using the commands `fg` and `bg`. All processes started by the shell can be killed at once using the command `overkill`.

Support for system processes is also implemented, and information about each process currently running/stopped by the system can be accessed using the `pinfo` command. It also provides information on the execution path, the exact process of the process and the virtual memory consumed by the process.

### Main Features!

  - Efficiently access files and directories, and information relating to them.
  - Self implemented commands also have limited flag support.
  - Helpful messages are displayed on incorrect command entries, and basic error handling is present.
  - Complete piping and file redirection support implemented.

### Extra Commands
+ remindme
Will issue a reminder specified in ***message*** after a time duration of ***time duration***.

    ```remindme [time duration] [message]```
+ clock
Will ping the user with the exact system time every ***interval*** seconds ***count*** times.

    ```clock -t [interval] -n [count]```

### File Structure
The entire shell is very modular, and each function is divided into separate files, each file with the name of the funtion. They are tied together by the user-defined header file "main.h". The file names themselves are very verbose.

> trash.c is the file containing main().


### Installation
Trash requires the GCC compiler to be installed. There are no dependencies.
Open your favorite Terminal and run these commands.

```sh
$ make
$ ./trash
```

### Todos

 - Implement --help for each command to be more verbose and helpful.

### Author
        Swaraj Renghe 
        IIIT Hyderabad

