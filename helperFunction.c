//
// Created by Yifei Ma on 2020-10-01.
//

#include "helperFunction.h"

int delete_process(pid_t pid, struct process pcb[MAX_PT_ENTRIES], int process_count) {
    int p_index = -1;
    for (int i = 0; i < process_count; i++) {
        if (pcb[i].pid == pid) {
            p_index = i;
            break;
        }
    }
    if (p_index == -1) {
        printf("Invalid index when deleting process!\n");
        return -1;
    }

    for (int i = p_index; i < process_count; i++) {
        pcb[i] = pcb[i + 1];
    }

    return 1;
}


int parse_input(char *raw_input, char commands[MAX_ARGS][MAX_LENGTH]) {
    char *command;
    char delimiter[] = " ";
    int index = 0;
    char input[strlen(raw_input)];

    strcpy(input, raw_input);

    command = strtok(input, delimiter);
    while (command != NULL) {
        if (strlen(command) <= MAX_LENGTH) {
            strcpy(commands[index], command);
        } else {
            printf("Invalid Command: single argument more than 20 characters!");
            return -1;
        }

        index++;
        if (index > MAX_ARGS) {
            printf("Invalid Command: more than 7 arguments!");
            return -1;
        }
        command = strtok(NULL, delimiter);
    }

    return index;
}
