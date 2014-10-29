#include "LogicSEQ.h"


LogicSEQ::LogicSEQ(void)
{
}


LogicSEQ::~LogicSEQ(void)
{
}


void LogicSEQ::runLifeCycle(BoardData& board, unsigned int generations)
{
	unsigned int lengthX = board.sizeX;
	unsigned int lengthY = board.sizeY;
	int countLives = 0;
	//int y_index, x_index;

	for(unsigned int h = 0; h < generations; ++h)
	{
		//printf("%d\n", h+1);
		for(unsigned int i = 0; i < lengthY; ++i)
		{
			for(unsigned int j = 0; j < lengthX; ++j)
			{
				countLives = 0;
		
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