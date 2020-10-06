//
// Created by Yifei Ma on 2020-10-01.
//

#include "Calc_time.h"

int get_cpu_time(pid_t pid) {
    // open ps as file -A indicates all process
    FILE *fp = popen("ps -A", "r");
    char line[1000];

    while (fgets(line, sizeof(line), fp) != NULL) {
        int i = 0;
        char *tokens[100];
        char *token = strtok(line, " ");
        while (token != NULL) {
            tokens[i] = token;
            i++;
            token = strtok(NULL, " ");
        }
        char *endptr;
        int current_pid = (int) strtol(tokens[0], &endptr, 10);
        if (*endptr == '\0' && current_pid == pid) {
            int h, m, s;
            int cpu_time;
            // reformat from hh:mm:ss to sec
            sscanf(tokens[2], "%02d:%02d:%02d", &h, &m, &s);
            cpu_time = h * 3600 + m * 60 + s;
            pclose(fp);
            return cpu_time;
        }
        memset(line, '\0', sizeof(*line));
    }
    pclose(fp);
    return -1;

}