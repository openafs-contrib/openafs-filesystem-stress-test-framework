//
// Created by arniejhingran on 7/13/22.
//

#ifndef OPENAFS_FILESYSTEM_STRESS_TEST_FRAMEWORK_FILEOPERATIONS_H
#define OPENAFS_FILESYSTEM_STRESS_TEST_FRAMEWORK_FILEOPERATIONS_H

#endif //OPENAFS_FILESYSTEM_STRESS_TEST_FRAMEWORK_FILEOPERATIONS_H
extern char global_buffer[];
extern int file_miss_count;

double addToFile(char path[]);
void overwriteFile(char data[], char path[]);
double read_Sequential(char path[]);
void copyContents(char pathSource[], char pathDest[]);
double renameFile(char pathSource[], int dirNum);
double deleteFile(char pathSource[]);
double createFile(char path[]);