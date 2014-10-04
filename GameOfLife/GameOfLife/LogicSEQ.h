#pragma once
#include "ILogic.h"

class LogicSEQ :
	public ILogic
{
public:
	LogicSEQ(void);
	virtual ~LogicSEQ(void);

	virtual void runLifeCycle(BoardData& board, unsigned int generations);
};