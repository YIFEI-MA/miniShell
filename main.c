#include "main.h"
#include "Calc_time.h"
#include "helperFunction.h"

struct process pcb[MAX_PT_ENTRIES];
int process_count = 0;


int update_process_count() {
    if (process_count == 0) {
        return process_count;
    }

    int status;
    // check if process still exist
    for (int i=0; i < process_count; i++) {
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
    // kill all process before exit
    for (int i = 0;i < process_count; i++) {
        if (waitpid(pcb[i].pid, NULL, WNOHANG) == 0) {
            kill(pcb[i].pid, SIGKILL);
        }
    }
    struct rusage ru;
    getrusage(RUSAGE_CHILDREN, &ru);
    printf("User time = \t\t%ld seconds\nSys  time = \t\t%ld seconds\n", ru.ru_utime.tv_sec, ru.ru_stime.tv_sec);

    return 1;
}


int jobs_cmd(){
    int active = 0;
    struct rusage ru;
    update_process_count();
    if (process_count > 0) {
        printf("#\tPID\tS\tSEC\tCOMMAND\n");
        for (int i=0; i<process_count; i++) {
            int sec;
            //get cpu time for each process
            sec = get_cpu_time(pcb[i].pid);
            printf("%d:\t%d\t%c\t%d\t%s\n", i, pcb[i].pid, pcb[i].status, sec, pcb[i].command);
            if (pcb[i].status == 'R') {
                active++;
            }
        }
    }
    printf("Processes =\t\t%d active\n", active);
    getrusage(RUSAGE_CHILDREN, &ru);
    // get time for all exited process
    printf("User time =\t\t%ld seconds\n", ru.ru_utime.tv_sec);
    printf("Sys  time =\t\t%ld seconds\n", ru.ru_stime.tv_sec);
    return 1;
}

int kill_cmd(pid_t pid) {
    update_process_count();
    if (kill(pid, SIGKILL)==0) {
        // delete from pcb
        delete_process(pid, pcb, process_count);
        process_count--;
    }
    else {
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
        for (int i=0; i < process_count; i++) {
            if (pcb[i].pid == pid) {
                pcb[i].status = 'R';
            }
        }
    }

    return 1;
}


void sleep_cmd(int sec) {
    sleep(sec);
}


int suspend_cmd(pid_t pid) {
    if (waitpid(pid, NULL, WNOHANG) == pid) {
        delete_process(pid, pcb, process_count);
        process_count--;
        printf("Process finished!\n");
        return 0;
    }
    if (kill(pid, SIGSTOP) == 0) {
        // set state to T
        for (int i=0; i < process_count; i++) {
            if (pcb[i].pid == pid) {
                pcb[i].status = 'T';
            }
        }
    }

    return 1;
}


int wait_cmd(pid_t pid) {
    // wait a process finish
    waitpid(pid, NULL, 0);
    delete_process(pid, pcb, process_count);
    process_count--;
    return 1;
}

int other_cmd(char commands[MAX_ARGS][MAX_LENGTH], int num_args, char raw_input[LINE_LENGTH+2]){

    // redirect needs to be done within child process

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
        // child


        for (int i = 0; i < num_args; i++) {
            if (commands[i][0] == '<') {
                int file = open(strtok(commands[i], "<"), O_RDONLY);
                dup2(file, STDIN_FILENO);
                strcpy(commands[i], "");
                close(file);
            }
            else if (commands[i][0] == '>') {
                int file = open(strtok(commands[i], ">"), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
                dup2(file, STDOUT_FILENO);
                strcpy(commands[i], "");
                close(file);
            }
        }






        char * args[num_args+1];
        * (args + num_args) = NULL;
        for (int i = 0; i < num_args; i++) {
            *(args + i) = commands[i];
        }

        if (execvp(args[0], args) == 0) {
            perror("Error executing command with execvp()");
        }
        _exit(EXIT_SUCCESS);
    }
    else if (child_pid < 0) {
        // error
        perror("Fork failed");
        _exit(EXIT_FAILURE);
    }
    else {
        // parent
        if (strcmp(commands[num_args-1], "&") == 0) {
            // running background
            process_count = update_process_count();
            if (process_count >= MAX_PT_ENTRIES) {
                printf("MAX process entries reached, running on foreground!\n");
                do {
                    waitpid(child_pid, &status, WUNTRACED);
                }while (!WIFEXITED(status) && !WIFSIGNALED(status));
            }
            else {
                strcpy(pcb[process_count].command, raw_input);
                pcb[process_count].pid = child_pid;
                pcb[process_count].status = 'R';
                process_count++;
            }
        }
        else {
            // wait child to be finished
            do {
                waitpid(child_pid, &status, WUNTRACED);
            }while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }

    return 1;
}


int main() {


    while (1) {
        fflush(stdout);
        fflush(stdin);
        char raw_input[LINE_LENGTH+2];
        char commands[MAX_ARGS][MAX_LENGTH];

        // initialize pcb
        for (int i=0; i < MAX_ARGS; i++) {
            for (int j=0; j < MAX_LENGTH; j++){
                commands[i][j] = '\0';
            }
        }

        printf("SHELL379: ");
        fflush(stdout);
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

        // raw line ends with \n and \0
        if (raw_input[strlen(raw_input)-1] != '\n') {
            printf("Input more than 100 characters!\n");
            fflush(stdout);
            continue;
        }

        raw_input[strlen(raw_input)-1] = '\0';
        int num_args;
        num_args = parse_input(raw_input, commands);
        if (num_args == -1) {
            continue;
        }

        if (commands[0][0] == '\0') continue;
        if (strchr(raw_input, '&') != NULL) {
            if (strcmp(commands[num_args-1], "&") != 0) {
                printf("Invalid Command: & is not last argument!");
            }
        }

        if (strcmp(commands[0], "exit") == 0) {
            if (num_args != 1) {
                printf("Invalid Command: \"wait\" command does not take argument!\n");
                continue;
            }
            // kill all before exit
            exit_cmd();
            break;
        }
        else if (strcmp(commands[0], "jobs") == 0) {
            if (num_args != 1) {
                printf("Invalid Command: \"jobs\" command does not take argument!\n");
                continue;
            }
            jobs_cmd();
        }
        else if (strcmp(commands[0], "kill") == 0) {
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
        }
        else if (strcmp(commands[0], "resume") == 0) {
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
        }
        else if (strcmp(commands[0], "sleep") == 0) {
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
        }
        else if (strcmp(commands[0], "suspend") == 0) {
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
        }
        else if (strcmp(commands[0], "wait") == 0) {
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
        }
        else {
            other_cmd(commands, num_args, raw_input);
            fflush(stdout);
        }

    }
    return 0;
}
