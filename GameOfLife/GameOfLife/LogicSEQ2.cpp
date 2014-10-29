#include "LogicSEQ2.h"


LogicSEQ2::LogicSEQ2(void)
{
}


LogicSEQ2::~LogicSEQ2(void)
{
}

/*
** Basically brute borce, but pays special (hardcoded)
** attention to the 4 corners and 4 borders, so that the
** rest of the board can be checked even faster.
*/
void LogicSEQ2::runLifeCycle(BoardData& board, unsigned int generations)
{
	unsigned int lengthX = board.sizeX;
	unsigned int lengthY = board.sizeY;
	int countLives = 0;

	for(unsigned int h = 0; h < generations; ++h)
	{

		// --- CALC 4 CORNERS ---

		// TOP LEFT CORNER
		countLives = 0;
		// top left
		countLives += board.BoardFront[lengthY-1][lengthX-1];
		// top
		countLives += board.BoardFront[lengthY-1][0];
		// top right
		countLives += board.BoardFront[lengthY-1][1];
		//center left
		countLives += board.BoardFront[0][lengthX-1];
		//center right
		countLives += board.BoardFront[0][1];
		//bottom left
		countLives += board.BoardFront[1][lengthX-1];
		//bottom center
		countLives += board.BoardFront[1][0];
		//bottom right
		countLives += board.BoardFront[1][1];

		applyLogicForCell(board, 0, 0, countLives);


		// TOP RIGHT CORNER
		countLives = 0;
		// top left
		countLives += board.BoardFront[lengthY-1][lengthX-2];
		// top
		countLives += board.BoardFront[lengthY-1][lengthX-1];
		// top right
		countLives += board.BoardFront[lengthY-1][0];
		//center left
		countLives += board.BoardFront[0][lengthX-2];
		//center right
		countLives += board.BoardFront[0][0];
		//bottom left
		countLives += board.BoardFront[1][lengthX-2];
		//bottom center
		countLives += board.BoardFront[1][lengthX-1];
		//bottom right
		countLives += board.BoardFront[1][0];

		applyLogicForCell(board, 0, lengthX-1, countLives);


		// BOTTOM RIGHT CORNER
		countLives = 0;
		// top left
		countLives += board.BoardFront[lengthY-2][lengthX-2];
		// top
		countLives += board.BoardFront[lengthY-2][lengthX-1];
		// top right
		countLives += board.BoardFront[lengthY-2][0];
		//center left
		countLives += board.BoardFront[lengthY-1][lengthX-2];
		//center right
		countLives += board.BoardFront[lengthY-1][0];
		//bottom left
		countLives += board.BoardFront[0][lengthX-2];
		//bottom center
		countLives += board.BoardFront[0][lengthX-1];
		//bottom right
		countLives += board.BoardFront[0][0];

		applyLogicForCell(board, lengthY-1, lengthX-1, countLives);


		// BOTTOM LEFT CORNER
		countLives = 0;
		// top left
		countLives += board.BoardFront[lengthY-2][lengthX-1];
		// top
		countLives += board.BoardFront[lengthY-2][0];
		// top right
		countLives += board.BoardFront[lengthY-2][1];
		//center left
		countLives += board.BoardFront[lengthY-1][lengthX-1];
		//center right
		countLives += board.BoardFront[lengthY-1][1];
		//bottom left
		countLives += board.BoardFront[0][lengthX-1];
		//bottom center
		countLives += board.BoardFront[0][0];
		//bottom right
		countLives += board.BoardFront[0][1];

		applyLogicForCell(board, lengthY-1, 0, countLives);


		// --- CALC 4 BORDERS ---

		// TOP BORDER
		for(unsigned int j = 1; j < lengthX-1; ++j)
		{
			countLives = 0;
			// top left
			countLives += board.BoardFront[lengthY-1][j-1];
			// top
			countLives += board.BoardFront[lengthY-1][j];
			// top right
			countLives += board.BoardFront[lengthY-1][j+1];
			//center left
			countLives += board.BoardFront[0][j-1];
			//center right
			countLives += board.BoardFront[0][j+1];
			//bottom left
			countLives += board.BoardFront[1][j-1];
			//bottom center
			countLives += board.BoardFront[1][j];
			//bottom right
			countLives += board.BoardFront[1][j+1];

			applyLogicForCell(board, 0, j, countLives);
		}

		// BOTTOM BORDER
		for(unsigned int j = 1; j < lengthX-1; ++j)
		{
			countLives = 0;
			// top left
			countLives += board.BoardFront[lengthY-2][j-1];
			// top
			countLives += board.BoardFront[lengthY-2][j];
			// top right
			countLives += board.BoardFront[lengthY-2][j+1];
			//center left
			countLives += board.BoardFront[lengthY-1][j-1];
			//center right
			countLives += board.BoardFront[lengthY-1][j+1];
			//bottom left
			countLives += board.BoardFront[0][j-1];
			//bottom center
			countLives += board.BoardFront[0][j];
			//bottom right
			countLives += board.BoardFront[0][j+1];

			applyLogicForCell(board, lengthY-1, j, countLives);
		}

		// LEFT BORDER
		for(unsigned int i = 1; i < lengthY-1; ++i)
		{
			countLives = 0;
			// top left
			countLives += board.BoardFront[i-1][lengthX-1];
			// top
			countLives += board.BoardFront[i-1][0];
			// top right
			countLives += board.BoardFront[i-1][1];
			//center left
			countLives += board.BoardFront[i][lengthX-1];
			//center right
			countLives += board.BoardFront[i][1];
			//bottom left
			countLives += board.BoardFront[i+1][lengthX-1];
			//bottom center
			countLives += board.BoardFront[i+1][0];
			//bottom right
			countLives += board.BoardFront[i+1][1];

			applyLogicForCell(board, i, 0, countLives);
		}

		// RIGHT BORDER
		for(unsigned int i = 1; i < lengthY-1; ++i)
		{
			countLives = 0;
			// top left
			countLives += board.BoardFront[i-1][lengthX-2];
			// top
			countLives += board.BoardFront[i-1][lengthX-1];
			// top right
			countLives += board.BoardFront[i-1][0];
			//center left
			countLives += board.BoardFront[i][lengthX-2];
			//center right
			countLives += board.BoardFront[i][0];
			//bottom left
			countLives += board.BoardFront[i+1][lengthX-2];
			//bottom center
			countLives += board.BoardFront[i+1][lengthX-1];
			//bottom right
			countLives += board.BoardFront[i+1][0];

			applyLogicForCell(board, i, lengthX-1, countLives);
		}

		// --- CALC INNER VALUES (all but borders) ---
		for(unsigned int i = 1; i < lengthY-1; ++i)
		{
			for(unsigned int j = 1; j < lengthX-1; ++j)
			{
				countLives = 0;

				// top left
				countLives += board.BoardFront[i-1][j-1];
				// top
				countLives += board.BoardFront[i-1][j];
				// top right
				countLives += board.BoardFront[i-1][j+1];
				//center left
				countLives += board.BoardFront[i][j-1];
				//center right
				countLives += board.BoardFront[i][j+1];
				//bottom left
				countLives += board.BoardFront[i+1][j-1];
				//bottom center
				countLives += board.BoardFront[i+1][j];
				//bottom right
				countLives += board.BoardFront[i+1][j+1];
				
				applyLogicForCell(board, i, j, countLives);
			}
		}
		board.Swap();
	}
}

void LogicSEQ2::applyLogicForCell (BoardData& board, unsigned int y, unsigned int x, int countLives) const
{
	if(countLives < 2)
	{
		board.BoardBack[y][x] = false;
	}
	else if(countLives == 2)
	{
		board.BoardBack[y][x] = board.BoardFront[y][x];
	}
	else if (countLives == 3)
	{
		board.BoardBack[y][x] = true;
	}
	else 
	{
		board.BoardBack[y][x] = false;
	}
}