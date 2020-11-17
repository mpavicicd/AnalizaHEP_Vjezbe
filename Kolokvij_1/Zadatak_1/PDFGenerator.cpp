#include "PDFGenerator.h"

PDFGenerator::PDFGenerator() { //implementacija konstruktora
	cout << "Objekt uspjesno kreiran." << endl;
}

void PDFGenerator::GenerateQuadraticPDF(string FileName){
	ofstream File(FileName);
	File << "x\tf(x)" << endl;
	int i;
	double x;
	double y;
	double fxmax = fx(0); //fja postize maximum u 0
	double U;
	int intfxmax = 1000*fxmax;
	while(i<10000){
		x = (double)(rand() % 2000 - 1000)/1000;
		y = fx(x);
		U = (double)(rand() % intfxmax)/1000;
		if (y < U){ //accept
			File << x << "\t" << y << endl;
			i++;
		}
	}
	File.close();
}

double PDFGenerator::fx(double x){
	return -0.75*x*x + 0.75;
}

void PDFGenerator::ConvertTxtToRootFile(string inputFile, TString outputFile){
	ifstream File(inputFile);
	skipFirstLine = true;
	
	//stvaranje ROOT file-a za spremanje Higgs dogadaja
	TFile *root_file = root_file = TFile::Open(outputFile,"RECREATE");
	//stvaranje stabla koje ce poprimiti sve Higgs dogadaje
	TTree *tree = new TTree("Tree","Zadatak_1");
	//deklaracija grana za svaku varijablu koja ce uci u stablo, postavlja se da pokazuje na pripadajucu varijablu koja ce se koristiti da puniti stablo

	tree->Branch("xin",&xin,"xin/D");
	tree->Branch("yin",&yin,"yin/D");

	if (File.is_open()){
		while ( getline (File,line) ){
			stringstream lineStream(line);
			if(skipFirstLine){
				skipFirstLine = false;
				continue;
			}
			lineStream >> xin >> yin;
			tree->Fill();
		}
	}
	//tree->Print();
	tree->Write();
	File.close();
	delete root_file;
}