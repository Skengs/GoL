#include "BoardManager.h"


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

	// read rest of map
	_board.BoardFront.reserve(y);
	for(unsigned int i = 0; getline(myfile, line) && i < y; ++i)
	{
		if(line.length() > x || line.length() < x)
			return 3;
		_board.BoardFront.push_back(line);
	}

	// reserve space in back board
	_board.BoardBack.reserve(y);
	_board.BoardBack.resize(y);
	for(unsigned int i = 0; i < y; ++i)
	{
		_board.BoardBack[i].reserve(x);
		_board.BoardBack[i].resize(x);
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

	// additional modes here

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
	for(auto i = _board.BoardFront.begin(); i != _board.BoardFront.end(); i++)
	{
			printf("%s\n", i->c_str());
	}
}

void BoardManager::print(const std::string& fileNameOut) const
{
	using namespace std;
	ofstream fileOut(fileNameOut.c_str());
	for(auto i = _board.BoardFront.begin(); i != _board.BoardFront.end(); i++)
	{
		fileOut << *i << endl;
	}
	fileOut.close();
}