//
// Created by Yifei Ma on 2020-10-01.
//

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#include <signal.h>

#include <sys/resource.h>
#include <errno.h>
#include <fcntl.h>

#define LINE_LENGTH 100 // Max # of characters in an input line
#define MAX_ARGS 7+1 // Max number of arguments to a command
#define MAX_LENGTH 20 // Max # of characters in an argument
#define MAX_PT_ENTRIES 32 // Max entries in the Process Table


struct process {
    pid_t pid;
    char command[LINE_LENGTH];
    char status;
};

#endif //MAIN_H
