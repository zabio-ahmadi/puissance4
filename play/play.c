
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../board/board.h"
#include "../helpers/helpers.h"
#include "play.h"


void play_agaist_random(board *_board, int col, bool turn){

    
}

// void play_against_ai();


void play_tow_player(board *_board, int col, bool turn){
  
    while(true){

        int column;
        
        scanf("%d", &column);

        // printf("%d\n", column - 1);

        // check column number to be correct 
        if((column-1) < 0 || (column - 1) >= col ){
            printf("Index must be between 1 and %d \n", col);
            continue; 
        }

        // check if the column is full
        if(column_is_full(_board, column)){
            printf("Column %d is full. Please enter another column.", column);
            continue;
        }

        add_to_board(_board,column,turn);
        print_board(_board);

        if(check_win(_board, column)){
            if(turn ==  false){
                printf("Player one won!\n");
            }else {
                printf("Player two won!\n");
            }
            break;
        }

        // change the turn 
        turn = !turn; 

        // if we have no winner and the board is full -> it is a draw 
        if(board_is_full(_board)){
            printf("It is a draw.\n");
            return;
            break;
        }

        flush_input();
        
    }    
}