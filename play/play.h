#include "../board/board.h"
#ifndef _PLAY_
#define _PLAY_

void play_agaist_random_ai(board *_board, int col, bool turn);

void play_against_smart_ai(board *_board, int col, bool turn);

void play_against_smart_ai2(board *_board, int col, bool turn);

void play_tow_player(board *_board, int col, bool turn);

#endif