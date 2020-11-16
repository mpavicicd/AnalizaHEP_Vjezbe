#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <TApplication.h>


using namespace std;

class Analyzer{
	public:
		Analyzer(); //poziv konstruktora
		void readFile(string);//fja za iscitavanje datoteke i ispis na konzoli
		void ConvertTxtToRootFile(string, TString);
	private:
		string Name1, Name2;
		double Mass1, En1, px1, py1, pz1, pT1, Mass2, En2, px2, py2, pz2, pT2;
		bool IfBoson1, IfBoson2;
		bool skipFirstLine;
		string line;
};