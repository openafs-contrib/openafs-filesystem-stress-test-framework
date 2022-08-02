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
char global_buffer[10];
int file_miss_count = 0;


/**
 * simple function to append a file with a given path
 * @param path
 */
double addToFile(char path[]){
    FILE* fileToAppend = NULL;
    fileToAppend = fopen(path, "a+");
    //adds 100 lines of the following text
    clock_t start, end;
    double time_used = 0;
    if(fileToAppend != NULL){
        for(int i = 0; i<100; i++){
            start = clock();
            fprintf(fileToAppend, "data inserted during test\n");
            end = clock();
            time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
        }
        fclose(fileToAppend);
        return time_used/100;
    }
    else{
        file_miss_count++;
        return -1;
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
double read_Sequential(char path[]){
    char buffer[1000000];
    FILE* fileToRead = fopen(path, "r");
    clock_t start, end;
    int num_el = 1000, count = 0;
    double time_used = 0;
    if(fileToRead != NULL) {
        //time_t end = time(NULL)+5;
        while (num_el == 1000) {
            start = clock();
            num_el = fread(buffer, 1, 1000, fileToRead);
            end = clock();
            count+=num_el;
            time_used += ((double) (end - start)) / CLOCKS_PER_SEC;
        }
        double throughput = count/time_used;
        fclose(fileToRead);
        return throughput;
    }
    else{
        file_miss_count++;
        return -1;
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
double renameFile(char pathSource[], int dirNum){
    parseConfig();
    char pathDest[56];
    int filenum = rand() % files+100;
    sprintf(pathDest, FILEFORMAT, dirNum, filenum);

    clock_t start, end;
    start = clock();
    int status = rename(pathSource, pathDest);
    end = clock();
    double time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    if(status!= 0){
        file_miss_count++;
        return -1;
    }
    return time_used;
}

/**
 * deletes a given file
 * @param pathSource
 */
double deleteFile(char pathSource[]){
    clock_t start, end;
    start = clock();
    int status = remove(pathSource);
    end = clock();
    double time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    if(status!= 0){
        file_miss_count++;
        return -1;
    }
    return time_used;
}

/**
 * creates file
 * @param pathSource
 */
double createFile(char path[]){
    clock_t start, end;
    start = clock();
    FILE *newFile = fopen(path, "w+");
    end = clock();
    double time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    if(newFile == NULL){
        file_miss_count++;
        return -1;
    }
    fclose(newFile);
    return time_used;
}
