//
// Created by arniejhingran on 7/13/22.
//
#include "stdio.h"
#include "string.h"
#include <sys/stat.h>
#include <stdlib.h>
#include "time.h"
#include "fileoperations.h"
#include "config-parser.h"

/**
 * tester runs on directories 0-8, manipulating random files with random operations
 * @return
 */
int main(int argc, char** argv){
    if(argc != 3){
        fprintf(stderr, "Incorrect Number of Arguments. Should be 2, got %d", argc);
        return 15;
    }
    parseConfig();
    //setup fields for names of directories and files
    char* dirLowerBound = *(argv+2);
    char* offsetArg = *(argv+1);
    int lowerBound = atoi(dirLowerBound);
    int offset = atoi(offsetArg);

    //printf("%d\t%d", lowerBound, offset);

    char dirName[32];
    char filename[56];
    char filenameCopy[56];
    //cpu time variables
    clock_t start, end;
    double cpu_time_used;
    FILE* timep = fopen("cpu-time.txt", "w+");
    FILE* read_time = fopen("read-metrics.txt", "w+");
    FILE* filesused = fopen("files-used.txt", "a+");
    //setting up the seed and timing
    srand(rand());
    time_t end_of_test = time(NULL)+time_of_test*60;

    //tests for 5 minutes
    while(time(NULL)<= end_of_test){
        int dirnum = rand() % offset + lowerBound;
        int filenum = rand() % files;
        sprintf(dirName, "testFiles-%i", dirnum);
        sprintf(filename, "%s/testfile%i.txt", dirName, filenum);
        sprintf(filenameCopy, "%s/testfile%i.txt", dirName, filenum/2);


        fprintf(filesused,"%s\t%d\n", filename, file_miss_count);

        if(filenum<read_f){
            double read_t = readIntoBuffer(filename);
            if(read_t != -1) fprintf(read_time, "%f\n", read_t);
        }
        else {
            if (rand() % 100 < write_chance) {
                start = clock();
                addToFile(filename);
                end = clock();
                cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                fprintf(timep, "%f\n", cpu_time_used);
            }

            if (rand() % 100 < copy_chance) copyContents(filename, filenameCopy);

            if (rand() % 100 < rename_chance) {
                renameFile(filenameCopy, dirnum);
            }
            if (rand() % 100 < delete_chance) {
                deleteFile(filename);
            }
        }

    }

    //closing log files
    fclose(timep);
    fclose(filesused);
    fclose(read_time);
    return 0;

}
