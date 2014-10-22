#include "LogicSEQ2.h"


LogicSEQ2::LogicSEQ2(void)
{
}


LogicSEQ2::~LogicSEQ2(void)
{
}

// THIS DOES NOT WORK ATM, SEQ2 CAN BE DELETED

void LogicSEQ2::runLifeCycle(BoardData& board, unsigned int generations)
{
	int x = 0, y = 0;

	y = board.BoardFront.size();
	x = board.BoardFront[0].size();

	std::vector<std::vector<Value>> valueMapFront, valueMapBack;

	valueMapFront.reserve(y);
	valueMapFront.resize(y);
	valueMapBack.reserve(y);
	valueMapBack.resize(y);
	for(int i = 0; i < y; ++i)
	{
		valueMapFront[i].reserve(x);
		valueMapFront[i].resize(x);
		valueMapBack[i].reserve(x);
		valueMapBack[i].resize(x);
	}

	int countLives = 0;
	int x_index, y_index;

	// generate valueMap
	for(int i = 0; i < y; ++i)
	{
		for(int j = 0; j < x; ++j)
		{
			countLives = 0;

			// check neighbars of each element
			for(int k = -1; k <= 1; ++k)
			{
				// check for y boundary
				y_index = i + k;
				if(y_index == -1)
					y_index = y-1;
				else if(y_index == y)
					y_index = 0;

				for(int l = -1; l <= 1; ++l)
				{
					// check for x boundary
					x_index = j + l;
					if(x_index == -1)
						x_index = x-1;
					else if(x_index == x)
						x_index = 0;

					countLives += board.BoardFront[y_index][x_index];
				}
			}
			countLives -= board.BoardFront[i][j];
			valueMapFront[i][j]._value = countLives;
		}
	}

	int tmp_value;

	// lifecycle loop
	for(unsigned int h = 0; h < generations; ++h)
	{
		printf("%d\n", h+1);
		for(int i = 0; i < y; ++i)
		{
			for(int j = 0; j < x; ++j)
			{

				// check if something has changed, possible skip
				if(!valueMapFront[i][j]._hasChanged)
				{
					board.BoardBack[i][j] = board.BoardFront[i][j];
				}
				else 
				{
					valueMapFront[i][j]._modifier = 0;

					// Logic
					if(valueMapFront[i][j]._value < 2)
					{
						board.BoardBack[i][j] = false;
					}
					else if(valueMapFront[i][j]._value == 2)
					{
						board.BoardBack[i][j] = board.BoardFront[i][j];
					}
					else if (valueMapFront[i][j]._value == 3)
					{
						board.BoardBack[i][j] = true;
					}
					else 
					{
						board.BoardBack[i][j] = false;
					}

					// check if cell changed state
					if(board.BoardBack[i][j] != board.BoardFront[i][j])
					{
						tmp_value = (board.BoardBack[i][j] == true) ? 1 : -1;

						// update value in each neighbar
						for(int k = -1; k <= 1; ++k)
						{
							// check for y boundary
							y_index = i + k;
							if(y_index == -1)
								y_index = y-1;
							else if(y_index == y)
								y_index = 0;

							for(int l = -1; l <= 1; ++l)
							{
								// check for x boundary
								x_index = j + l;
								if(x_index == -1)
									x_index = x-1;
								else if(x_index == x)
									x_index = 0;

								if(k != 0 && l != 0)
								{
									// "inform" neighbar of change to this cell
									valueMapBack[y_index][x_index]._modifier += tmp_value;
									valueMapBack[y_index][x_index]._value = 
										valueMapFront[y_index][x_index]._value + 
										valueMapBack[y_index][x_index]._modifier;
									valueMapBack[y_index][x_index]._hasChanged = true;
								}
							}
						}
					}
					/*
					if(valueMapBack[i][j]._modifier == 0)
						valueMapBack[i][j]._hasChanged = false;
						*/
				}
			}
		}
		board.Swap();
		valueMapFront.swap(valueMapBack);
	}
}

Value::Value(void)
	: _value(0)
	, _modifier(0)
	, _hasChanged(true)
{
}