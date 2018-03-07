/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2017, <Andrew Selvarajah, Mark ...>
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
    // cwd buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };
    char pwd[BUFFER_LEN] = "";//for the current directory
    char shell[BUFFER_LEN] = { 0 };
    char *token;//holds seperate tokens
    char *cwd;//temp holds the cwd
    int counter;//cehcks number of arguments


    // Parse the commands provided using argc and argv
    cwd = getcwd(pwd, BUFFER_LEN);
    *pwd = *cwd;
    printf("shell=");
    printf("%s", pwd);
    printf("/myshell:");


    // Perform an infinite loop getting command cwd from users
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
            cwd = getcwd(pwd, BUFFER_LEN);
            *pwd = *cwd;
            printf("%s\n", pwd);

        }
        //lists all files within current directory
         else if (strcmp(command, "dir") == 0)
        {
            printDir(pwd);
        }
        //clears screen
        else if (strcmp(command, "clr") == 0)
        {
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        }
        //lists all relevent variables
        else if (strcmp(command, "environ") == 0)
        {
            cwd = getcwd(pwd, BUFFER_LEN);
            printf("pwd: %s\n", cwd);
            printf("shell: %s\n", shell);

        }
        //prints argument
        else if (strcmp(command, "echo") == 0)
        {
            printf("%s\n", arg);
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
    printf("shell=");
    printf("%s", pwd);
    printf("/myshell:");
           
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
