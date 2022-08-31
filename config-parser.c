//
// Created by arniejhingran on 7/24/22.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cores;
int write_chance;
int copy_chance;
int delete_chance;
int rename_chance;
int time_of_test;
int directories;
int files;
int read_f;
int create_chance;

/**
 * parses the config file and sets global variables
 */
void parseConfig(){
    FILE* config = fopen("config.cfg", "r");
    char config_line[25];
    if(config == NULL) fprintf(stderr, "Config file missing");
    else{
        while(fgets(config_line, sizeof(config_line), config) != NULL){
            char* token = strtok(config_line, "=");
            if(strstr(token, "cores")!=NULL){
                token = strtok(NULL, "=");
                cores = atoi(token);
            }
            else if(strstr(token, "write")!=NULL){
                token = strtok(NULL, "=");
                write_chance = atoi(token);
            }
            else if(strstr(token, "copy")!=NULL){
                token = strtok(NULL, "=");
                copy_chance = atoi(token);
            }
            else if(strstr(token, "delete")!=NULL){
                token = strtok(NULL, "=");
                delete_chance = atoi(token);
            }
            else if(strstr(token, "rename")!=NULL){
                token = strtok(NULL, "=");
                rename_chance = atoi(token);
            }
            else if(strstr(token, "time")!=NULL){
                token = strtok(NULL, "=");
                time_of_test = atoi(token);
            }
            else if(strstr(token, "directories")!=NULL){
                token = strtok(NULL, "=");
                directories = atoi(token);
            }
            else if(strstr(token, "files")!=NULL){
                token = strtok(NULL, "=");
                files = atoi(token);
            }
            else if(strstr(token, "read_f")!=NULL){
                token = strtok(NULL, "=");
                read_f = atoi(token);
            }
            else if(strstr(token, "create")!=NULL){
                token = strtok(NULL, "=");
                create_chance = atoi(token);
            }
            else{
                fprintf(stderr, "config contains unknown key:value pair");
            }

            //token = strtok(NULL, "=");
            //printf("%s", token);
        }

        if(directories%cores != 0) {
            fprintf(stderr, "error in config, num of directories must be divisible by core count");
            exit(1);
        }
        if(read_f>files) {
            fprintf(stderr, "error in config, num of reading operation files greater than total files");
            exit(1);
        }
    }
}

