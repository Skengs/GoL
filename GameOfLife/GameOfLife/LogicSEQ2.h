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

struct Value 
{
public:
	Value(void);
	unsigned short _value;
	int _modifier;
	bool _hasChanged;
};