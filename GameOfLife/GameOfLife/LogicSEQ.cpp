#include "LogicSEQ.h"


LogicSEQ::LogicSEQ(void)
{
}


LogicSEQ::~LogicSEQ(void)
{
}


void LogicSEQ::runLifeCycle(BoardData& board, unsigned int generations)
{
	unsigned int lengthX = board.BoardFront[0].size();
	unsigned int lengthY = board.BoardFront.size();
	int countLives = 0;
	int y_index, x_index;

	for(unsigned int h = 0; h < generations; ++h)
	{
		//printf("%d\n", h+1);
		for(unsigned int i = 0; i < lengthY; ++i)
		{
			for(unsigned int j = 0; j < lengthX; ++j)
			{
				countLives = 0;

				/*
				// check neighbars of each element
				for(int k = -1; k <= 1; ++k)
				{
					// check for y boundary
					y_index = i + k;
					if(y_index == -1)
						y_index = lengthY-1;
					else if(y_index == lengthY)
						y_index = 0;

					for(int l = -1; l <= 1; ++l)
					{
						// check for x boundary
						x_index = j + l;
						if(x_index == -1)
							x_index = lengthX-1;
						else if(x_index == lengthX)
							x_index = 0;

						countLives += board.BoardFront[y_index][x_index];
					}
				}
				countLives -= board.BoardFront[i][j];
				*/

				
				// top left
				countLives += board.BoardFront[(lengthY+i-1)%lengthY][(lengthX+j-1)%lengthX];
				// top
				countLives += board.BoardFront[(lengthY+i-1)%lengthY][j];
				// top right
				countLives += board.BoardFront[(lengthY+i-1)%lengthY][(lengthX+j+1)%lengthX];
				//center left
				countLives += board.BoardFront[i][(lengthX+j-1)%lengthX];
				//center right
				countLives += board.BoardFront[i][(lengthX+j+1)%lengthX];
				//bottom left
				countLives += board.BoardFront[(lengthY+i+1)%lengthY][(lengthX+j-1)%lengthX];
				//bottom center
				countLives += board.BoardFront[(lengthY+i+1)%lengthY][j];
				//bottom right
				countLives += board.BoardFront[(lengthY+i+1)%lengthY][(lengthX+j+1)%lengthX];
				

				// Logic
				if(countLives < 2)
				{
					board.BoardBack[i][j] = false;
				}
				else if(countLives == 2)
				{
					board.BoardBack[i][j] = board.BoardFront[i][j];
				}
				else if (countLives == 3)
				{
					board.BoardBack[i][j] = true;
				}
				else 
				{
					board.BoardBack[i][j] = false;
				}
			}
		}
		board.Swap();
	}
}