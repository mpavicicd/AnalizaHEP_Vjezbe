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

class PDFGenerator{
	public:

		PDFGenerator(); //poziv konstruktora
		void GenerateQuadraticPDF(string);
		double fx(double);
		void ConvertTxtToRootFile(string, TString);

	private:
		double xin, yin;
		bool skipFirstLine;
		string line;
};