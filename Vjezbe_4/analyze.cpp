#include "Analyzer.h"

int main () {
	Analyzer *pok;
	pok = new Analyzer();
	pok->readFile("../Vjezbe_3/Analysis.txt");
	pok->ConvertTxtToRootFile("../Vjezbe_3/Analysis.txt","Analysis.root");
	delete pok;
  return 0;
}