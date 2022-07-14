//
// Created by arniejhingran on 7/14/22.
//
//
// Created by arniejhingran on 7/13/22.
//
#include "stdio.h"
#include "string.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "time.h"
#include "fileoperations.h"

int main(){
    char dirName[32];
    char filename[56];
    char filenameCopy[56];
    clock_t start, end;
    double cpu_time_used;
    FILE* timep = fopen("cpu-time.txt", "w+");
    srand(rand());
    while(file_miss_count<100000){
        int dirnum = rand() % 8 + 8;
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
