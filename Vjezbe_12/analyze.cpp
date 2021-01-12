#include "Analyzer.h"
#include <cstdlib> 
#include <ctime> 

int main () {
	srand((int)time(0));

	Analyzer *pok;
	pok = new Analyzer();
	pok->LoopBackground();
	pok->LoopSignal();
	pok->PlotDistributions();
	pok->MVATraining();
	pok->MVAanalysis();
	delete pok;
	return 0;
}