#include "Analyzer.h"



int main () {
	Analyzer *pok;
	pok = new Analyzer(1000); //konstruktor je modificiran da prima broj binova za ROC kao argument
	pok->PlotHistogram("/home/public/data/ggH125/ZZ4lAnalysis.root");
	pok->PlotHistogram("/home/public/data/qqZZ/ZZ4lAnalysis.root"); //pozadina - SREDIT SKALU
	//pok->PlotMass();
	//pok->PlotDiscriminator();
	pok->HiggsMassWidth();
	delete pok;
	return 0;
}