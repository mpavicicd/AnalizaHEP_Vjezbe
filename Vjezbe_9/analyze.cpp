#include "Analyzer.h"

int main () {
	Analyzer *pok;
	pok = new Analyzer();
	pok->TimeDistribution();
	delete pok;
	return 0;
}