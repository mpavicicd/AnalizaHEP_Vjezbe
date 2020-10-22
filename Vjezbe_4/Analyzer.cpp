#include "Analyzer.h"

Analyzer::Analyzer() { //implementacija konstruktora
}

void Analyzer::readFile(){ //implementacija funkcije za ucitavanje datoteke
	string ime;
	double masa, en1, px1, py1, pz1, en2, px2, py2, pz2;
	bool ifbozon;
	ifstream File("Analysis.txt");
	string line;
	if (File.is_open())
	{
	while ( getline (File,line) )
	{
		stringstream lineStream(line);
		lineStream >> ime >> masa >> ifbozon >> en1 >> px1 >> py1 >> pz1 >> en2 >> px2 >> py2 >> pz2;
		cout << ime << masa << ifbozon << en1 << px1 << py1 << pz1 << en2 << px2 << py2 << pz2 << endl;
		}
	}
	File.close();
} 