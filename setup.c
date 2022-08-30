//
// Created by arniejhingran on 6/28/22.
//
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include "config-parser.h"

void createFile(char path[], unsigned num);
/**
 * establishes the test directories and populates them with n files based on config
 * @param num
 */
void setupTestDirectory(unsigned num){
    char dirName[32];
    sprintf(dirName, "testFiles-%i", num);
    mkdir(dirName, 0777);
    for(int i = 0; i<files; i++){
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
    char fileCreation[100];
    sprintf(fileCreation, "dd if=/dev/random of=%s oflag=direct,sync bs=1M count=1024 2>&1", filename);
    //

    if(fileToWrite != NULL){
        if(num<read_f){
            system(fileCreation);
        }
        else{
            fprintf(fileToWrite, "test-file-generated\n");
        }
    }

    fclose(fileToWrite);
}


/**
 * sets up n test directories
 * @return
 */
int main(){
    parseConfig();
    mkdir("test-directory", 0777);
    chdir("test-directory");
    for(int i = 0; i<directories; i++){
        setupTestDirectory(i);
    }
}


