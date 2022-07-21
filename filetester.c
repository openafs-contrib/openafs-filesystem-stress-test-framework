//
// Created by arniejhingran on 7/13/22.
//
#include "stdio.h"
#include "unistd.h"

/**
 * runs the two executables in parallel, each manipulating 8 directories
 * @return
 */
int main(){
    int pid = fork();
    if(pid == -1){
        fprintf(stderr, "Error in forking the process");
        return 1;
    }
    else if (pid == 0){
        execvp("./fileexec-2", NULL);
    }
    else{
        execvp("./fileexec-1", NULL);
    }
    return 0;
}

