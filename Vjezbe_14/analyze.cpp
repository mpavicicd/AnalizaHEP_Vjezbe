#include "Analyzer.h"
#include <cstdlib> 
#include <ctime> 

int main () {
	srand((int)time(0));

	Analyzer *pok;
	pok = new Analyzer();
	//cout << endl << "********** First task **********" << endl;
	pok->FirstTask();
	//cout << endl << "********** Second task **********" << endl;
	pok->SecondTask();
	delete pok;
	return 0;
}