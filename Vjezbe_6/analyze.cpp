#include "Analyzer.h"



int main () {
	Analyzer *pok;
	pok = new Analyzer();
	pok->PlotHistogram();
	//pok->HiggsKonstr();
	delete pok;
	return 0;
}