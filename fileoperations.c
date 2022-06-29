//
// Created by arniejhingran on 6/28/22.
//
#include "stdio.h"
#include "string.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
char buffer[255];

void addToFile(char path[]){
    FILE* fileToAppend = NULL;
    fileToAppend = fopen(path, "a+");
    if(fileToAppend != NULL){
        fprintf(fileToAppend, "data inserted during test\n");
    }
    fclose(fileToAppend);
}

void overwriteFile(char path[]){
    FILE* fileToWrite = fopen(path, "w+");
    fprintf(fileToWrite, "%s", buffer);
    fclose(fileToWrite);
}

void readIntoBuffer(char path[]){
    FILE* fileToRead = fopen(path, "r");
    int c = fgetc(fileToRead);
    for(int i = 0; c != EOF; i++){
        buffer[i] = (char) c;
        c = fgetc(fileToRead);
    }
    fclose(fileToRead);
}

void copyContents(char pathSource[], char pathDest[]){
    readIntoBuffer(pathSource);
    overwriteFile(pathDest);
}

int main(){
    addToFile("testFiles-0/testfile1.txt");
    copyContents("testFiles-0/testfile1.txt", "testFiles-0/testfile2.txt");
}
