#include "Analyzer.h"
#include <cstdlib> 
#include <ctime> 

int main () {
	srand((int)time(0));
	Analyzer *pok;
	int i, nexp, dice, count = 0;
	int yes=0, no=0;
	pok = new Analyzer();
	int throws = 10;
	/*for(int r_in=0; r_in<= 10; r_in++){ //za Z2
		pok->ClopperPearson(r_in,10,0.68); //r, N, C
	}*/
	for(nexp=0; nexp<1000; nexp++){ // za Z4
		for(i=0; i<throws; i++){
			dice = rand() % 6 + 1;
			if(dice == 6)
				count = count + 1;
		}
	/*if(pok->CheckInterval(count, throws, 1./6)) //TU STALA, javlja seg
		yes = yes + 1;
	else
		no = no + 1;*/
	}
	cout << "Broj slucajeva u kojim vjerojatnost upada u pojas: " << yes << endl;
	delete pok;
	return 0;
}