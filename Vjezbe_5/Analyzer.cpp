#define Analyzer_cxx
#include "Analyzer.h"

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
	  //cout << *Ime1 << endl;
   }
}

void Analyzer::PlotHistogram() //fja za crtanje histograma
{
	//cestice raspada kao elementi klase TLorentzVector
	TLorentzVector *pocetna;
	pocetna = new TLorentzVector();;
	
	/*inicijalizacija i postavljanje histograma*/
	TH1F *histo1, *histo2, *histo3;
	//pozivanje konstruktora (name of histogram, histogram title, number of bins, low edge of first bin, upper edge of last bin)
	histo1 = new TH1F("Histogram1", "Decay particles transverse momentum", 75, 0, 150);
	histo2 = new TH1F("Histogram2", "Decay particles transverse momentum", 75, 0, 150);
	histo3 = new TH1F("Histogram3", "Higgs boson transverse momentum", 75, 0, 150);
	//petlja koja puni histogram podacima
	if (fChain == 0) return;
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		pocetna->SetPxPyPzE(px1 + px2, py1 + py2, pz1 + pz2, En1 + En2); //stvaranje 4-vektora
		histo1->Fill(pT1);
		histo2->Fill(pT2);
		//ispuni treci histogram s p_T pocetne cestice
		histo3->Fill(pocetna->Pt());
	}

	/*uredivanje svojstava histograma*/
	histo1->GetXaxis()->SetTitle("p_{T} [GeV]"); //postavlja oznaku na x-osi
	histo1->GetYaxis()->SetTitle("Events / 2 GeV"); //postavlja oznaku na y-osi
	histo3->GetXaxis()->SetTitle("p_{T} [GeV]");
	histo3->GetYaxis()->SetTitle("Events / 2 GeV");
	histo1->SetLineColor(2); //postavlja boju linije
	histo2->SetLineColor(4);
	histo3->SetLineColor(3);
	//boje navedene na https://root.cern.ch/doc/master/classTAttLine.html
	histo1->SetFillStyle(1001); //postavlja stil ispune
	histo1->SetFillColor(2); //postavlja boju ispune
	histo3->SetFillStyle(1001); //postavlja stil ispune
	histo3->SetFillColor(3); //postavlja boju ispune
	//boje i stil navedeni na https://root.cern.ch/doc/master/classTAttFill.html
	histo3->SetMaximum(350);
	//gStyle->SetOptStat("n"); //u opisu ispisi samo naziv histograma
	gStyle->SetOptStat(0); //uklanja statisticki opis

	/*dodavanje legende - https://root.cern.ch/doc/master/classTLegend.html*/
	TLegend *leg1, *leg2;
	//pozivanje konstruktora za legendu
	//(Double_t x1, Double_t y1, Double_t x2, Double_t y2, const char* header = "", Option_t* option = "brNDC")
	//x1,y1,x2,y2 - the coordinates of the Legend in the current pad
	//header - the title displayed at the top of the legend (default is no header (header = 0))
	//options - defines looks of the box, more at https://root.cern.ch/doc/master/classTPave.html#ac9ec1ee85b11f589e9a24c609872095d
	leg1 = new TLegend(0.6,0.78,0.9,0.9,"Simulation results");
	leg2 = new TLegend(0.1,0.83,0.58,0.9,"Calculation from the simulation results");
	leg1->SetTextSize(.03); //postavljanje velicine teksta - izrazeno u postotku velicine trenutkog odjeljka
	leg2->SetTextSize(.03);
	//povezivanje legende s histogramom (naziv histograma, labela, opcija)
	leg1->AddEntry(histo1, "1st decay particle", "f");
	leg1->AddEntry(histo2, "2nd decay particle", "f");
	leg2->AddEntry(histo3, "Higgs boson", "f");

	TCanvas *canv; //stvaranje platna
	//pozivanje konstruktora za platno
	/*(const char* name, const char* title, Int_t wtopx, Int_t wtopy, Int_t ww, Int_t wh)
	name - canvas name
	title - canvas title
	wtopx,wtopy - pixel coordinates of the top left corner of the canvas (if wtopx < 0 the menubar is not shown)
	ww - canvas size in pixels along X
	wh - canvas size in pixels along Y*/
	canv = new TCanvas("c1","Profile histogram example",200, 10,700,500);
	canv->Divide(2,1); //podjela platna na 2 stupca, 1 redak

	//crtanje na lijevoj strani platna
	canv->cd(1); //postavljanje prvog odjeljka ("pad") kao aktivnog
	histo1->Draw(); //nacrtaj histogram na danom platnu
	histo2->Draw("same"); //same - crtaj na istom platnu
	leg1->Draw(); //nacrtaj legendu na danom platnu

	//crtanje na desnoj strani platna
	canv->cd(2);
	histo3->Draw();
	leg2->Draw();

	canv->SaveAs("Histogram_Z5.pdf"); //spremi platno kao...
	canv->SaveAs("Histogram_Z5.png"); //spremi platno kao...
	canv->SaveAs("Histogram_Z5.root"); //spremi platno kao...

	delete histo1; //brisanje pokazivaca
	delete histo2;
	delete histo3;
	delete pocetna;
}
