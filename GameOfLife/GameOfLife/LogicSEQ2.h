#pragma once
#include "ILogic.h"

class LogicSEQ2 :
	public ILogic
{
public:
	LogicSEQ2(void);
	virtual ~LogicSEQ2(void);
	virtual void runLifeCycle(BoardData& board, unsigned int generations);

private:
	void applyLogicForCell (BoardData& board, unsigned int y, unsigned int x, int countLives) const;
};