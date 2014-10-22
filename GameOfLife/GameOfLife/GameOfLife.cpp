#include "stdafx.h"
#include "BoardManager.h"

using namespace std;

void seqLifeCycle (int generations);

vector<string> mapFront, mapBack;


int main(int argc, const char* argv[])
{

	/*** Part 1 Read Input ***/

	Timer timerInput;

    // start timer
    timerInput.start();

	string filenameIn="", filenameOut = "", mode = "seq";
	int generations = 0;
	bool measure = false;

	for(int i = 0; i<argc; i++)
	{
		if(strcmp(argv[i], "--load") == 0)
		{
			filenameIn = argv[i+1];
		}
		else if(strcmp(argv[i], "--save") == 0)
		{
			filenameOut = argv[i+1];
		}
		else if(strcmp(argv[i], "--generations") == 0)
		{
			stringstream s(argv[i+1]);
			if(!(s>>generations))
				generations = 0;
		}
		else if(strcmp(argv[i], "--measure") == 0)
		{
			measure = true;
		}
		else if(strcmp(argv[i], "--mode") == 0)
		{
			mode = argv[i+1];
		}		
	}

	BoardManager boardManager;
	if(boardManager.readMapFromFile(filenameIn) != 0)
	{
		printf("An error occured when reading the inputfile \"%s\"", filenameIn.c_str());
		getchar();
		return EXIT_FAILURE;
	}
	//board.print();

	if (strcmp(mode.c_str(), "seq") == 0)
	{
		boardManager.setLogicMode(LogicMode::SEQ);
	}
	else if(strcmp(mode.c_str(), "seq2") == 0)
	{
		boardManager.setLogicMode(LogicMode::SEQ2);
	}
	// ADD MODES HERE (2 of 3)


    timerInput.stop();
    cout << "Timer 1: " << timerInput.getElapsedTimeInMilliSec() << " ms\n";

	Timer timerCalc;
	timerCalc.start();
	boardManager.startLifeCycle(generations);
	timerCalc.stop();
	cout << "Timer 2: " << timerCalc.getElapsedTimeInMilliSec() << " ms\n";

	Timer timerPrint;
	timerPrint.start();
	boardManager.print(filenameOut);
	timerPrint.stop();
	cout << "Timer 3: " << timerPrint.getElapsedTimeInMilliSec() << " ms\n";

	getchar();
	return EXIT_SUCCESS;
}
