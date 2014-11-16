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
	// Are you sure it's undefined behaviour to delete a null pointer?
	// Stefan Reinalter "made sure" we know that it's safe
	if(BoardFront != NULL)
	{
		delete[] BoardFront[0]; // deletes whole board --> see BoardManager::readMapFromFile(...) why
		delete[] BoardFront;
	}

	if(BoardBack != NULL)
	{
		delete[] BoardBack[0];
		delete[] BoardBack;
	}
}


void BoardData::Swap()
{
	bool** tmp;
	tmp = BoardFront;
	BoardFront = BoardBack;
	BoardBack = tmp;
}