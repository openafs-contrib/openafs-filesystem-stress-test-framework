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

char buffer[INT_MAX];

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
    if(fileToWrite != NULL) fprintf(fileToWrite, "%s", buffer);
    fclose(fileToWrite);
}

void readIntoBuffer(char path[]){
    FILE* fileToRead = fopen(path, "r");
    if(fileToRead != NULL) {
        int c = fgetc(fileToRead);
        for (int i = 0; c != EOF && i<INT_MAX; i++) {
            buffer[i] = (char) c;
            c = fgetc(fileToRead);
        }
    }
    fclose(fileToRead);
}

void copyContents(char pathSource[], char pathDest[]){
    readIntoBuffer(pathSource);
    overwriteFile(pathDest);
}

int main(){
    char dirName[32];
    char filename[56];
    char filenameCopy[56];

    for(int i = 0; i< 100000; i++){
        int dirnum = rand() % 4;
        int filenum = rand() % 16;
        sprintf(dirName, "testFiles-%i", dirnum);
        sprintf(filename, "%s/testfile%i.txt", dirName, filenum);
        sprintf(filenameCopy, "%s/testfile%i.txt", dirName, filenum/2);

        printf("%s\t%s\t%s\t%d\n", dirName, filename, filenameCopy, i);
        addToFile(filename);
        copyContents(filename, filenameCopy);
    }

    //addToFile("testFiles-0/testfile1.txt");
    //copyContents("testFiles-0/testfile1.txt", "testFiles-0/testfile2.txt");
}
