#include "Analyzer.h"

Analyzer::Analyzer() { //implementacija konstruktora
}

void Analyzer::readFile(string fileName){ //implementacija funkcije za ucitavanje datoteke
	ifstream File(fileName);
	skipFirstLine = true;
	//samo ucitavanje datoteke i ispis na ekran
	if (File.is_open()){
		while ( getline (File,line) ){
			stringstream lineStream(line);
			if(skipFirstLine){
				skipFirstLine = false;
				continue;
			}
			lineStream >> Name1 >> Mass1 >> IfBoson1 >> En1 >> px1 >> py1 >> pz1 >> pT1
						>> Name2 >> Mass2 >> IfBoson2 >> En2 >> px2 >> py2 >> pz2 >>pT2;
			//cout << Name1 <<"\t"<< Mass1 <<"\t"<< IfBoson1 <<"\t"<< En1 <<"\t"<< px1 <<"\t"<< py1 <<"\t"<< pz1 <<"\t"<< pT1 <<"\t"<< Name2 <<"\t"<< Mass2 <<"\t"<< IfBoson2 <<"\t"<< En2 <<"\t"<< px2 <<"\t"<< py2 <<"\t"<< pz2 <<"\t"<< pT2 << endl;
		}
	}
	File.close();
} 

void Analyzer::ConvertTxtToRootFile(string inputFile, TString outputFile){
	ifstream File(inputFile);
	skipFirstLine = true;
	
	//stvaranje ROOT file-a za spremanje Higgs dogadaja
	TFile *root_file = root_file = TFile::Open(outputFile,"RECREATE");
	//stvaranje stabla koje ce poprimiti sve Higgs dogadaje
	TTree *tree = new TTree("Tree","Vjezbe_4");
	//deklaracija grana za svaku varijablu koja ce uci u stablo, postavlja se da pokazuje na pripadajucu varijablu koja ce se koristiti da puniti stablo
	tree->Branch("Name1",&Name1);
	tree->Branch("Mass1",&Mass1,"Mass1/D");
	tree->Branch("IfBoson1",&IfBoson1,"IfBoson1/O");
	tree->Branch("En1",&En1,"En1/D");
	tree->Branch("px1",&px1,"px1/D");
	tree->Branch("py1",&py1,"py1/D");
	tree->Branch("pz1",&pz1,"pz1/D");
	tree->Branch("pT1",&pT1,"pT1/D");
	tree->Branch("Name2",&Name2);
	tree->Branch("Mass2",&Mass2,"Mass2/D");
	tree->Branch("IfBoson2",&IfBoson2,"IfBoson2/O");
	tree->Branch("En2",&En2,"En2/D");
	tree->Branch("px2",&px2,"px2/D");
	tree->Branch("py2",&py2,"py2/D");
	tree->Branch("pz2",&pz2,"pz2/D");
	tree->Branch("pT2",&pT2,"pT2/D");
  
	if (File.is_open()){
		while ( getline (File,line) ){
			stringstream lineStream(line);
			if(skipFirstLine){
				skipFirstLine = false;
				continue;
			}
			lineStream >> Name1 >> Mass1 >> IfBoson1 >> En1 >> px1 >> py1 >> pz1 >> pT1 >> Name2 >> Mass2 >> IfBoson2 >> En2 >> px2 >> py2 >> pz2 >> pT2;
			tree->Fill();
		}
	}
	tree->Print();
	tree->Write();
	File.close();
	delete root_file;
}