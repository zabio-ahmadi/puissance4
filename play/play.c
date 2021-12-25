
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../board/board.h"
#include "../helpers/helpers.h"
#include "play.h"

void play_against_smart_ai2(board *_board, int col, bool turn){
    // la série 2 5 3
    srand(0);
    while(true){

       // user input 
       printf("Column number? (starts at 1):\n"); 
        int column;
        int col_to_win = -1;
        int col_to_loss = -1;
        scanf("%d", &column);
        if((column-1) < 0 || (column - 1) >= col ){
            printf("Index must be between 1 and %d \n", col);
        }
        else if(column_is_full(_board, column)){
            printf("Column %d is full. Please enter another column.\n", column);

        }else {
            
            add_to_board(_board,column,false);
            print_board(_board);
            if(check_win(_board, column)){
                if(turn ==  false){
                    printf("Player one won!\n");
                }else {
                    printf("Computer won!\n");
                }
                break;
            }

            if(board_is_full(_board)){
                printf("It is a draw.\n");
                break;
            }


            col_to_win = predit_col_win(_board);
            col_to_loss = predit_col_loss(_board);  

            // change the turn 
            turn = !turn; 
            
           
            if(col_to_win != -1){

                column = col_to_win + 1; 
            }
            else if(col_to_loss != -1){
                column = col_to_loss + 1; 
            }

            if(col_to_win == -1 && col_to_loss == -1){
                // generate random 
                column = (rand() % _board->col) + 1;
            }


            if(column_is_full(_board, column)){
                printf("Column %d is full. Please enter another column.\n", column);
                
            }else {
                add_to_board(_board,column, true);
                print_board(_board);

                if(check_win(_board, column)){
                    if(turn ==  false){
                        printf("Player one won!\n");
                    }else {
                        printf("Computer won!\n");
                    }
                    break;
                }

                // change the turn 
                turn = !turn; 

                // if we have no winner and the board is full -> it is a draw 
                if(board_is_full(_board)){
                    printf("It is a draw.\n");
                    break;
                }
            }

        }
    }
}



void play_agaist_random_ai(board *_board, int col, bool turn){

    // la série 2 5 3
    srand(0);  
    while(true){
        printf("Column number? (starts at 1):\n");
        int column;
        scanf("%d", &column);

        // check column number to be correct 
        if((column-1) < 0 || (column - 1) >= col ){
            printf("Index must be between 1 and %d \n", col);
        }
        // check if the column is full
        else if(column_is_full(_board, column)){
            printf("Column %d is full. Please enter another column.", column);
    
        }else {
            add_to_board(_board,column,false);
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
                break;
            }
        }


        // machine input
        int random_column = (rand() % _board->col) + 1;
        
        if(column_is_full(_board, random_column)){
            printf("Column rand %d is full. Please enter another column.", random_column);
        }else {
            add_to_board(_board,random_column, true);
            print_board(_board);

            if(check_win(_board, random_column)){
                if(turn ==  false){
                    printf("Player one won!\n");
                }else {
                    printf("Computer won!\n");
                }
                break;
            }

            // change the turn 
            turn = !turn; 

            // if we have no winner and the board is full -> it is a draw 
            if(board_is_full(_board)){
                printf("It is a draw.\n");
                break;
            }
        }
    }
    
}

void play_tow_player(board *_board, int col, bool turn){
    
    while(true){
        printf("Column number? (starts at 1):\n");
        int column;
        scanf("%d", &column);
       
        // check column number to be correct 
        if((column-1) < 0 || (column - 1) >= col ){
            printf("Index must be between 1 and %d \n", col);
        }
        // check if the column is full
        else if(column_is_full(_board, column)){
            printf("Column %d is full. Please enter another column.", column);
    
        }
        else{

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
            
                break;
            }
            // flush_input();
            //cat testbed/rand_ai/test4.in | ./puissance4 3 6 7 >diff.txt
        
        }
        
        
    }    



}