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
#include <pthread.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>

FILE *file;
int c;
bool check = false;
int row ;
int column;
int board[9][9];


void loadFile(){
    file = fopen("puzzle.txt", "r");
    if (file != NULL) {
		for (int row = 0; row < 9; row++) { // loop for each row
			for (int col = 0; col < 9; col++) {
				fscanf(file, "%d ", &board[row][col]);
			}
		}
	} else {
		printf("Could not open file\n");
	}
	fclose(file);

}
void checkColumn(){

}
void checkRow(){

}
void checkSubGrid(){

}
void checkSudoku(){

}
int main()
{
   row = 0;
   column = 0;
   
    loadFile();

   
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            printf("%d", board[x][y]);
            printf(" ");
        }
        printf("\n");
    }
}

