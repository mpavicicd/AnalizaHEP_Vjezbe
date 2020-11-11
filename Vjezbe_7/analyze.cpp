#include "Analyzer.h"



int main () {
	Analyzer *pok;
	pok = new Analyzer();
	pok->PlotHistogram("/home/public/data/ggH125/ZZ4lAnalysis.root");
	pok->PlotHistogram("/home/public/data/qqZZ/ZZ4lAnalysis.root"); //pozadina - SREDIT SKALU
	pok->PlotMass();
	pok->PlotDiscriminator();
	delete pok;
	return 0;
}