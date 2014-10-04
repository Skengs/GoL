#include "BoardData.h"


BoardData::BoardData(void)
{
}


BoardData::~BoardData(void)
{
}


void BoardData::Swap()
{
	BoardFront.swap(BoardBack);
}