#pragma once

#include "stdafx.h"
#include "BoardData.h"

class ILogic {
public:
	virtual ~ILogic(void){};
	virtual void runLifeCycle(BoardData& board, unsigned int generations) = 0;
};