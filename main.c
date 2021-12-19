#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "./board/board.h"
#include "./helpers/helpers.h"
#include "./play/play.h"

int main(int argc, char **argv){


    
   
   
    int mod = atoi(argv[1]);
    int row = atoi(argv[2]);
    int col = atoi(argv[3]);

    //if(argc <=3 || row <= 3 || col <= 3)
    if(argc <= 3){
        invalid_param(argc, argv);
        return EXIT_FAILURE;
    }

    board _board; 
    
    board_alloc(&_board,row,col);
    board_init(&_board); 
 
    printf("Board size is %dx%d (rows x col)\n", row, col);  
    print_board(&_board);
   
    bool turn = _board.turn;


    switch (mod){
    case 1:
        play_agaist_random(&_board, col, turn);
        break;
    // case 2:
    //     play_against_ai(&_board, row, col, turn);
    //     break;
    case 3:
        play_tow_player(&_board, col, turn);
        break;

    default:
        invalid_param(argc, argv);
        break;
    }
    
    board_destroy(&_board);
}