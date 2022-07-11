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

int main(){
    char dirName[32];
    char filename[56];
    char filenameCopy[56];
    clock_t start, end;
    double cpu_time_used;
    FILE* timep = fopen("cpu-time.txt", "w+");
    srand(rand());
    while(file_miss_count<100000){
        int dirnum = rand() % 8;
        int filenum = rand() % 50;
        sprintf(dirName, "testFiles-%i", dirnum);
        sprintf(filename, "%s/testfile%i.txt", dirName, filenum);
        sprintf(filenameCopy, "%s/testfile%i.txt", dirName, filenum/2);


        printf("%s\t%s\t%d\n", filename, filenameCopy, file_miss_count);

        if(rand() % 10 < 7) {
            start = clock();
            addToFile(filename);
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            fprintf(timep, "%f\n", cpu_time_used);
        }

        if(rand() % 10 < 4) copyContents(filename, filenameCopy);

        if(rand()%10<1) {
            renameFile(filenameCopy, dirnum);
            deleteFile(filename);
        }
    }

    //renameFile("testFiles-0/testfile0.txt", 0);
    //deleteFile("testFiles-0/testfile0.txt");
    //addToFile("testFiles-0/testfile1.txt");
    //copyContents("testFiles-0/testfile1.txt", "testFiles-0/testfile2.txt");
}
