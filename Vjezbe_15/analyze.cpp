#include "Analyzer.h"
#include <cstdlib> 
#include <ctime> 

int main () {
	srand((int)time(0));

	Analyzer *pok;
	pok = new Analyzer();
	pok->InvariantMass();
	pok->TestStatistic();
	pok->PValue();
	delete pok;
	return 0;
}