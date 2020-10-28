#include "Analyzer.h"



int main () {
	Analyzer *pok;
	pok = new Analyzer();
	pok->Loop();
	delete pok;
	return 0;
}