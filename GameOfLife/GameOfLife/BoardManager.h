#pragma once

#include "stdafx.h"
#include "BoardData.h"
#include "ILogic.h"
#include "LogicSEQ.h"
#include "LogicSEQ2.h"

class BoardManager
{
public:
	BoardManager(void);
	~BoardManager(void);

	int readMapFromFile(const std::string& fileName);
	void setLogicMode(LogicMode mode);
	void startLifeCycle(unsigned int generations);
	void print() const;
	void print(const std::string& fileNameOut) const;

private:
	BoardData _board;
	ILogic* _logic;
};

