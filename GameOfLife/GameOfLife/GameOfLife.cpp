#include "stdafx.h"
#include "BoardManager.h"

void printTime(double ms);

using namespace std;


/*
** Search for "ADD MODES HERE" to see where to 
** hook in additional computation modes.
*/

int main(int argc, const char* argv[])
{

	/*** Part 1 Read Input ***/

	Timer timerInput;

    // start timer
    timerInput.start();

	string filenameIn="", filenameOut = "", mode = "seq";
	int generations = 0;
	bool measure = false;
	bool total = false;

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
		else if(strcmp(argv[i], "--total") == 0)
		{
			total = true;
		}
		else if(strcmp(argv[i], "--mode") == 0)
		{
			mode = argv[i+1];
		}		
	}

	BoardManager* boardManager = new BoardManager();
	if(boardManager->readMapFromFile(filenameIn) != 0)
	{
		printf("An error occured when reading the inputfile \"%s\"", filenameIn.c_str());
		getchar();
		return EXIT_FAILURE;
	}

	if (strcmp(mode.c_str(), "seq") == 0)
	{
		boardManager->setLogicMode(LogicMode::SEQ2);
	}
	else if(strcmp(mode.c_str(), "seq_old") == 0)
	{
		boardManager->setLogicMode(LogicMode::SEQ);
	}
	// ADD MODES HERE (2 of 3)


    timerInput.stop();
    if(measure) printTime(timerInput.getElapsedTimeInMilliSec());

	/*** Part 2 Calc Lifecycle ***/
	Timer timerCalc;
	timerCalc.start();
	boardManager->startLifeCycle(generations);
	timerCalc.stop();
	if(measure) printTime(timerCalc.getElapsedTimeInMilliSec());

	/*** Part 3 Print to File & Cleanup ***/
	Timer timerPrint;
	timerPrint.start();
	boardManager->print(filenameOut);
	delete boardManager;
	timerPrint.stop();
	if(measure) printTime(timerPrint.getElapsedTimeInMilliSec());

	double sum = timerInput.getElapsedTimeInMilliSec();
	sum += timerCalc.getElapsedTimeInMilliSec();
	sum += timerPrint.getElapsedTimeInMilliSec();
	if(total) printTime(sum);

	getchar();
	return EXIT_SUCCESS;
}


void printTime(double ms)
{
	int h,m,s;

	h = ms / (60*60*1000);
	ms -= h*(60*60*1000);
	m = ms / (60*1000);
	ms -= m*(60*1000);
	s = ms / 1000;
	ms -= s*1000;
	printf("%02d:%02d:%02d.%03.0f; ", h, m, s, ms);
}