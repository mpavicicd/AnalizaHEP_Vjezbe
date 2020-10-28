#include "Analyzer.h"



int main () {
	Analyzer *pok;
	pok = new Analyzer();
	pok->PlotHistogram();
	delete pok;
	return 0;
}