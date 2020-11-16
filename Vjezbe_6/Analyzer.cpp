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
   }
}

void Analyzer::PlotHistogram(){
	double weight; //w=L*sigma*w_ev / sum(w_ev)
	double L = 137; //luminozitet
	/*inicijalizacija i postavljanje histograma*/
	TH1F *histo1, *histo2, *histo3, *histo4; //4 histograma za 4 komponente pT
	TH1F *histo5, *histo6, *histo7, *histo8; //4 histograma za pseudorapiditet
	TH1F *histo9, *histo10, *histo11, *histo12; //4 histograma za azimutalni kut
	TH1F *histo13, *histo14, *histo15, *histo16; //4 histograma za BDT rezultat
	//pozivanje konstruktora (name of histogram, histogram title, number of bins, low edge of first bin, upper edge of last bin)
	histo1 = new TH1F("Histogram_pt1", "Decay leptons transverse momentum with event weight included", 70, 0, 140);
	histo2 = new TH1F("Histogram_pt2", "", 70, 0, 140);
	histo3 = new TH1F("Histogram_pt3", "", 70, 0, 140);
	histo4 = new TH1F("Histogram_pt4", "", 70, 0, 140);
	histo5 = new TH1F("Histogram_eta1", "Decay leptons pseudorapidity with event weight included", 60, -3, 3);
	histo6 = new TH1F("Histogram_eta2", "", 60, -3, 3);
	histo7 = new TH1F("Histogram_eta3", "", 60, -3, 3);
	histo8 = new TH1F("Histogram_eta4", "", 60, -3, 3);
	histo9 = new TH1F("Histogram_psi1", "Decay leptons azimuthal angle with event weight included", 70, -3.5, 3.5);
	histo10 = new TH1F("Histogram_psi2", "", 70, -3.5, 3.5);
	histo11 = new TH1F("Histogram_psi3", "", 70, -3.5, 3.5);
	histo12 = new TH1F("Histogram_psi4", "", 70, -3.5, 3.5);
	histo13 = new TH1F("Histogram_BDT1", "Decay leptons BDT result with event weight included", 110, -1, 10);
	histo14 = new TH1F("Histogram_BDT2", "", 110, -1, 10);
	histo15 = new TH1F("Histogram_BDT3", "", 110, -1, 10);
	histo16 = new TH1F("Histogram_BDT4", "", 110, -1, 10);
	
	//petlja koja puni histogram podacima
	if (fChain == 0) return;
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		weight = (L*xsec*1000*overallEventWeight)/(h1->GetBinContent(40));
		histo1->Fill(LepPt->at(0),weight);
		histo2->Fill(LepPt->at(1),weight);
		histo3->Fill(LepPt->at(2),weight);
		histo4->Fill(LepPt->at(3),weight);
		histo5->Fill(LepEta->at(0),weight);
		histo6->Fill(LepEta->at(1),weight);
		histo7->Fill(LepEta->at(2),weight);
		histo8->Fill(LepEta->at(3),weight);
		histo9->Fill(LepPhi->at(0),weight);
		histo10->Fill(LepPhi->at(1),weight);
		histo11->Fill(LepPhi->at(2),weight);
		histo12->Fill(LepPhi->at(3),weight);
		histo13->Fill(LepBDT->at(0),weight);
		histo14->Fill(LepBDT->at(1),weight);
		histo15->Fill(LepBDT->at(2),weight);
		histo16->Fill(LepBDT->at(3),weight);
   }
   /*uredivanje svojstava histograma*/
	histo1->GetXaxis()->SetTitle("p_{T} [GeV]"); //postavlja oznaku na x-osi
	histo1->GetYaxis()->SetTitle("Events / 2 GeV"); //postavlja oznaku na y-osi
	histo1->SetLineColor(kBlue+1); //postavlja boju linije, alpha - prozirnost
	histo2->SetLineColor(kOrange+6);
	histo3->SetLineColor(kMagenta+2);
	histo4->SetLineColorAlpha(kGreen+2,0.35);
	histo1->SetFillStyle(1001); //postavlja stil ispune
	histo1->SetFillColor(kBlue+1);//postavlja boju ispune
	histo4->SetFillColorAlpha(kGreen+2,0.35);
	histo1->SetMaximum(30); //postavljanje yrange
	
	histo5->GetXaxis()->SetTitle("#eta");
	histo5->GetYaxis()->SetTitle("Events / 0.1");
	histo5->SetLineColor(kBlue+1); //postavlja boju linije, alpha - prozirnost
	histo6->SetLineColor(kOrange+6);
	histo7->SetLineColor(kMagenta+2);
	histo8->SetLineColorAlpha(kGreen+2,0.35);
	histo5->SetFillStyle(1001); //postavlja stil ispune
	histo5->SetFillColor(kBlue+1);//postavlja boju ispune
	histo8->SetFillColorAlpha(kGreen+2,0.35);
	histo5->SetMaximum(10); //postavljanje yrange
	
	histo9->GetXaxis()->SetTitle("#phi [rad]");
	histo9->GetYaxis()->SetTitle("Events / 0.1 rad");
	histo9->SetLineColor(kBlue+1); //postavlja boju linije, alpha - prozirnost
	histo10->SetLineColor(kOrange+6);
	histo11->SetLineColor(kMagenta+2);
	histo12->SetLineColorAlpha(kGreen+2,0.35);
	histo9->SetFillStyle(1001); //postavlja stil ispune
	histo9->SetFillColor(kBlue+1);//postavlja boju ispune
	histo12->SetFillColorAlpha(kGreen+2,0.35);
	histo9->SetMaximum(6); //postavljanje yrange
	
	histo13->GetXaxis()->SetTitle("BDT");
	histo13->GetYaxis()->SetTitle("Events / 0.1");
	histo13->SetLineColor(kBlue+1); //postavlja boju linije, alpha - prozirnost
	histo14->SetLineColor(kOrange+6);
	histo15->SetLineColor(kMagenta+2);
	histo16->SetLineColorAlpha(kGreen+2,0.35);
	histo13->SetFillStyle(1001); //postavlja stil ispune
	histo13->SetFillColor(kBlue+1);//postavlja boju ispune
	histo16->SetFillColorAlpha(kGreen+2,0.35);
	histo13->SetMaximum(100); //postavljanje yrange
	
	gStyle->SetOptStat(0); //uklanja statisticki opis
	
	/*dodavanje legende*/
	TLegend *leg1, *leg2, *leg3, *leg4;
	//pozivanje konstruktora za legendu
	//(Double_t x1, Double_t y1, Double_t x2, Double_t y2, const char* header = "", Option_t* option = "brNDC")
	//x1,y1,x2,y2 - the coordinates of the Legend in the current pad
	//header - the title displayed at the top of the legend (default is no header (header = 0))
	//options - defines looks of the box, more at https://root.cern.ch/doc/master/classTPave.html#ac9ec1ee85b11f589e9a24c609872095d
	leg1 = new TLegend(0.6,0.7,0.9,0.9,"");
	leg2 = new TLegend(0.6,0.7,0.9,0.9,"");
	leg3 = new TLegend(0.6,0.7,0.9,0.9,"");
	leg4 = new TLegend(0.6,0.7,0.9,0.9,"");
	leg1->SetTextSize(.035); //postavljanje velicine teksta - izrazeno u postotku velicine trenutkog odjeljka
	leg2->SetTextSize(.035);
	leg3->SetTextSize(.035);
	leg4->SetTextSize(.035);
	//povezivanje legende s histogramom (naziv histograma, labela, opcija)
	leg1->AddEntry(histo1, "1st decay lepton", "f");
	leg1->AddEntry(histo2, "2nd decay lepton", "f");
	leg1->AddEntry(histo3, "3rd decay lepton", "f");
	leg1->AddEntry(histo4, "4th decay lepton", "f");
	leg2->AddEntry(histo5, "1st decay lepton", "f");
	leg2->AddEntry(histo6, "2nd decay lepton", "f");
	leg2->AddEntry(histo7, "3rd decay lepton", "f");
	leg2->AddEntry(histo8, "4th decay lepton", "f");
	leg3->AddEntry(histo9, "1st decay lepton", "f");
	leg3->AddEntry(histo10, "2nd decay lepton", "f");
	leg3->AddEntry(histo11, "3rd decay lepton", "f");
	leg3->AddEntry(histo12, "4th decay lepton", "f");
	leg4->AddEntry(histo13, "1st decay lepton", "f");
	leg4->AddEntry(histo14, "2nd decay lepton", "f");
	leg4->AddEntry(histo15, "3rd decay lepton", "f");
	leg4->AddEntry(histo16, "4th decay lepton", "f");
	TCanvas *canv; //stvaranje platna
	//pozivanje konstruktora za platno
	/*(const char* name, const char* title, Int_t wtopx, Int_t wtopy, Int_t ww, Int_t wh)
	name - canvas name
	title - canvas title
	wtopx,wtopy - pixel coordinates of the top left corner of the canvas (if wtopx < 0 the menubar is not shown)
	ww - canvas size in pixels along X
	wh - canvas size in pixels along Y*/
	canv = new TCanvas("c1","Profile histogram example",200, 10,700,500);
	canv->Divide(2,2); //podjela platna na 2 stupca, 2 retka
	
	canv->cd(1); //postavljanje prvog odjeljka ("pad") kao aktivnog
	histo1->Draw("HISTO"); //nacrtaj histogram na danom platnu
	histo2->Draw("HISTO same");
	histo3->Draw("HISTO same");
	histo4->Draw("HISTO same");
	leg1->Draw();
	
	canv->cd(2);
	histo5->Draw("HISTO");
	histo6->Draw("HISTO same");
	histo7->Draw("HISTO same");
	histo8->Draw("HISTO same");
	leg2->Draw();
	
	canv->cd(3);
	histo9->Draw("HISTO");
	histo10->Draw("HISTO same");
	histo11->Draw("HISTO same");
	histo12->Draw("HISTO same");
	leg3->Draw();
	
	canv->cd(4);
	histo13->Draw("HISTO");
	histo14->Draw("HISTO same");
	histo15->Draw("HISTO same");
	histo16->Draw("HISTO same");
	leg4->Draw();
	
	canv->SaveAs("Histogram_Z4_leptons.pdf"); //spremi platno kao...
	canv->SaveAs("Histogram_Z4_leptons.png");
	canv->SaveAs("Histogram_Z4_leptons.root");
	
	delete histo1; //brisanje pokazivaca
	delete histo2;
	delete histo3;
	delete histo4;
	delete histo5;
	delete histo6;
	delete histo7;
	delete histo8;
	delete histo9;
	delete histo10;
	delete histo11;
	delete histo12;
	delete histo13;
	delete histo14;
	delete histo15;
	delete histo16;
	delete leg1;
	delete leg2;
	delete leg3;
	delete leg4;
	delete canv;
}

void Analyzer::HiggsKonstr(){
	double weight; //w=L*sigma*w_ev / sum(w_ev)
	double L = 137; //luminozitet
	//cestice raspada kao elementi klase TLorentzVector
	TLorentzVector *lep1;
	TLorentzVector *lep2;
	TLorentzVector *lep3;
	TLorentzVector *lep4;
	TLorentzVector *Z1;
	TLorentzVector *Z2;
	TLorentzVector *Higgs;
	lep1 = new TLorentzVector();
	lep2 = new TLorentzVector();
	lep3 = new TLorentzVector();
	lep4 = new TLorentzVector();
	Z1 = new TLorentzVector();
	Z2 = new TLorentzVector();
	Higgs = new TLorentzVector();
	TH1F *histo1;
	//pozivanje konstruktora (name of histogram, histogram title, number of bins, low edge of first bin, upper edge of last bin)
	histo1 = new TH1F("Histogram", "Reconstructed four-lepton mass with event weight included", 25, 90, 140);

	/*postavke izgleda histograma*/
	histo1->SetLineColor(kBlue+1); //postavlja boju linije, alpha - prozirnost
	histo1->SetFillStyle(1001); //postavlja stil ispune
	histo1->SetFillColor(kBlue+1);//postavlja boju ispune
	gStyle->SetOptStat(0); //uklanja statisticki opis
	histo1->SetMaximum(100); //postavljanje yrange

	/*dodavanje legende*/
	TLegend *leg1;
	//pozivanje konstruktora za legendu
	//(Double_t x1, Double_t y1, Double_t x2, Double_t y2, const char* header = "", Option_t* option = "brNDC")
	//x1,y1,x2,y2 - the coordinates of the Legend in the current pad
	//header - the title displayed at the top of the legend (default is no header (header = 0))
	//options - defines looks of the box, more at https://root.cern.ch/doc/master/classTPave.html#ac9ec1ee85b11f589e9a24c609872095d
	leg1 = new TLegend(0.1,0.83,0.7,0.9,"");
	leg1->SetTextSize(.025); //postavljanje velicine teksta - izrazeno u postotku velicine trenutkog odjeljka
	//povezivanje legende s histogramom (naziv histograma, labela, opcija)
	leg1->AddEntry(histo1, "gluon-gluon fusion", "f");

	if (fChain == 0) return;
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		//SetPtEtaPhiM	(	Double_t pt,Double_t eta,Double_t phi, Double_t m)
		lep1->SetPtEtaPhiM(LepPt->at(0),LepEta->at(0),LepPhi->at(0), 0); //pp da je masa 0
		lep2->SetPtEtaPhiM(LepPt->at(1),LepEta->at(1),LepPhi->at(1), 0);
		lep3->SetPtEtaPhiM(LepPt->at(2),LepEta->at(2),LepPhi->at(2), 0);
		lep4->SetPtEtaPhiM(LepPt->at(3),LepEta->at(3),LepPhi->at(3), 0);
		*Z1 = *lep1 + *lep2;
		*Z2 = *lep3 + *lep4;
		*Higgs = *Z1 + *Z2;
		weight = (L*xsec*1000*overallEventWeight)/(h1->GetBinContent(40));
		histo1->Fill(Higgs->M(),weight);
   }
	leg1->AddEntry(histo1,Form("Expected number of reconstructed Higgs bosons: %10.4f",histo1->Integral()),""); 
	histo1->GetXaxis()->SetTitle("m_{4l} [GeV]"); //postavlja oznaku na x-osi
	histo1->GetYaxis()->SetTitle("Events / 2 GeV"); //postavlja oznaku na y-osi
	
	TCanvas *canv; //stvaranje platna
	//pozivanje konstruktora za platno
	/*(const char* name, const char* title, Int_t wtopx, Int_t wtopy, Int_t ww, Int_t wh)
	name - canvas name
	title - canvas title
	wtopx,wtopy - pixel coordinates of the top left corner of the canvas (if wtopx < 0 the menubar is not shown)
	ww - canvas size in pixels along X
	wh - canvas size in pixels along Y*/
	canv = new TCanvas("c1","Profile histogram example",200, 10,700,500);
	histo1->Draw("HISTO"); //nacrtaj histogram na danom platnu
	leg1->Draw();
	canv->SaveAs("Histogram_Z4_Higgs.pdf"); //spremi platno kao...
	canv->SaveAs("Histogram_Z4_Higgs.png");
	canv->SaveAs("Histogram_Z4_Higgs.root");
	delete histo1; //brisanje pokazivaca
	delete lep1;
	delete lep2;
	delete lep3;
	delete lep4;
	delete Z1;
	delete Z2;
	delete Higgs;
	delete leg1;
}
