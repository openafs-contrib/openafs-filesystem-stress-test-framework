//
// Created by arniejhingran on 7/13/22.
//

#ifndef OPENAFS_FILESYSTEM_STRESS_TEST_FRAMEWORK_FILEOPERATIONS_H
#define OPENAFS_FILESYSTEM_STRESS_TEST_FRAMEWORK_FILEOPERATIONS_H

#endif //OPENAFS_FILESYSTEM_STRESS_TEST_FRAMEWORK_FILEOPERATIONS_H
extern char global_buffer[];
extern int file_miss_count;

void addToFile(char path[]);
void overwriteFile(char data[], char path[]);
double readIntoBuffer(char path[]);
void copyContents(char pathSource[], char pathDest[]);
void renameFile(char pathSource[], int dirNum);
void deleteFile(char pathSource[]);