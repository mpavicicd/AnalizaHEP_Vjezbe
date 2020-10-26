#include "Analyzer.h"

Analyzer::Analyzer() { //implementacija konstruktora
}

void Analyzer::readFile(){ //implementacija funkcije za ucitavanje datoteke
	string ime1, ime2;
	double masa1, en1, px1, py1, pz1, pT1, masa2, en2, px2, py2, pz2, pT2;
	bool ifbozon1, ifbozon2;
	ifstream File("Analysis.txt");
	string line;
	//samo ucitavanje datoteke i ispis na ekran
	if (File.is_open())
	{
	while ( getline (File,line) )
	{
		stringstream lineStream(line);
		lineStream >> ime1 >> masa1 >> ifbozon1 >> en1 >> px1 >> py1 >> pz1 >> pT1 >> ime2 >> masa2 >> ifbozon2 >> en2 >> px2 >> py2 >> pz2 >>pT2;
		cout << ime1 <<"\t"<< masa1 <<"\t"<< ifbozon1 <<"\t"<< en1 <<"\t"<< px1 <<"\t"<< py1 <<"\t"<< pz1 <<"\t"<< pT1 <<"\t"<< ime2 <<"\t"<< masa2 <<"\t"<< ifbozon2 <<"\t"<< en2 <<"\t"<< px2 <<"\t"<< py2 <<"\t"<< pz2 <<"\t"<< pT2 << endl;
		}
	}
	File.close();
} 