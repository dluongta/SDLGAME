#include "Board.h"
#include "Extension.h"

Board::Board()
{
	std::vector<int> input = readNumberListFromFile(inputFile[rand() % numberOfInputFile]);
	int index = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			arr[i][j].set_val(input[index]);
			index++;
		}
	}
	index = 0;
	arr[2][2].set_watered(1);

}
Board::~Board()
{

}
void Board::Show_Board(SDL_Surface* des)
{
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j < 4; j++)
		{	
			arr[i][j].update();
			arr[i][j].LoadImg(s[arr[i][j].get_val()].c_str());
			arr[i][j].SetRect(i * HEIGHT_CELL, j * WIDTH_CELL, WIDTH_CELL, HEIGHT_CELL);
			arr[i][j].Show(des);
		}
	}
}
bool Board::CheckBoard()
{
	bool ok = true;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (arr[i][j].get_watered() == 0) ok = false;
		}
	}
	return ok;
	
}
void Board::HandleInputAction(SDL_Event events)
{
	if (events.type == SDL_MOUSEBUTTONDOWN)
	{

		if (events.button.button == SDL_BUTTON_LEFT || events.button.button == SDL_BUTTON_RIGHT)
		{
			int x_loc = events.button.x / HEIGHT_CELL; 
			int y_loc = events.button.y / WIDTH_CELL;
			arr[x_loc][y_loc].HandleInputAction(events);
			arr[x_loc][y_loc].Show(g_screen);
			SDL_Delay(100);

		}
		
	}
	else if (events.type == SDL_KEYDOWN)
	{
		if (events.key.keysym.sym == SDLK_ESCAPE)
		{
			return;
		}
	}
}
void Board::convert()
{
	std::pair<int, int> source = std::make_pair(2, 2);
	std::vector< int > dx = { 1, -1, 0, 0 };
	std::vector< int > dy = { 0, 0, -1, 1 };
	memset(check, false, sizeof check);
	bool  direct[18][4] =
	{ {1, 0, 0, 0},
	{0, 0, 0, 1},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 1, 0, 1},
	{0, 1, 1, 0},
	{1, 0, 1, 0},
	{1, 0, 0, 1},
	{1, 1, 1, 0},
	{1, 0, 1, 1},
	{1, 1, 0, 1},
	{0, 1, 1, 1},
	{1, 1, 0, 0},
	{0, 0, 1, 1},
	{1, 1, 1, 0},
	{1, 0, 1, 1},
	{1, 1, 0, 1},
	{0, 1, 1, 1}
	};

	std::queue< std::pair< int, int > > q;
	//TODO : parameterize
	q.push(source);
	check[source.first][source.second] = true;
	//BFS
	while (!q.empty()) {
		std::pair< int, int > current_cell = q.front();
		q.pop();

		for (int dir = 0; dir < 4; dir++) {
			const int value = arr[current_cell.first][current_cell.second].get_val() % 18;
			std::pair< int, int > new_cell;
			if (direct[value][dir]) {
				new_cell.first = current_cell.first + dx[dir];
				new_cell.second = current_cell.second + dy[dir];

				if (new_cell.first >= 0 && new_cell.first < 4 && new_cell.second >= 0 && new_cell.second < 4)
				{
					int new_val = arr[new_cell.first][new_cell.second].get_val() % 18;
					if (!direct[new_val][dir ^ 1])
						continue;
					if (check[new_cell.first][new_cell.second])
						continue;
					q.push(new_cell);
					check[new_cell.first][new_cell.second] = true;
				}

			}
		}
	}

	//Update water of each cell
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (check[i][j])
				arr[i][j].set_watered(true);
			else
				arr[i][j].set_watered(false);
}
int Board::score()
{
	int score = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (arr[i][j].get_watered())
				score++;
	return score;
}
