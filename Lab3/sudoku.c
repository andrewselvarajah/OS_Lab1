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
#include <stdbool.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>

int main()
{
    FILE *file;
    int c;
    bool check = false;
    int counter = 0;
    int counter2 = 0;
    file = fopen("puzzle.txt", "r");
    int board[9][9];

    if (file)
    {
        while (((c = getc(file)) != EOF))
        {
            if (check == false)
            {

                if (counter == 9)
                {
                    counter2++;
                    counter = 0;
                }
                board[counter][counter2];
                printf("%d\n", board[counter][counter2]);
                counter++;
                check = true;
            }
            else if (check == true)
            {
                check = false;
            }
        }
    }
    /*for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            printf("%d", board[x][y]);
        }
        printf("\n");
    }*/
}
