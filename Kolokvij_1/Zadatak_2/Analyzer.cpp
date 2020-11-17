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
	/*inicijalizacija i postavljanje histograma*/
	TH1F *histo1;
	TH1F *pomocni;
	TH2F *histo2;
	//konstruktor za TH1F (name of histogram, histogram title, number of bins, low edge of first bin, upper edge of last bin)
	histo1 = new TH1F("Histogram_pt1", "Electron p_{T}", 70, 0, 140);
	//konstruktor za TH2F (name of histogram, histogram title, nbinsx, xlow, xup, nbinsy, ylow, yup)
	histo2 = new TH2F("histo_signal", "p_{T} vs scl_eta", 70, 0., 140., 70, -3., 3.); //range za y odreden stvaranjem histograma za scl_eta

	//petlja koja puni histogram podacima
	if (fChain == 0) return;
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<10000;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		histo1->Fill(ele_pt);
		histo2->Fill(ele_pt, scl_eta);
   }
   /*uredivanje svojstava histograma*/
	histo1->GetXaxis()->SetTitle("p_{T} [GeV]"); //postavlja oznaku na x-osi
	histo1->GetYaxis()->SetTitle("Events / 2 GeV"); //postavlja oznaku na y-osi
	histo1->SetLineColor(kRed); //postavlja boju linije, alpha - prozirnost
	//histo1->SetMaximum(30); //postavljanje yrange
	
	gStyle->SetOptStat(0); //uklanja statisticki opis
	
	TCanvas *canv; //stvaranje platna
	//pozivanje konstruktora za platno
	canv = new TCanvas("c1","Profile histogram example",200, 10,700,500);
	canv->Divide(2); //podjela platna na 2 stupca, 2 retka
	
	canv->cd(1); //postavljanje prvog odjeljka ("pad") kao aktivnog
	gPad->SetLeftMargin(0.15);
	histo1->Draw("HISTO"); //nacrtaj histogram na danom platnu
	
	canv->cd(2);
	gPad->SetLeftMargin(0.15);
	histo2->Draw("COLZ");
	histo2->GetXaxis()->SetTitle("p_{T} [GeV]");
	histo2->GetYaxis()->SetTitle("scl_eta");
	
	canv->SaveAs("Histogram_Z2.pdf"); //spremi platno kao...
	canv->SaveAs("Histogram_Z2.png");
	canv->SaveAs("Histogram_Z2.root");
	
	delete histo1; //brisanje pokazivaca
	delete histo2;
	delete canv;
}
