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

void Analyzer::ConvertTxtToRootFile(){
	string	Ime1;
	Double_t	Masa1;
	Bool_t		IfBozon1;
	Double_t	En1;
	Double_t	Px1;
	Double_t	Py1;
	Double_t	Pz1;
	Double_t	Pt1;
	string	Ime2;
	Double_t	Masa2;
	Bool_t		IfBozon2;
	Double_t	En2;
	Double_t	Px2;
	Double_t	Py2;
	Double_t	Pz2;
	Double_t	Pt2;

	ifstream File("Analysis.txt");
	TFile *root_file = root_file = TFile::Open("Analysis.root","RECREATE");

	TTree *tree = new TTree("Tree","Vjezbe_4");
	tree->Branch("Ime1",&Ime1);
	tree->Branch("Masa1",&Masa1,"Masa1/D");
	tree->Branch("IfBozon1",&IfBozon1,"IfBozon1/O");
	tree->Branch("En1",&En1,"En1/D");
	tree->Branch("Px1",&Px1,"Px1/D");
	tree->Branch("Py1",&Py1,"Py1/D");
	tree->Branch("Pz1",&Pz1,"Pz1/D");
	tree->Branch("Pt1",&Pt1,"Pt1/D");
	tree->Branch("Ime2",&Ime2);
	tree->Branch("Masa2",&Masa2,"Masa2/D");
	tree->Branch("IfBozon2",&IfBozon2,"IfBozon2/O");
	tree->Branch("En2",&En2,"En2/D");
	tree->Branch("Px2",&Px2,"Px2/D");
	tree->Branch("Py2",&Py2,"Py2/D");
	tree->Branch("Pz2",&Pz2,"Pz2/D");
	tree->Branch("Pt2",&Pt2,"Pt2/D");
  
	string line;
	if (File.is_open())
	{
	while ( getline (File,line) )
	{
		stringstream lineStream(line);
		lineStream >> Ime1 >> Masa1 >> IfBozon1 >> En1 >> Px1 >> Py1 >> Pz1 >> Pt1 >> Ime2 >> Masa2 >> IfBozon2 >> En2 >> Px2 >> Py2 >> Pz2 >> Pt2;
		tree->Fill();
		}
	}
	tree->Print();
	tree->Write();
	File.close();
	delete root_file;
}