#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analyzer.C
//      root> Analyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}

void Analyzer::PlotHistogram(){
	cout << "Histogram nije napravljen, seg fault" <<endl;
/*	TH1F *histo1;
	//pozivanje konstruktora (name of histogram, histogram title, number of bins, low edge of first bin, upper edge of last bin)
	histo1 = new TH1F("Histogram1", "", 75, 0, 150);
	//petlja koja puni histogram podacima
	if (fChain == 0) return;
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		cout << "Tu" << endl;
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		cout << yin << endl;
		histo1->Fill(yin);

	}

	//histo1->GetXaxis()->SetTitle("p_{T} [GeV]"); //postavlja oznaku na x-osi
	//histo1->GetYaxis()->SetTitle("Events / 2 GeV"); //postavlja oznaku na y-osi
	//histo1->SetLineColor(2); //postavlja boju linije
	//histo1->SetFillStyle(1001); //postavlja stil ispune
	//histo1->SetFillColor(2); //postavlja boju ispune
	gStyle->SetOptStat(0); //uklanja statisticki opis

	TCanvas *canv; //stvaranje platna
	//pozivanje konstruktora za platno
	canv = new TCanvas("c1","Profile histogram example",200, 10,700,500);

	//crtanje na lijevoj strani platna
	canv->cd(1); //postavljanje prvog odjeljka ("pad") kao aktivnog
	histo1->Draw(); //nacrtaj histogram na danom platnu

	canv->SaveAs("Histogram_Z1.pdf"); //spremi platno kao...
	canv->SaveAs("Histogram_Z1.png"); //spremi platno kao...
	canv->SaveAs("Histogram_Z1.root"); //spremi platno kao...

	delete histo1; //brisanje pokazivaca
	delete canv;
*/
}