//
// Created by arniejhingran on 6/28/22.
//
#include "stdio.h"
#include "string.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "time.h"

#define FILEFORMAT "testFiles-%i/testfile%i.txt"
char buffer[INT_MAX];
int file_miss_count = 0;

void addToFile(char path[]){
    FILE* fileToAppend = NULL;
    fileToAppend = fopen(path, "a+");
    if(fileToAppend != NULL){
        for(int i = 0; i< 100; i++) fprintf(fileToAppend, "data inserted during test\n");
        fclose(fileToAppend);
    }
    else{
        file_miss_count++;
    }
}

void overwriteFile(char data[], char path[]){
    FILE* fileToWrite = fopen(path, "w+");
    if(fileToWrite != NULL){
        fprintf(fileToWrite, "%s", data);
        fclose(fileToWrite);
    }
    else{
        file_miss_count++;
    }
}

void readIntoBuffer(char path[]){
    FILE* fileToRead = fopen(path, "r");
    if(fileToRead != NULL) {
        int c = fgetc(fileToRead);
        for (int i = 0; c != EOF && i<10000; i++) {
            buffer[i] = (char) c;
            c = fgetc(fileToRead);
        }
        fclose(fileToRead);
    }
    else{
        file_miss_count++;
    }
}

void copyContents(char pathSource[], char pathDest[]){
    char data[100000];
    FILE* fileToRead = fopen(pathSource, "r");

    if(fileToRead != NULL) {
        int c = fgetc(fileToRead);
        for (int i = 0; c != EOF && i<100000; i++) {
            data[i] = (char) c;
            c = fgetc(fileToRead);
        }
        fclose(fileToRead);
    }
    else{
        file_miss_count++;
    }
    //readIntoBuffer(pathSource);
    overwriteFile(data, pathDest);
}

void renameFile(char pathSource[], int dirNum){
    char pathDest[56];
    int filenum = rand() % 100;
    sprintf(pathDest, FILEFORMAT, dirNum, filenum);
    if(rename(pathSource, pathDest) != 0) file_miss_count++;
}

void deleteFile(char pathSource[]){
    if(remove(pathSource)) file_miss_count++;
}


