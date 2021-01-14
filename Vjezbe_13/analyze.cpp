#include "Analyzer.h"
#include <cstdlib> 
#include <ctime> 

int main () {
	srand((int)time(0));

	Analyzer *pok;
	pok = new Analyzer();
	pok->CalculateTobs();
	cout << endl << "********** First task **********" << endl;
	pok->FirstTask();
	cout << endl << "********** Second task **********" << endl;
	pok->SecondTask("France");
	pok->SecondTask("Italy");
	pok->SecondTask("Netherland");
	delete pok;
	return 0;
}