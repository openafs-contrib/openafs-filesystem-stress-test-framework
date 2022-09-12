//
// Created by arniejhingran on 7/13/22.
//
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include "fileoperations.h"
#include "config-parser.h"

/**
 * based on the config file, the tester biases towards or against certain file operations
 * all metrics are recording and saved to the metrics folder
 * @return
 */
int main(int argc, char** argv){
    if(argc != 3){
        fprintf(stderr, "Incorrect Number of Arguments. Should be 2, got %d", argc);
        return 15;
    }
    parseConfig();
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t", cores, write_chance, copy_chance, delete_chance, rename_chance, time_of_test, directories, files, read_f, create_chance);

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
    FILE* read_throughput = fopen("metrics/read-metrics-seq.txt", "a+");
    FILE* read_rand = fopen("metrics/read-metrics-rand.txt", "a+");
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

    //tests for n minutes
    while(time(NULL)<= end_of_test){
        int dirnum = rand() % offset + lowerBound;
        int filenum = rand() % files;
        sprintf(dirName, "test-directory/testFiles-%i", dirnum);
        sprintf(filename, "%s/testfile%i.txt", dirName, filenum);
        sprintf(filenameCopy, "%s/testfile%i.txt", dirName, filenum+1);


        fprintf(filesused,"%s\t%d\n", filename, file_miss_count);

        if(filenum<read_f){
            fprintf(filesused,"%s\t%d\n", filename, file_miss_count);
            double read_t = read_Sequential(filename);
            double read_rand_t = random_Read(filename);
            if(read_t != -1) fprintf(read_throughput, "%f\n", read_t);
            if(read_rand_t != -1) fprintf(read_rand, "%f\n", read_rand_t);
        }

        else {
            if (rand() % 100 < write_chance) {
                double append_t = addToFile(filename);
                if(append_t != -1) fprintf(append_time, "%f\n", append_t);
            }
            if (rand() % 100 < copy_chance) copyContents(filename, filenameCopy);

            if (rand() % 100 < rename_chance) {
                double rename_t = renameFile(filenameCopy, dirnum);
                printf("%f", rename_t);
                if(rename_t != -1) fprintf(rename_time, "%f\n", rename_t);
            }

            if (rand() % 100 < delete_chance) {
                double delete_t = deleteFile(filename);
                if(delete_t != -1) fprintf(delete_time, "%f\n", delete_t);
            }
            if (rand() % 100 < create_chance) {
                char path[50];
                sprintf(path, "%s/created_file%d.txt", dirName, filenum+rand());
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