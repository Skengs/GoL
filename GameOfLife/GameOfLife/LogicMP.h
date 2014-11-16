#pragma once
#include "ILogic.h"

class LogicMP :
	public ILogic
{
public:
	LogicMP(void);
	virtual ~LogicMP(void);

	virtual void runLifeCycle(BoardData& board, unsigned int generations);

private:
	void applyLogicForCell (BoardData& board, unsigned int y, unsigned int x, int countLives) const;
};

