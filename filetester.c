//
// Created by arniejhingran on 7/13/22.
//
#include <stdlib.h>
#include <wait.h>
#include "stdio.h"
#include "unistd.h"
#include "config-parser.h"
#define execString "./filemonkeytester"
/**
 * runs the two executables in parallel, each manipulating 8 directories
 * @return
 */
int main(int argc, char** argv){
    parseConfig();
    if(directories%cores != 0) {
        fprintf(stderr, "error in config, num of directories must be divisible by core count");
        return 15;
    }
    int offset = directories/cores;
    int baseDir = 0;

    for(int i = 0; i<cores; i++) {
        char arg1[2];
        char arg2[2];
        sprintf(arg1, "%d", offset);
        sprintf(arg2, "%d", baseDir);
        char* args[4] = {execString,arg1, arg2, NULL};

        //sprintf(execstring, "./filemonkeytester %d %d", offset, baseDir);
        int pid = fork();
        if (pid == -1) {
            fprintf(stderr, "Error in forking the process");
            return 1;
        }
        else if (pid == 0) {
            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
            //printf("%d\t%d\n", baseDir, offset);
            execvp(execString, args);
            exit(0);
        }
        else {
            baseDir += offset;
        }
    }
    for(int i = 0; i<cores; i++) wait(NULL);

    return 0;
}

