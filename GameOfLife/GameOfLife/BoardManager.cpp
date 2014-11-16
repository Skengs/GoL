#include "BoardManager.h"
#include "LogicSEQ.h"
#include "LogicSEQ2.h"
#include "LogicMP.h"


BoardManager::BoardManager(void)
	: _logic(new LogicSEQ())
{
}


BoardManager::~BoardManager(void)
{
	delete _logic;
}

int BoardManager::readMapFromFile(const std::string& fileName)
{
	using namespace std;

	string line;
	unsigned int x, y;

	ifstream myfile(fileName.c_str());

	if(!myfile.is_open())
	{
		// file not found, error
		return 1;
	}

	// cut first line, eg: "500, 250"
	getline(myfile, line);
	string strX = line.substr(0, line.find(","));
	string strY = line.substr(line.find(",")+1, line.size());

	// convert string to int
	stringstream sx(strX);
	if(!(sx>>x))
		x = 0;
	stringstream sy(strY);
	if(!(sy>>y))
		y = 0;

	// cannot be 0
	if (x == 0 || y == 0)
		return 2;

	_board.sizeX = x;
	_board.sizeY = y;

	// create boards
	_board.BoardFront = new bool*[y];
	_board.BoardBack = new bool*[y];

	// [0] holds the whole board (1D)
	_board.BoardFront[0] = new bool[x * y];
	_board.BoardBack[0] = new bool[x * y];

	// manually set pointers to rows of the board
	for(unsigned int i = 1; i < y; ++i)
	{
		_board.BoardFront[i] = _board.BoardFront[0] + i * x;
		_board.BoardBack[i] = _board.BoardBack[0] + i * x;
	}

	// read rest of file
	for(unsigned int i = 0; getline(myfile, line) && i < y; ++i)
	{
		if(line.length() > x || line.length() < x)
			return 3;

		for (unsigned int j = 0; j < x; ++j)
		{
			_board.BoardFront[i][j] = (line[j] == 'x') ? true : false;
		}
	}

	myfile.close();

	return 0;
}

void BoardManager::setLogicMode(LogicMode mode)
{
	switch(mode)
	{
	case LogicMode::SEQ:
		delete _logic;
		_logic = new LogicSEQ();
		break;

	case LogicMode::SEQ2:
		delete _logic;
		_logic = new LogicSEQ2();
		break;

	case LogicMode::MP:
		delete _logic;
		_logic = new LogicMP();
		break;

	// ADD MODES HERE (3 of 3)

	default:
		break;
	}
}

void BoardManager::startLifeCycle(unsigned int generations)
{
	_logic->runLifeCycle(_board, generations);
}

void BoardManager::print() const
{
	for(unsigned int i = 0; i < _board.sizeY; ++i)
	{
		for(unsigned j = 0; j < _board.sizeX; ++j)
		{
			printf("%c", (_board.BoardFront[i][j] == true) ? 'x' : '.');
		}
		printf("\n");
	}
}

void BoardManager::print(const std::string& fileNameOut) const
{
	FILE* fileOut = NULL;
	char c;

	fileOut = fopen(fileNameOut.c_str(), "w");
	if (fileOut == NULL)
	{
		printf("Error creating/opening %s for output.\n", fileNameOut.c_str());
	}

	fprintf(fileOut, "%d,%d\n", _board.sizeX, _board.sizeY);
	for(unsigned int i = 0; i < _board.sizeY; ++i)
	{
		for(unsigned int j = 0; j < _board.sizeX; ++j)
		{
			c = (_board.BoardFront[i][j] == true) ? 'x' : '.';
			fprintf(fileOut, "%c", c);
		}
		fprintf(fileOut, "\n");
	}
	
	fclose(fileOut);
}