#ifndef BOARD_H_
#define BOARD_H_
#include "CommonFunction.h"
#include "Cell.h"
#include<iostream>
#include <queue>
class Board
{
	public:
		Board();
		~Board();
		void Show_Board(SDL_Surface* des);
		bool CheckBoard();
		void HandleInputAction(SDL_Event events);
		void convert();
		int score();
		
	private:
		Cell arr[4][4];
		bool check[4][4];
		bool direct[18][4];

		
};
#endif

