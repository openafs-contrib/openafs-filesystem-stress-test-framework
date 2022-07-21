//
// Created by arniejhingran on 6/28/22.
//
#include "stdio.h"
#include "string.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
void createFile(char path[], unsigned num);

/**
 * establishes the test directories and populates them with 100 files
 * @param num
 */
void setupTestDirectory(unsigned num){
    char dirName[32];
    sprintf(dirName, "testFiles-%i", num);
    mkdir(dirName, 0777);
    for(int i = 0; i<100; i++){
        createFile(dirName, i);
    }
}

/**
 * creates test files in the form of .txt files
 * @param path
 * @param num
 */
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

/**
 * sets up 16 test directories
 * @return
 */
int main(){
    for(int i = 0; i<16; i++){
        setupTestDirectory(i);
    }
}


