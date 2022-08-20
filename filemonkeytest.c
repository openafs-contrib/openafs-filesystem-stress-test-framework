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

    //metrics
    mkdir("metrics", 0777);
    FILE* append_time = fopen("metrics/append-metrics.txt", "a+");
    FILE* read_throughput = fopen("metrics/read-metrics.txt", "a+");
    FILE* rename_time = fopen("metrics/rename-metrics.txt", "a+");
    FILE* delete_time = fopen("metrics/delete-metrics.txt", "a+");
    FILE* create_time = fopen("metrics/create-metrics.txt", "a+");
    FILE* filesused = fopen("metrics/files-used.txt", "a+");
    if(append_time == NULL || read_throughput == NULL || rename_time == NULL || delete_time == NULL || filesused == NULL){
        exit(-1);
    }
    //setting up the seed and timing
    srand(rand());
    time_t end_of_test = time(NULL)+time_of_test*60;

    //tests for 5 minutes
    while(time(NULL)<= end_of_test){
        int dirnum = rand() % offset + lowerBound;
        int filenum = rand() % files;
        sprintf(dirName, "testFiles-%i", dirnum);
        sprintf(filename, "%s/testfile%i.txt", dirName, filenum);
        sprintf(filenameCopy, "%s/testfile%i.txt", dirName, filenum+1);


        fprintf(filesused,"%s\t%d\n", filename, file_miss_count);

        if(filenum<read_f){
            fprintf(filesused,"%s\t%d\n", filename, file_miss_count);
            double read_t = read_Sequential(filename);
            if(read_t != -1) fprintf(read_throughput, "%f\n", read_t);
        }
        else {
            if (rand() % 100 < write_chance) {
                double append_t = addToFile(filename);
                if(append_t != -1) fprintf(append_time, "%f\n", append_t);
            }

            if (rand() % 100 < copy_chance) copyContents(filename, filenameCopy);

            if (rand() % 100 < rename_chance) {
                double rename_t = renameFile(filenameCopy, dirnum);
                if(rename_t != -1) fprintf(rename_time, "%f\n", rename_t);
            }

            if (rand() % 100 < delete_chance) {
                double delete_t = deleteFile(filename);
                if(delete_t != -1) fprintf(delete_time, "%f\n", delete_t);
            }
            if (rand() % 100 < create_chance) {
                char path[50];
                sprintf(path, "%s/created_file%d.txt", dirName, filenum+100);
                double create_t = createFile(path);
                if(create_t != -1) fprintf(create_time, "%f\n", create_t);
            }
        }

    }

    //closing log files
    fclose(append_time);
    fclose(rename_time);
    fclose(read_throughput);
    fclose(filesused);
    fclose(delete_time);

    return 0;

}
