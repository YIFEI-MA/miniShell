//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <sys/wait.h>
//#include <string.h>
//
//#include <signal.h>
//
//#include <sys/resource.h>
//#include <errno.h>
//#include <fcntl.h>

#include "main.h"
#include "helperFunction.h"


//#define LINE_LENGTH 100 // Max # of characters in an input line
//#define MAX_ARGS 7+1 // Max number of arguments to a command
//#define MAX_LENGTH 20 // Max # of characters in an argument
//#define MAX_PT_ENTRIES 32 // Max entries in the Process Table
//
//
//struct process {
//    pid_t pid;
//    char command[LINE_LENGTH];
//    char status;
//};

struct process pcb[MAX_PT_ENTRIES];
int process_count = 0;

//int get_cpu_time(pid_t pid) {
//    FILE *fp = popen("ps -A", "r");
//    char line[1000];
//
//    while (fgets(line, sizeof(line), fp) != NULL) {
//        int i = 0;
//        char *tokens[100];
//        char *token = strtok(line, " ");
//        while (token != NULL) {
//            tokens[i] = token;
//            i++;
//            token = strtok(NULL, " ");
//        }
//        char *endptr;
//        int current_pid = (int) strtol(tokens[0], &endptr, 10);
//        if (*endptr == '\0' && current_pid == pid) {
//            int h, m, s;
//            int cpu_time;
//            sscanf(tokens[2], "%02d:%02d:%02d", &h, &m, &s);
//            cpu_time = h * 3600 + m * 60 + s;
//            pclose(fp);
//            return cpu_time;
//        }
//        memset(line, '\0', sizeof(*line));
//    }
//    pclose(fp);
//    return -1;
//
//}


//int delete_process(pid_t pid) {
//    int p_index = -1;
//    for (int i = 0; i < process_count; i++) {
//        if (pcb[i].pid == pid) {
//            p_index = i;
//            break;
//        }
//    }
//    if (p_index == -1) {
//        printf("Invalid index when deleting process!\n");
//        return -1;
//    }
//
//    for (int i = p_index; i < process_count; i++) {
//        pcb[i] = pcb[i + 1];
//    }
//
//    return 1;
//}

int update_process_count() {
    if (process_count == 0) {
        return process_count;
    }

    int status;
    for (int i = 0; i < process_count; i++) {
        status = kill(pcb[i].pid, 0);
        if (status == ESRCH) {
            delete_process(pcb[i].pid, pcb, process_count);
            process_count--;
            i--;
        }
    }

    return process_count;
}


int exit_cmd() {
    update_process_count();
    for (int i = 0; i < process_count; i++) {
        if (waitpid(pcb[i].pid, NULL, WNOHANG) == 0) {
            kill(pcb[i].pid, SIGKILL);
        }
    }
    struct rusage ru;
    getrusage(RUSAGE_CHILDREN, &ru);
    printf("User time = \t\t%ld seconds\nSys  time = \t\t%ld seconds\n", ru.ru_utime.tv_sec, ru.ru_stime.tv_sec);

    return 1;
}


int jobs_cmd() {
    int active = 0;
    struct rusage ru;
    update_process_count();
    if (process_count > 0) {
        printf("#\tPID\tS\tSEC\tCOMMAND\n");
        for (int i = 0; i < process_count; i++) {
            int sec;
            sec = get_cpu_time(pcb[i].pid);
            printf("%d:\t%d\t%c\t%d\t%s\n", i, pcb[i].pid, pcb[i].status, sec, pcb[i].command);
            if (pcb[i].status == 'R') {
                active++;
            }
        }
    }
    printf("Processes =\t\t%d active\n", active);
    getrusage(RUSAGE_CHILDREN, &ru);
    printf("User time =\t\t%ld seconds\n", ru.ru_utime.tv_sec);
    printf("Sys  time =\t\t%ld seconds\n", ru.ru_stime.tv_sec);
    return 1;
}

int kill_cmd(pid_t pid) {
    process_count =update_process_count();
    if (kill(pid, SIGKILL) == 0) {
        delete_process(pid, pcb, process_count);
        process_count--;
    } else {
        printf("Error killing this pid\n");
        return 0;
    }
    return 1;
}


int resume_cmd(pid_t pid) {
    printf("suspend\n");
    if (waitpid(pid, NULL, WNOHANG) == pid) {
        delete_process(pid, pcb, process_count);
        process_count--;
        printf("Process finished!\n");
        return 0;
    }
    if (kill(pid, SIGCONT) == 0) {
        for (int i = 0; i < process_count; i++) {
            if (pcb[i].pid == pid) {
                pcb[i].status = 'R';
            }
        }
    }

    return 1;
}


//void sleep_cmd(int sec) {
//    sleep(sec);
//}


int suspend_cmd(pid_t pid) {
    if (waitpid(pid, NULL, WNOHANG) == pid) {
        delete_process(pid, pcb, process_count);
        process_count--;
        printf("Process finished!\n");
        return 0;
    }
    if (kill(pid, SIGSTOP) == 0) {
        for (int i = 0; i < process_count; i++) {
            if (pcb[i].pid == pid) {
                pcb[i].status = 'T';
            }
        }
    }

    return 1;
}


int wait_cmd(pid_t pid) {
    waitpid(pid, NULL, 0);
    delete_process(pid, pcb, process_count);
    process_count--;
    return 1;
}

int other_cmd(char commands[MAX_ARGS][MAX_LENGTH], int num_args, char raw_input[LINE_LENGTH + 2]) {

//    for (int i = 0; i < num_args; i++) {
//        if (commands[i][0] == '<') {
//            int file = open(strtok(commands[i], "<"), O_RDONLY);
//            dup2(file, STDIN_FILENO);
//            strcpy(commands[i], "");
//            close(file);
//        }
//        else if (commands[i][0] == '>') {
//            int file = open(strtok(commands[i], ">"), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
//            dup2(file, STDOUT_FILENO);
//            strcpy(commands[i], "");
//            close(file);
//        }
//    }

    int child_pid = fork();
    int status;


    if (child_pid == 0) {


        for (int i = 0; i < num_args; i++) {
            if (commands[i][0] == '<') {
                int file = open(strtok(commands[i], "<"), O_RDONLY);
                dup2(file, STDIN_FILENO);
                strcpy(commands[i], "");
                close(file);
            } else if (commands[i][0] == '>') {
                int file = open(strtok(commands[i], ">"), O_WRONLY | O_TRUNC | O_CREAT,
                                S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                dup2(file, STDOUT_FILENO);
                strcpy(commands[i], "");
                close(file);
            }
        }


        char *args[num_args + 1];
        *(args + num_args) = NULL;
        for (int i = 0; i < num_args; i++) {
            *(args + i) = commands[i];
        }

        if (execvp(args[0], args) == 0) {
            perror("Error executing command with execvp()");
        }
        _exit(EXIT_SUCCESS);
    } else if (child_pid < 0) {
        perror("Fork failed");
        _exit(EXIT_FAILURE);
    } else {
        if (strcmp(commands[num_args - 1], "&") == 0) {
            // running background
            process_count = update_process_count();
            if (process_count >= MAX_PT_ENTRIES) {
                printf("MAX process entries reached, running on foreground!\n");
                do {
                    waitpid(child_pid, &status, WUNTRACED);
                } while (!WIFEXITED(status) && !WIFSIGNALED(status));
            } else {
                strcpy(pcb[process_count].command, raw_input);
                pcb[process_count].pid = child_pid;
                pcb[process_count].status = 'R';
                process_count++;
            }
        } else {
            do {
                waitpid(child_pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }

    return 1;
}


//int parse_input(char *raw_input, char commands[MAX_ARGS][MAX_LENGTH]) {
//    char *command;
//    char delimiter[] = " ";
//    int index = 0;
//    char input[strlen(raw_input)];
//
//    strcpy(input, raw_input);
//
//    command = strtok(input, delimiter);
//    while (command != NULL) {
//        if (strlen(command) <= MAX_LENGTH) {
//            strcpy(commands[index], command);
//        } else {
//            printf("Invalid Command: single argument more than 20 characters!");
//            return -1;
//        }
//
//        index++;
//        if (index > MAX_ARGS) {
//            printf("Invalid Command: more than 7 arguments!");
//            return -1;
//        }
//        command = strtok(NULL, delimiter);
//    }
//
//    return index;
//}

int main() {


    while (1) {
        char raw_input[LINE_LENGTH + 2];
        char commands[MAX_ARGS][MAX_LENGTH];
        for (int i = 0; i < MAX_ARGS; i++) {
            for (int j = 0; j < MAX_LENGTH; j++) {
                commands[i][j] = '\0';
            }
        }

        fflush(stdout);
        fflush(stdin);
        printf("SHELL379: ");
        // https://www.geeksforgeeks.org/taking-string-input-space-c-3-different-methods/
        // reads a line from the specified stream and stores it into the string pointed to by str.
        // It stops when either (n-1) characters are read, the newline character is read, or the end-of-file
        // is reached, whichever comes first.

        fgets(raw_input, sizeof(raw_input), stdin);
        //    if (raw_input[strlen(raw_input)-1] == '\0') {
        //        printf("0");
        //    }
        //    else if (raw_input[strlen(raw_input)-1] == '\n'){
        //        printf("n");
        //    }
        if (raw_input[strlen(raw_input) - 1] != '\n') {
            printf("Input more than 100 characters!\n");
            fflush(stdout);
            continue;
        }

        raw_input[strlen(raw_input) - 1] = '\0';
        int num_args;
        num_args = parse_input(raw_input, commands);
        if (num_args == -1) {
            continue;
        }

        if (commands[0][0] == '\0') continue;
        if (strchr(raw_input, '&') != NULL) {
            if (strcmp(commands[num_args - 1], "&") != 0) {
                printf("Invalid Command: & is not last argument!");
            }
        }

        if (strcmp(commands[0], "exit") == 0) {
            if (num_args != 1) {
                printf("Invalid Command: \"wait\" command does not take argument!\n");
                continue;
            }
            exit_cmd();
            break;
        } else if (strcmp(commands[0], "jobs") == 0) {
            if (num_args != 1) {
                printf("Invalid Command: \"jobs\" command does not take argument!\n");
                continue;
            }
            jobs_cmd();
        } else if (strcmp(commands[0], "kill") == 0) {
            if (num_args != 2) {
                printf("Invalid Command: \"kill\" command takes exactly one argument!\n");
                continue;
            }
            // https://stackoverflow.com/questions/20091356/check-for-valid-integer
            char *endptr;
            int num = (int) strtol(commands[1], &endptr, 10);
            if (*endptr != '\0') {
                printf("Invalid Command: the argument should be an integer!\n");
                continue;
            }

            kill_cmd(num);
        } else if (strcmp(commands[0], "resume") == 0) {
            if (num_args != 2) {
                printf("Invalid Command: \"resume\" command takes exactly one argument!\n");
                continue;
            }

            char *endptr;
            int num = (int) strtol(commands[1], &endptr, 10);
            if (*endptr != '\0') {
                printf("Invalid Command: the argument should be an integer!\n");
                continue;
            }

            resume_cmd(num);
        } else if (strcmp(commands[0], "sleep") == 0) {
            if (num_args != 2) {
                printf("Invalid Command: \"sleep\" command takes exactly one argument!\n");
                continue;
            }

            char *endptr;
            int num = (int) strtol(commands[1], &endptr, 10);
            if (*endptr != '\0') {
                printf("Invalid Command: the argument should be an integer!\n");
                continue;
            }

            sleep_cmd(num);
        } else if (strcmp(commands[0], "suspend") == 0) {
            if (num_args != 2) {
                printf("Invalid Command: \"suspend\" command takes exactly one argument!\n");
                continue;
            }

            char *endptr;
            int num = (int) strtol(commands[1], &endptr, 10);
            if (*endptr != '\0') {
                printf("Invalid Command: the argument should be an integer!\n");
                continue;
            }

            suspend_cmd(num);
        } else if (strcmp(commands[0], "wait") == 0) {
            if (num_args != 2) {
                printf("Invalid Command: \"wait\" command takes exactly one argument!\n");
                continue;
            }

            char *endptr;
            int num = (int) strtol(commands[1], &endptr, 10);
            if (*endptr != '\0') {
                printf("Invalid Command: the argument should be an integer!\n");
                continue;
            }

            wait_cmd(num);
        } else {
            other_cmd(commands, num_args, raw_input);
        }

    }
    return 0;
}
