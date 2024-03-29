//
// Created by arniejhingran on 6/28/22.
// List of file operations utilized by the tester
//

#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <fcntl.h>
#include "config-parser.h"
#define FILEFORMAT "test-directory/testFiles-%i/testfile%i.txt"
char global_buffer[10];
int file_miss_count = 0;


/**
 * simple function to append a file with a given path
 * records time taken in absolute wall time to do the add operation and returns the value
 * @param path
 */
double addToFile(char path[]){
    FILE* fileToAppend = NULL;
    fileToAppend = fopen(path, "a+");
    //adds 100 lines of the following text
    struct timeval start, end;
    double time_used = 0;
    if(fileToAppend != NULL){
        for(int i = 0; i<100; i++){
            gettimeofday(&start, NULL);
            fprintf(fileToAppend, "data inserted during test\n");
            gettimeofday(&end, NULL);
            time_used += (double) (end.tv_sec-start.tv_sec)+ (double)(end.tv_usec-start.tv_usec)/1000000;
        }
        fclose(fileToAppend);
        return time_used;
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
 * reads the entire file sequentially and records the throughput value
 * caching is partially minimized due to O_SYNC, O_Direct implementation coming...
 * @param path
 * @return throughput
 */
double read_Sequential(char path[]){
    unsigned char buffer[10000];
    int fd;
    fd = open(path ,O_RDONLY | O_SYNC);
    struct timeval start, end;
    long count = 0;
    double time_used = 0;
    if(fd != -1) {
        //time_t end = time(NULL)+5;
        gettimeofday(&start, NULL);
        //num = read(fd, buffer, 1000000);
        while (read(fd, buffer, 10000) == 10000) {
            //num_el = fread(buffer, 1, 1000000, fileToRead);
            count+=10000;
        }
        gettimeofday(&end, NULL);
        time_used = (double) (end.tv_sec-start.tv_sec)*1000000+ (double)(end.tv_usec-start.tv_usec);

        double throughput = (double) (count*1000000/time_used);
        close(fd);
        return throughput;
    }
    else{
        file_miss_count++;
        return -1;
    }
}

/**
 * randomly reads from the file based on a random offset
 * returns the throughput
 * @param path
 * @return throughput
 */
double random_Read(char path[]) {
    srand(rand());
    unsigned char buffer[10000];
    int fd;
    fd = open(path ,O_RDONLY | O_SYNC);
    struct timeval start, end;
    long count = 0;
    double time_used = 0;
    if(fd != -1) {
        //time_t end = time(NULL)+5;
        gettimeofday(&start, NULL);
        //num = read(fd, buffer, 1000000);
        while (read(fd, buffer, 10000) == 10000) {
            lseek(fd, rand()%50000, SEEK_CUR);
            count+=10000;
        }
        gettimeofday(&end, NULL);
        time_used = (double) (end.tv_sec-start.tv_sec)*1000000+ (double)(end.tv_usec-start.tv_usec);

        double throughput = (double) (count*1000000/time_used);
        close(fd);
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
 * records the time the operation takes and returns
 * @param pathSource
 * @param dirNum
 */
double renameFile(char pathSource[], int dirNum){
    parseConfig();
    char pathDest[56];
    int filenum = rand() % files+100;
    sprintf(pathDest, FILEFORMAT, dirNum, filenum);

    struct timeval start, end;
    gettimeofday(&start, NULL);
    int status = rename(pathSource, pathDest);
    gettimeofday(&end, NULL);
    double time_used = (double) (end.tv_sec-start.tv_sec)+ (double)(end.tv_usec-start.tv_usec)/1000000;

    if(status!= 0){
        file_miss_count++;
        return -1;
    }
    return time_used;
}

/**
 * deletes a given file
 * records the time the operation takes and returns
 * @param pathSource
 */
double deleteFile(char pathSource[]){
    struct timeval start, end;
    gettimeofday(&start, NULL);
    int status = remove(pathSource);
    gettimeofday(&end, NULL);
    double time_used = (double) (end.tv_sec-start.tv_sec)+ (double)(end.tv_usec-start.tv_usec)/1000000;

    if(status!= 0){
        file_miss_count++;
        return -1;
    }
    return time_used;
}

/**
 * creates file
 * records the time the operation takes and returns
 * @param pathSource
 */
double createFile(char path[]){
    struct timeval start, end;
    gettimeofday(&start, NULL);
    FILE *newFile = fopen(path, "w+");
    gettimeofday(&end, NULL);
    double time_used = (double) (end.tv_sec-start.tv_sec)+ (double)(end.tv_usec-start.tv_usec)/1000000;

    if(newFile == NULL){
        file_miss_count++;
        return -1;
    }
    fclose(newFile);
    return time_used;
}
