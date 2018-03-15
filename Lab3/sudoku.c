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
int rowChecks[9];
int columnChecks[9];
int gridChecks[9];
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
    for(int col = 0; col < 9; col++){
        int counter[9] = {0};
		for(int row = 0; row < 9; row++){
			if(board[row][col] != 0){
				counter[board[row][col]-1] += 1;
			}
		}
		columnChecks[col] = 1;
		for(int i = 0; i < 9; i++){
			if(counter[i] > 1){
				columnChecks[col] = 0;
				break;
			}
		}
	}
	return NULL;

}
void checkRow(){
    for(int row = 0; row < 9; row++){
		int counter[9] = {0};
		for(int col = 0; col < 9; col++){
			if(board[row][col] != 0){
				counter[board[row][col]-1] += 1;
			}
		}
		rowChecks[row] = 1;
		for(int i = 0; i < 9; i++){
			if(counter[i] > 1){
				rowChecks[row] = 0;
				break;
			}
		}
	}
	return NULL;

}
int checkSubGrid(int rowNum, int column){

    int counter[9] = {0};
	for(int row = rowNum; row < rowNum+3; row++){
		for(int col = column; col < column+3; col++){
			if(board[row][col] != 0){
				counter[board[row][col]-1] += 1;
			}
		}
	}
	for(int i = 0; i < 9; i++){
		if(counter[i] > 1){
			return 0;
		}
	}
	return 1;

}
void* validateGrids () {
	for (int row = 0; row < 9; row+=3) {
		for (int col = 0; col < 9; col+=3) {
			gridChecks[row+col/3] = checkSubGrid(row, col);
		}
	}
	return NULL;
}
void checkSudoku(){
    pthread_t columns, rows, grids;

	// create threads and execute thread functions
	pthread_create(&columns, NULL, checkColumn, NULL);
	pthread_create(&rows, NULL, checkRow, NULL);
	pthread_create(&grids, NULL, checkSubGrid, NULL);

	pthread_join(columns, NULL);
	pthread_join(rows, NULL);
	pthread_join(grids, NULL);

	for (int i = 0; i < 9; i++) {
		if (columnChecks[i] == 0)
			return 0;
		if (rowChecks[i] == 0)
			return 0;
		if (gridChecks[i] == 0)
			return 0;
	}
	return 1;
}

int main()
{
   
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

