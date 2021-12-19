#include "../board/board.h"
#ifndef _PLAY_
#define _PLAY_

void play_agaist_random(board *_board, int col, bool turn);

void play_against_ai(board *_board, int row, int col, bool turn);

void play_tow_player(board *_board, int col, bool turn);

#endif