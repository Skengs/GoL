#pragma once
#include "ILogic.h"

class LogicSEQ2 :
	public ILogic
{
public:
	LogicSEQ2(void);
	virtual ~LogicSEQ2(void);
	virtual void runLifeCycle(BoardData& board, unsigned int generations);
};

