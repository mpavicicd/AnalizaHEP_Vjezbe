#include "PDFGenerator.h"
#include "Analyzer.h"

int main () {
	srand((int)time(0));
	PDFGenerator *pok;
	pok = new PDFGenerator();
	pok -> GenerateQuadraticPDF("Zadatak1.txt");
	pok->ConvertTxtToRootFile("Zadatak1.txt","Zadatak1.root");
	Analyzer *pok2;
	pok2 = new Analyzer();
	pok2->PlotHistogram();
	delete pok;
  return 0;
}