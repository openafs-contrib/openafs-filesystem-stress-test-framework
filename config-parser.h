//
// Created by arniejhingran on 7/24/22.
//

#ifndef OPENAFS_FILESYSTEM_STRESS_TEST_FRAMEWORK_CONFIG_PARSER_H
#define OPENAFS_FILESYSTEM_STRESS_TEST_FRAMEWORK_CONFIG_PARSER_H

#endif //OPENAFS_FILESYSTEM_STRESS_TEST_FRAMEWORK_CONFIG_PARSER_H

extern int cores;
extern int write_chace;
extern int copy_chance;
extern int delete_chance;
extern int rename_chance;
extern int time_of_test;
extern int directories;
extern int files;

void parseConfig();