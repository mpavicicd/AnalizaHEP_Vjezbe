#include "Analyzer.h"



int main () {
	Analyzer *pok;
	pok = new Analyzer();
	pok->HiggsKonstr();
	delete pok;
	return 0;
}