#include "Analyzer.h"



int main () {
	Analyzer *pok;
	pok = new Analyzer(); //konstruktor je modificiran da prima broj binova za ROC kao argument
	pok->TimeDistribution();
	delete pok;
	return 0;
}