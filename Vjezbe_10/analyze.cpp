#include "Analyzer.h"

int main () {
	Analyzer *pok;
	pok = new Analyzer();
	pok->FitFunction();
	delete pok;
	return 0;
}