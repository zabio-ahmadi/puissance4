
#ifndef _BOARD_
#define _BOARD_

typedef struct {
    int row;
    int col;
    bool turn; 
    char **matrix;
    int *col_index;
} board; 


// void printInColor(char *color, char *text);

// void flush_input();

void board_alloc(board *_board, int row, int col);
void board_init(board *_board);

void print_board(board *_board);

void add_to_board(board *_board,int col, bool turn);

bool board_is_full(board *_board);
bool column_is_full(board *_board, int col);

void board_destroy(board *_board);

bool board_is_empty(board *_board);

bool check_row(board *_board, int column);

bool check_col(board *_board, int column);

int predit_col_win(board *_board);

int predit_col_loss(board *_board);

bool check_diagonal_forward(board *_board);

bool check_diagonal_backward(board *_board);

bool check_backward_diagonal(board *_board, int column);

bool check_forward_diagonal(board *_board, int column);

bool check_win(board *_board, int column);

#endif