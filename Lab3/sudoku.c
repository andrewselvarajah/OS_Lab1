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


void loadFile();
void checkColumn();
void checkRow();
int checkSubGrid(int rowNum, int column);
void* validateGrids();
void solve_square(int row, int col);
void navigate(int row, int col);
void printBoard();
void writeToFile (char fileName[]);


int main()
{
   
    loadFile();
	bool valid = true;

    printBoard();
	checkSudoku();
	for(int i = 0; i < 9; i++){
		if(columnChecks[i] == 0 || rowChecks[i] == 0 || gridChecks[i] == 0){
			valid = false;
			break;
		}
	}
	if(valid){
		puts("Unsolved Puzzle:");
		printBoard();
		solve_square(0,0);
		if(check){
			puts("Solved Puzzle:");
			printBoard();
		} else {
			puts("Sudoku puzzle is unsolvable.");
		}
	} else {
		puts("Puzzle is not a valid sudoku.");
	}
}
void writeToFile (char fileName[]) {
	FILE *file = fopen(fileName, "w");

	if (file != NULL) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (j != 8)
					fprintf(file, "%d ", board[i][j]);
				else
					fprintf(file, "%d", board[i][j]);
			}
			fprintf(file, "\n");
		}
	} else {
		printf("File: %s could not be opened for writing", fileName);
		return;
	}
}
void printBoard(){
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
}
int checkSudoku(){
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
void solve_square(int row, int col) {
	if(row>8){
		check = true;
		return;
	}
	if(board[row][col] != 0){
		navigate(row, col);
	} else {
		for(int i = 1; i <= 9; i++){
			board[row][col] = i;
			checkSudoku();
			if(columnChecks[col] != 1 || rowChecks[row] != 1
				|| gridChecks[(row/3)*3+col/3] != 1){
				board[row][col] = 0;
			} else {
				navigate(row, col);
			}
			if(check)
				return;
		}
		board[row][col] = 0;
	}
}
void navigate(int row, int col){
	if(col<8)
		solve_square(row, col+1);
	else
		solve_square(row+1, 0);
}


