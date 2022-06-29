//
// Created by arniejhingran on 6/28/22.
//
#include "stdio.h"
#include "string.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
void createFile(char path[], unsigned num);


void setupTestDirectory(unsigned num){
    char dirName[32];
    sprintf(dirName, "testFiles-%i", num);
    mkdir(dirName, 0777);
    for(int i = 1; i<16; i++){
        createFile(dirName, i);
    }
}

void createFile(char path[], unsigned num){
    char filename[32];
    sprintf(filename, "%s/testfile%i.txt", path, num);
    FILE* fileToWrite = NULL;
    fileToWrite = fopen(filename, "w+");
    if(fileToWrite != NULL){
        fprintf(fileToWrite, "test-file-generated\n");
    }
    fclose(fileToWrite);
}

int main(){
    for(int i = 0; i<4; i++){
        setupTestDirectory(i);
    }
}


