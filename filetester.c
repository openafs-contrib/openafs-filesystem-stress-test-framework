//
// Created by arniejhingran on 7/13/22.
//
#include <stdlib.h>
#include "stdio.h"
#include "unistd.h"

/**
 * runs the two executables in parallel, each manipulating 8 directories
 * @return
 */
int main(int argc, char** argv){
    int offset = 2;
    int baseDir = 0;

    for(int i = 0; i<8; i++) {
        char arg1[2];
        char arg2[2];
        sprintf(arg1, "%d", offset);
        sprintf(arg2, "%d", baseDir);
        char* args[2];
        args[0] = arg1;
        args[1] = arg2;

        //sprintf(execstring, "./filemonkeytester %d %d", offset, baseDir);
        int pid = fork();
        if (pid == -1) {
            fprintf(stderr, "Error in forking the process");
            return 1;
        }
        else if (pid == 0) {
            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
            //printf("%d\t%d\n", baseDir, offset);
            execvp("./filemonkeytester", args);
            exit(0);
        }
        else {
            baseDir += offset;
        }
    }
    return 0;
}

