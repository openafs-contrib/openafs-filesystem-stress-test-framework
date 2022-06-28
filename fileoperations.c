//
// Created by arniejhingran on 6/28/22.
//
#include "stdio.h"
#include "string.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void setupTestDirectory(){
    mkdir("testFiles", 0777);
}
void createFile(unsigned num){
    char filename[32];
    sprintf(filename, "testFiles/testfile%i.txt", num);
    FILE* fileToWrite = NULL;
    fileToWrite = fopen(filename, "w+");
    if(fileToWrite != NULL){
        fprintf(fileToWrite, "testfilegenerated");
    }
    fclose(fileToWrite);
}

int main(){
    setupTestDirectory();
    createFile(16);
}
