#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "../helpers/helpers.h"


void board_alloc(board *_board, int row, int col){

    _board->row = row; 
    _board->col = col; 

    _board->matrix = malloc( row * sizeof(char *));
    _board->col_index = malloc(col * sizeof(int));

    for(int i = 0; i < row; i++){
        // size of char is 8 
        _board->matrix[i] = malloc(col * 8);
    }
}

void board_init(board *_board){
    _board->turn = false; // first player

    for (int i = 0; i < _board->col; i++)
    {
        _board->col_index[i] = _board->row;
    }
}

  
void print_board(board *_board){
    // row 2n + 1
    for (int i = 0; i < (2 * _board->row + 1); i++){
        // col 2n + 1 
        for (int j = 0; j < (2 * _board->col + 1); j++)
        {
            if(i == 0){
                if(j == 0){
                printf("┌");
                continue;

                }else if(j == (2*_board->col)){
                    printf("┐");
                    continue;
                }
            
                else if(j % 2 == 1){
                    printf("─");
                }

                else if(j % 2 == 0){
                    printf("┬");
                }

            }else if(i == (2 * _board->row)){

                if(j == 0){
                printf("└");
                continue;

                }else if(j == (2 * _board->col)){
                    printf("┘");
                    continue;
                }
                else if(j % 2 == 1){
                    printf("─");
                }

                else if(j % 2 == 0){
                    printf("┴");
                }

            }     
            else {

                if(i % 2 == 1){

                    if(j == 0 || j == (2 * _board->col)){
                        printf("│");
                    }else {
                        if(j % 2 == 0){
                            printf("│");
                        }else {                          
                            if((int)_board->matrix[i/2][j/2] > 65){

                                printf("%c", _board->matrix[i/2][j/2]);
                                

                            }else {
                                printf(" ");
                            }
                        }
                    }
                }else {
                    if(j == 0){
                        printf("├");
                    }else if (j == (2 * _board->col)){
                        printf("┤");
                    }else if(j % 2 == 0){
                        printf("┼");
                    }else {
                        printf("─");
                    }
                }

            }
        } 
        printf("\n"); 
    }

    for(int i = 1; i <= _board->col; i++){
        if(i == 1)
            printf(" %d ", i % 10);
        else if(i + 1 > _board->col)
            printf("%d", i % 10);
        else
            printf("%d ", i % 10);
    }
    printf("\n");

   
    
}


void add_to_board(board *_board,int col, bool turn){
    int column = col -1;
    char val = (turn)? 'O': 'X'; // player one starts with 'X' 
    _board->col_index[column]--;
    _board->matrix[_board->col_index[column]][column] = val; 
    

}

bool board_is_full(board *_board){

    int somme = 0;
    for (int i = 0; i < _board->col; i++)
    {
       somme+=_board->col_index[i];
    }
    return (somme == 0)? true:false;
   
}

bool column_is_full(board *_board, int col){

    return (_board->col_index[col - 1] == 0)? true: false; 
}

void board_destroy(board *_board){

    for (int i = 0; i < _board->row; i++){
        free(_board->matrix[i]);
    }
    free(_board->col_index);
    
    free(_board->matrix);
}


bool board_is_empty(board *_board){

    bool is_empty = true; 
    for(int i = 0; i < _board->col; i++){

        // see if column is full
        if(_board->col_index[i] != _board->row - 0){
            is_empty = false;
        }
    }
    return is_empty;
}


bool check_row(board *_board, int column){
    
    // bool result = false;
    int row =  _board->col_index[column -1];
    // int col = column - 1;
    
    int x_count = 0; 
    int o_count = 0; 
    
    for(int i = 0; i < _board->col; i++){

         if(_board->matrix[row][i] == 'O'){
            o_count++;
            x_count = 0; 
        }
        if(_board->matrix[row][i] == 'X'){
            x_count++;
            o_count = 0; 
        }

        if(x_count == 4 || o_count == 4){
            return true; 
        }
    }      

    return false; 
}


bool check_col(board *_board, int column){

    // bool result = false;
    int col = column - 1;

    int x_count = 0; 
    int o_count = 0; 

    for (int i = _board->row -1; i >= 0; i--){

        if(_board->matrix[i][col] == 'O'){
            o_count++;
            x_count = 0; 
        }
        if(_board->matrix[i][col] == 'X'){
            x_count++;
            o_count = 0; 
        }

        if(x_count == 4 || o_count == 4){
            return true; 
        }   
    }
    return false;


}


int predit_col_win(board *_board){
   
    //predict forward diagonal (forward diagonal have priority)
    for (int col = 0; col < _board->col; col++){

        for(int row = _board->row -1; row >= 0; row--){

            int x_count = 0; 
            int o_count = 0;    
            int cols = col; 
            int rows = row; 
            // look up 
            while(cols <= _board->col && rows >= 0){

                if(_board->matrix[rows][cols] == 'O'){
                    o_count++;
                    x_count = 0; 
                }
                if(_board->matrix[rows][cols] == 'X'){
                    x_count++;
                    o_count = 0; 
                }   

                if(( o_count == 3) && ((int)_board->matrix[rows-1][cols +1] < 65 && (int)_board->matrix[rows][cols+1] > 65 )){
                    return cols + 1;
                    // break;
                }
                rows--;
                cols++;
            }
        }
    }

    //predict col 
    for (int col = 0; col < _board->col; col++){
        int x_count = 0; 
        int o_count = 0; 
        for(int row = _board->row -1; row >= 0; row--){

            if(_board->matrix[row][col] == 'O'){
                o_count++;
                x_count = 0; 
            }
            if(_board->matrix[row][col] == 'X'){
                x_count++;
                o_count = 0; 
            }   
        }

        if(o_count == 3){
            return col; 
        }
    }


    // predict rows 
    for(int row = 0; row < _board->row; row++){
    
        for (int col = 0; col < _board->col; col++){

            int o_count = 0; 

            if(_board->matrix[row][col] < 65){

                int column = col - 1;
                //check left  
                while(column >= 0){

                    if(_board->matrix[row][column] == 'O'){
                        o_count++;
                    }
                    else {
                        break;
                    }

                    if(o_count == 3){
                        return col; 
                    }
                    column--;
                }

                column = col + 1; 
                while(column < _board->col){

                    if(_board->matrix[row][column] == 'O'){
                        o_count++;
                    }
                    else {
                        break;
                    }

                    if(o_count == 3){
                        return col; 
                    }
                    column++;
                }  
            }

        }
    }  
    
    return -1;

}




int predit_col_loss(board *_board){
    //predict columns 
    for (int col = 0; col < _board->col; col++){
        int x_count = 0; 
        int o_count = 0; 
        for(int row = _board->row -1; row >= 0; row--){

            if(_board->matrix[row][col] == 'O'){
                o_count++;
                x_count = 0; 
            }
            if(_board->matrix[row][col] == 'X'){
                x_count++;
                o_count = 0; 
            }   
        }
        if(x_count == 3){
            return col; 
        }
    }


    // predict rows 
    for(int row = _board->row -1; row >= 0; row--){
    
        for (int col = 0; col < _board->col; col++){

            int x_count = 0; 
            int o_count = 0; 

            if(_board->matrix[row][col] < 65){

                
                int column = col - 1;
                //check left  
                while(column >= 0){

                    if(_board->matrix[row][column] == 'O'){
                        o_count++;
                        x_count = 0; 
                    }
                    else if(_board->matrix[row][column] == 'X'){
                        x_count++;
                        o_count = 0; 
                    }
                    else {
                        break;
                    }

                    if((x_count == 3) && (row+1 < _board->row) && ((int)_board->matrix[row+1][col] > 65)){
                        return col; 
                    }
                    column--;
                }


                 //check right
                 column = col + 1;  
                while(column < _board->col){

                    if(_board->matrix[row][column] == 'O'){
                        o_count++;
                        x_count = 0; 
                    }
                    else if(_board->matrix[row][column] == 'X'){
                        x_count++;
                        o_count = 0; 
                    }
                    else {
                        break;
                    }

                    // if((x_count == 3 || o_count == 3) && (row+1 < _board->row) && ((int)_board->matrix[col][row+1] > 65)){
                    //     return col; 
                    // }

                    if((x_count == 3)&& (row+1 < _board->row) && ((int)_board->matrix[row+1][col] > 65)){
                        return col; 
                    }
                    column++;
                }
                
            }

        }
    }  
    


    // predict forward diagonal 
    for (int col = 0; col < _board->col; col++){

        for(int row = _board->row -1; row >= 0; row--){

            int x_count = 0; 
            int o_count = 0;    
            int cols = col; 
            int rows = row; 
            // look up 
            while(cols <= _board->col && rows >= 0){

                if(_board->matrix[rows][cols] == 'O'){
                    o_count++;
                    x_count = 0; 
                }
                if(_board->matrix[rows][cols] == 'X'){
                    x_count++;
                    o_count = 0; 
                }   

                if((x_count == 3 || o_count == 3) && ((int)_board->matrix[rows-1][cols +1] < 65 && (int)_board->matrix[rows][cols+1] > 65 )){
                    return cols + 1;
                    // break;
                }
                rows--;
                cols++;
            }
        }
    }
    
    return -1;

}



bool check_diagonal_forward(board *_board){
    bool result  = false; 
    //check forward diagonal 
    int o_count_d = 0; 
    int x_count_d = 0; 
    for (int row = 0; row < _board->row; row++){

        for (int col = 0; col < _board->col; col++){
            //pour avoir exactment 4 x || 4 o 
            if( row + col == 3){

                if(_board->matrix[row][col] == 'O'){
                    o_count_d++;
                    x_count_d = 0; 
                }

                if(_board->matrix[row][col] == 'X'){
                    x_count_d++;
                    o_count_d = 0; 
                }
            }

        }

        if(o_count_d == 4 || x_count_d == 4){
            result = true; 
            break; 

        }
    }

    return result;
}

bool check_diagonal_backward(board *_board){

    bool result = false; 
    int o_count_d = 0; 
    int x_count_d = 0; 
    // check backward diagonal
    for (int row = 0; row < _board->row; row++){
        
        for (int col = 0; col < _board->col; col++){
            
            if( (col - row ) == 0){

                if(_board->matrix[row][col] == 'O'){
                    o_count_d++;
                    x_count_d = 0; 
                }

                if(_board->matrix[row][col] == 'X'){
                    x_count_d++;
                    o_count_d = 0;

                } 
            }
            
        }
        if(o_count_d == 4 || x_count_d == 4){
            result = true; 
            break; 

        }
    }
    
    return result; 
}


bool check_backward_diagonal(board *_board, int column){
   
    // bool result = false;
    int row =  _board->col_index[column -1];
    int col = column -1;

    int x_count = 0; 
    int o_count = 0; 
    // look up 
    while(row >= 0 && col >= 0){

        if(_board->matrix[row][col] == 'O'){
            o_count++;
            x_count = 0; 
        }
        if(_board->matrix[row][col] == 'X'){
            x_count++;
            o_count = 0; 
        }

        if(x_count == 4 || o_count == 4){
            return true; 
        } 

    row--;
    col--;
    }

    row =  _board->col_index[column -1];
    col = column -1;
    row++;
    col++;

    //look down 
    while(row < _board->row && col < _board->col){

        if(_board->matrix[row][col] == 'O'){
            o_count++;
            x_count = 0; 
        }
        if(_board->matrix[row][col] == 'X'){
            x_count++;
            o_count = 0; 
        }

        if(x_count == 4 || o_count == 4){
            return true; 
        } 

        col++;
        row++;
    }

    

    return false; 

}

bool check_forward_diagonal(board *_board, int column){
    // bool result = false;
    int row =  _board->col_index[column -1];
    int col = column -1;
    int x_count = 0; 
    int o_count = 0; 

    // look down
    while(col >= 0 && row < _board->row){

        if(_board->matrix[row][col] == 'O'){
            o_count++;
            x_count = 0; 
        }
        if(_board->matrix[row][col] == 'X'){
            x_count++;
            o_count = 0; 
        }

        if(x_count == 4 || o_count == 4){
            return true; 
        } 
        row++;
        col--;
    }

    // look up 
    row =  _board->col_index[column -1];
    col = column -1;
    
    while(col <= _board->col && row >= 0){

        if(_board->matrix[row][col] == 'O'){
            o_count++;
            x_count = 0; 
        }
        if(_board->matrix[row][col] == 'X'){
            x_count++;
            o_count = 0; 
        }

        if(x_count == 5 || o_count == 5){
            return true; 
        } 
        row--;
        col++;
    }

    return false;
}

bool check_win(board *_board, int column){

    if(check_col(_board,column)){
        return true; 
    }

    else if(check_row(_board,column)){
        return true; 
    }

    else if(check_forward_diagonal(_board,column)){
        return true; 
    }

    else if(check_backward_diagonal(_board, column)){
        return true; 
    }
    else 
        return false;
    
}

