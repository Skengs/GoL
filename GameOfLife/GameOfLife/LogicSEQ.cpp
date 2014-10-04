#include "LogicSEQ.h"


LogicSEQ::LogicSEQ(void)
{
}


LogicSEQ::~LogicSEQ(void)
{
}


void LogicSEQ::runLifeCycle(BoardData& board, unsigned int generations)
{
	int lengthX = 0;
	int lengthY = 0;
	int countLives = 0;

	for(unsigned int h = 0; h < generations; ++h)
	{
		printf("%d\n", h+1);
		for(unsigned int i = 0; i < board.BoardFront.size(); ++i)
		{
			for(unsigned int j = 0; j < board.BoardFront[i].length(); ++j)
			{
				lengthX = board.BoardFront[i].length();
				lengthY = board.BoardFront.size();
				countLives = 0;

				// top left
				if(board.BoardFront[(lengthY+i-1)%lengthY][(lengthX+j-1)%lengthX] == 'x')
				{
					countLives++;
				}
				// top
				if(board.BoardFront[(lengthY+i-1)%lengthY][j] == 'x')
				{
					countLives++;
				}
				// top right
				if(board.BoardFront[(lengthY+i-1)%lengthY][(lengthX+j+1)%lengthX] == 'x')
				{
					countLives++;
				}
				// center left
				if(board.BoardFront[i][(lengthX+j-1)%lengthX] == 'x')
				{
					countLives++;
				}
				// center right
				if(board.BoardFront[i][(lengthX+j+1)%lengthX] == 'x')
				{
					countLives++;
				}
				// bottom left
				if(board.BoardFront[(lengthY+i+1)%lengthY][(lengthX+j-1)%lengthX] == 'x')
				{
					countLives++;
				}
				// bottom center
				if(board.BoardFront[(lengthY+i+1)%lengthY][j] == 'x')
				{
					countLives++;
				}
				// bottom right
				if(board.BoardFront[(lengthY+i+1)%lengthY][(lengthX+j+1)%lengthX] == 'x')
				{
					countLives++;
				}

				// Logic
				if(countLives < 2)
				{
					board.BoardBack[i][j] = '.';
				}
				else if(countLives == 2)
				{
					board.BoardBack[i][j] = board.BoardFront[i][j];
				}
				else if (countLives == 3)
				{
					board.BoardBack[i][j] = 'x';
				}
				else 
				{
					board.BoardBack[i][j] = '.';
				}
			}
		}
		board.Swap();
	}
}