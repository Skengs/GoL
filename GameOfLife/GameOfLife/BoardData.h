#pragma once

#include "stdafx.h"

class BoardData
{
public:
	BoardData(void);
	~BoardData(void);

	void Swap();

	//std::vector<std::vector<bool>> BoardFront, BoardBack;
	bool** BoardFront;
	bool** BoardBack;
	unsigned int sizeX;
	unsigned int sizeY;
};

