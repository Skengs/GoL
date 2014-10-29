#include "BoardData.h"


BoardData::BoardData(void)
	: BoardFront(NULL)
	, BoardBack(NULL)
	, sizeX(0)
	, sizeY(0)
{
}


BoardData::~BoardData(void)
{
	for(unsigned int i = 0; i < sizeY; ++i)
	{
		delete[] BoardFront[i];
		delete[] BoardBack[i];
	}
	delete[] BoardFront;
	delete[] BoardBack;
}


void BoardData::Swap()
{
	bool** tmp;
	tmp = BoardFront;
	BoardFront = BoardBack;
	BoardBack = tmp;
}