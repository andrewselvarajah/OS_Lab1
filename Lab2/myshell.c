/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2017, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include "utility.h"
#include "myshell.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256

// Put global environment variables here

// Define functions declared in myshell.h here
void searchDir(char *pwd, char *arg);
void printDir();

int main(int argc, char *argv[])
{
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };
    char pwd[BUFFER_LEN] = "";//for the current directory
    char shell[BUFFER_LEN] = { 0 };
    char *token;
    char *input;
    int counter;
    char *argpoint;


    // Parse the commands provided using argc and argv

    // Perform an infinite loop getting command input from users
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        counter = 0;
        const char delim[2] = " ";
        // Perform string tokenization to get the command and argument
        //printf("%s", buffer);
        //buffer[BUFFER_LEN-1] = "\0";
        token = strtok(buffer, "\n");
        token = strtok(buffer, " ");
        strcpy(command, token);

        
        while(token != NULL ) {
            strcpy(arg, token);
            token = strtok(NULL, " ");
            counter  = counter + 1;
        }
        if(strcmp(command, arg) == 0 && counter < 2){
            strcpy(arg, "");
        }
        input = getcwd(pwd, BUFFER_LEN);
        *pwd = *input;


            
        

        // Check the command and execute the operations for each command
        // cd command -- change the current directory
        if (strcmp(command, "cd") == 0)
        {
            if(strcmp(arg, "") == 0){
                printf("Not a directory\n");
                printf("cd 'Directory name'\n");
            }
            else{
                searchDir(pwd, arg);
                printf("%s\n", arg);
            }
            // your code here
        }
        //outputs current working directory
        else if (strcmp(command, "pwd") == 0)
        {
            input = getcwd(pwd, BUFFER_LEN);
            *pwd = *input;
            printf("%s\n", pwd);

        }
        //lists all files within current directory
         else if (strcmp(command, "dir") == 0)
        {
            printDir(pwd);
        }
        //lists all relevent variables
        else if (strcmp(command, "environ") == 0)
        {
            input = getcwd(pwd, BUFFER_LEN);
            printf("pwd: %s\n", input);
            printf("shell: %s\n", shell);

        }

        
        // quit command -- exit the shell
        else if (strcmp(command, "quit") == 0)
        {
            return EXIT_SUCCESS;
        }
        //help command
        else if (strcmp(command, "help") == 0)
        {
            FILE *f;
            char c, filename[100] = "readme";

            f = fopen(filename, "r");
            if(f == NULL)
            {
                printf("no file");
                exit(0);
            }
            c = fgetc(f);
            while (c !=EOF)
            {
                printf("%c", c);
                c = fgetc(f);
            }

            fclose(f);

        }

        // Unsupported command
        else
        {
            fputs("Unsupported command, use help to display the manual\n", stderr);
        }
           
    }
    return EXIT_SUCCESS;
}
//prints all files within the current directory
void printDir(char *pwd){
     DIR *directory = opendir(pwd);
     struct dirent *dire = NULL;
     if(directory == NULL){
         printf("Directory does not exist\n");
     }
     else{
        while(NULL != (dire = readdir(directory)) )
        {
            printf(" [%s] ",dire->d_name);
        }
        printf("\n");
     }
     closedir(directory);
     

 }
 //searches through the list of files and checks if the argument is 
 //one of the files for cd
 //todo: fix check in case file is not within directory
 //check if argument is a directory
 //update pwd properly so that new directory is current
 void searchDir(char *pwd, char *arg){
     DIR *directory = opendir(pwd);
     struct dirent *dire = NULL;
     if(directory == NULL){
         printf("Directory does not exist\n");
     }
     else{
        while(NULL != (dire = readdir(directory)) )
        {
            if(strcmp(arg, dire->d_name) == 0){
                //*pwd = pwd + "/" + arg;  //gives an error
            }
            else{

            }
            printf(" [%s] ",dire->d_name);
        }
        printf("\n");
     }

 }
