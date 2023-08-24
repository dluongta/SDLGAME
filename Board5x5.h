#ifndef BOARD_5x5_H_
#define BOARD_5x5_H_

#include "CommonFunction.h"
#include "Cell.h"
#include<iostream>
#include <queue>
class Board5x5
{
public:
	Board5x5();
	~Board5x5();
	void Show_Board(SDL_Surface* des);
	bool CheckBoard();
	void HandleInputAction(SDL_Event events);
	void convert();
	int score();

private:
	Cell arr[5][5];
	bool check[5][5];
	bool direct[18][4];


};
#endif

