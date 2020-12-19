#include "Analyzer.h"
#include <cstdlib> 
#include <ctime> 

int main () {
	srand((int)time(0));

	Analyzer *pok;
	pok = new Analyzer();

	//#####Z2#####
	int N = 10; //total number of events
	double CL = 0.6827; //confidence level
	pok -> RepeatClopperPearson(N, CL); //function that repeats ClopperPearson for all possibilities of r and prints all intervals
	cout << endl;

	//#####Z3#####
	pok -> PlotCPBelt(5); //input value is desired r
	
	//#####Z4#####
	int throws = 10; //number of throws
	int numofexp = 1000; //number of experiments
	cout << endl << "Experiment with dice throwing - percent of experiments in which interval covers true value" << endl;
	cout << "\tConfidence level\tpercent" << endl;
	cout << "\t1sigma\t\t\t" << pok -> DiceExperiment(numofexp, throws, 1) << "%" << endl;
	cout << "\t2sigma\t\t\t" << pok -> DiceExperiment(numofexp, throws, 2) << "%" << endl;

	delete pok;
	return 0;
}