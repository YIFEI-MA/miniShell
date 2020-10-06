//
// Created by Yifei Ma on 2020-10-01.
//

#ifndef COMMANDS_H
#define COMMANDS_H

#include "main.h"
#include "Calc_time.h"

int delete_process(pid_t pid, struct process pcb[MAX_PT_ENTRIES], int process_count);


int parse_input(char *raw_input, char commands[MAX_ARGS][MAX_LENGTH]);

#endif //COMMANDS_H
