//
// Created by arniejhingran on 6/28/22.
// List of file operations utilized by the tester
//
#include "stdio.h"
#include "string.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "time.h"
#include "config-parser.h"

#define FILEFORMAT "testFiles-%i/testfile%i.txt"
char buffer[INT_MAX];
int file_miss_count = 0;


/**
 * simple function to append a file with a given path
 * @param path
 */
void addToFile(char path[]){
    FILE* fileToAppend = NULL;
    fileToAppend = fopen(path, "a+");
    //adds 100 lines of the following text
    if(fileToAppend != NULL){
        for(int i = 0; i< 100; i++) fprintf(fileToAppend, "data inserted during test\n");
        fclose(fileToAppend);
    }
    else{
        file_miss_count++;
    }
}

/**
 * overwrites a given file with the data given
 * @param data to overwrite with
 * @param path
 */
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

/**
 * reads the first 10000 characters from the file into the buffer
 * @param path
 */
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

/**
 * copies the first 100000 characters from the source file to the dest file
 * @param pathSource
 * @param pathDest
 */
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
    overwriteFile(data, pathDest);
}

/**
 * renames a given file
 * @param pathSource
 * @param dirNum
 */
void renameFile(char pathSource[], int dirNum){
    parseConfig();
    char pathDest[56];
    int filenum = rand() % files+100;
    sprintf(pathDest, FILEFORMAT, dirNum, filenum);
    if(rename(pathSource, pathDest) != 0) file_miss_count++;
}

/**
 * deletes a given file
 * @param pathSource
 */
void deleteFile(char pathSource[]){
    if(remove(pathSource)) file_miss_count++;
}


