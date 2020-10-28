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
		void readFile();//fja za iscitavanje datoteke i ispis na konzoli
		void ConvertTxtToRootFile();
};