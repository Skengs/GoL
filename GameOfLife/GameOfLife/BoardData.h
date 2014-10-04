#pragma once

#include "stdafx.h"

class BoardData
{
public:
	BoardData(void);
	~BoardData(void);

	void Swap();

	std::vector<std::string> BoardFront, BoardBack;
};

