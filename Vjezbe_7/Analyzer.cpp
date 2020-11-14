#define Analyzer_cxx
#include "Analyzer.h"
#include <TH1F.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TAttFill.h>
#include <TLorentzVector.h>
#include <THStack.h>
#include <TMath.h>
#include <TGraph.h>

void Analyzer::Loop(){ //petlja po svim dogadajima
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

void Analyzer::PlotHistogram(TString putanja){ //funkcija za fill grafova i plot distribucija
	/*inicijalizacija varijabli*/
	//{
	TFile *f;
	TTree *tree;
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
	double weight; //w=L*sigma*w_ev / sum(w_ev)
	double L = 137; //luminozitet
	double cback = 70; //konstanta skaliranja za diskriminator za pozadinu
	double csig = 1; //za signal
	double diskr;
	//}
	
	/* connect the file used to generate this class and read the Tree.*/
	//{
	f = new TFile(putanja);
	TDirectory * dir = (TDirectory*)f->Get(putanja+":/ZZTree");
	dir->GetObject("candTree",tree);
	Init(tree, putanja);
	//}
	
	h1 = (TH1F*)f->Get("ZZTree/Counters"); //histogram u kojem se nalazi event weights
	
	/*inicijalizacija i konstruktor histograma za distribuciju - ostali su u .h*/
	//{
	TH1F *histo1, *histo2, *histo3, *histo4; //4 histograma za 4 komponente pT
	TH1F *histo5, *histo6, *histo7, *histo8; //4 histograma za pseudorapiditet
	TH1F *histo9, *histo10, *histo11, *histo12; //4 histograma za azimutalni kut
	TH1F *histo13, *histo14, *histo15, *histo16; //4 histograma za BDT rezultat
	//pozivanje konstruktora (name of histogram, histogram title, number of bins, low edge of first bin, upper edge of last bin)
	if(putanja == "/home/public/data/ggH125/ZZ4lAnalysis.root"){
		histo1 = new TH1F("pt1", "Distribution of decay leptons transverse momentum for signal events", 70, 0, 140);
		histo5 = new TH1F("eta1", "Distribution of decay leptons pseudorapidity for signal events", 60, -3, 3);
		histo9 = new TH1F("phi1", "Distribution of decay leptons azimuthal angle for signal events", 70, -3.5, 3.5);
		histo13 = new TH1F("bdt1", "Distribution of decay leptons BDT result for signal events", 110, -1, 10);
	}
	else{
		histo1 = new TH1F("pt1", "Distribution of decay leptons transverse momentum for background events", 70, 0, 140);
		histo5 = new TH1F("eta1", "Distribution of decay leptons pseudorapidity for background events", 60, -3, 3);
		histo9 = new TH1F("phi1", "Distribution of decay leptons azimuthal angle for background events", 70, -3.5, 3.5);
		histo13 = new TH1F("bdt1", "Distribution of decay leptons BDT result for background events", 110, -1, 10);
	}
	histo2 = new TH1F("pt2", "", 70, 0, 140);
	histo3 = new TH1F("pt3", "", 70, 0, 140);
	histo4 = new TH1F("pt4", "", 70, 0, 140);
	histo6 = new TH1F("eta2", "", 60, -3, 3);
	histo7 = new TH1F("eta3", "", 60, -3, 3);
	histo8 = new TH1F("eta4", "", 60, -3, 3);
	histo10 = new TH1F("phi2", "", 70, -3.5, 3.5);
	histo11 = new TH1F("phi3", "", 70, -3.5, 3.5);
	histo12 = new TH1F("phi4", "", 70, -3.5, 3.5);
	histo14 = new TH1F("bdt2", "", 110, -1, 10);
	histo15 = new TH1F("bdt3", "", 110, -1, 10);
	histo16 = new TH1F("bdt4", "", 110, -1, 10);
	//}
	
	/*petlja koja puni histogram podacima*/
	//{
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
		/*dio za masu*/
		lep1->SetPtEtaPhiM(LepPt->at(0),LepEta->at(0),LepPhi->at(0), 0); //pp da je masa 0
		lep2->SetPtEtaPhiM(LepPt->at(1),LepEta->at(1),LepPhi->at(1), 0);
		lep3->SetPtEtaPhiM(LepPt->at(2),LepEta->at(2),LepPhi->at(2), 0);
		lep4->SetPtEtaPhiM(LepPt->at(3),LepEta->at(3),LepPhi->at(3), 0);
		*Z1 = *lep1 + *lep2;
		*Z2 = *lep3 + *lep4;
		*Higgs = *Z1 + *Z2;
		weight = (L*xsec*1000*overallEventWeight)/(h1->GetBinContent(40));
		if(putanja == "/home/public/data/ggH125/ZZ4lAnalysis.root"){
			mass_signal_histo->Fill(Higgs->M(),weight);
			diskr = pow((1+((csig* p_QQB_BKG_MCFM)/p_GG_SIG_ghg2_1_ghz1_1_JHUGen)),-1);
			disc_signal_histo_10->Fill(diskr,weight);
			disc_signal_histo->Fill(diskr,weight);
		}
		else{
			mass_background_histo->Fill(Higgs->M(),weight);
			diskr = pow((1+((cback* p_QQB_BKG_MCFM)/p_GG_SIG_ghg2_1_ghz1_1_JHUGen)),-1);
			disc_background_histo_10->Fill(diskr,weight);
			disc_background_histo->Fill(diskr,weight);
		}
   }
	//}
   
	/*uredivanje svojstava histograma - nazivi osi, boja linije, ispuna, yrange (maximum)*/
	//{
	histo1->GetXaxis()->SetTitle("p_{T} [GeV]"); //postavlja oznaku na x-osi
	histo1->GetYaxis()->SetTitle("Events / 2 GeV"); //postavlja oznaku na y-osi
	histo1->SetLineColor(kBlue+1); //postavlja boju linije
	histo2->SetLineColor(kOrange+6);
	histo3->SetLineColor(kMagenta+2);
	histo4->SetLineColorAlpha(kGreen+2,0.35);
	histo1->SetFillStyle(1001); //postavlja stil ispune
	histo1->SetFillColor(kBlue+1);//postavlja boju ispune
	histo4->SetFillColorAlpha(kGreen+2,0.35);
	if(putanja == "/home/public/data/ggH125/ZZ4lAnalysis.root")
		histo1->SetMaximum(30); //postavljanje yrange
	else
		histo1->SetMaximum(200);
	
	histo5->GetXaxis()->SetTitle("#eta");
	histo5->GetYaxis()->SetTitle("Events / 0.1");
	histo5->SetLineColor(kBlue+1);
	histo6->SetLineColor(kOrange+6);
	histo7->SetLineColor(kMagenta+2);
	histo8->SetLineColorAlpha(kGreen+2,0.35);
	histo5->SetFillStyle(1001);
	histo5->SetFillColor(kBlue+1);
	histo8->SetFillColorAlpha(kGreen+2,0.35);
	if(putanja == "/home/public/data/ggH125/ZZ4lAnalysis.root")
		histo5->SetMaximum(10);
	else
		histo5->SetMaximum(150);
	
	histo9->GetXaxis()->SetTitle("#phi [rad]");
	histo9->GetYaxis()->SetTitle("Events / 0.1");
	histo9->SetLineColor(kBlue+1);
	histo10->SetLineColor(kOrange+6);
	histo11->SetLineColor(kMagenta+2);
	histo12->SetLineColorAlpha(kGreen+2,0.35);
	histo9->SetFillStyle(1001);
	histo9->SetFillColor(kBlue+1);
	histo12->SetFillColorAlpha(kGreen+2,0.35);
	if(putanja == "/home/public/data/ggH125/ZZ4lAnalysis.root")
		histo9->SetMaximum(6);
	else
		histo9->SetMaximum(100);
	
	histo13->GetXaxis()->SetTitle("BDT");
	histo13->GetYaxis()->SetTitle("Events / 0.1");
	histo13->SetLineColor(kBlue+1);
	histo14->SetLineColor(kOrange+6);
	histo15->SetLineColor(kMagenta+2);
	histo16->SetLineColorAlpha(kGreen+2,0.35);
	histo13->SetFillStyle(1001);
	histo13->SetFillColor(kBlue+1);
	histo16->SetFillColorAlpha(kGreen+2,0.35);
	if(putanja == "/home/public/data/ggH125/ZZ4lAnalysis.root")
		histo13->SetMaximum(100);
	else
		histo13->SetMaximum(1600);
	//}
	
	gStyle->SetOptStat(0); //uklanja statisticki opis
	
	/*legenda*/
	//{
	TLegend *leg1, *leg2, *leg3, *leg4;
	//konstruktor za legendu (Double_t x1, Double_t y1, Double_t x2, Double_t y2, const char* header = "", Option_t* option = "brNDC")
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
	leg1->AddEntry(histo1, "1st decay lepton", "l");
	leg1->AddEntry(histo2, "2nd decay lepton", "l");
	leg1->AddEntry(histo3, "3rd decay lepton", "l");
	leg1->AddEntry(histo4, "4th decay lepton", "l");
	leg2->AddEntry(histo5, "1st decay lepton", "l");
	leg2->AddEntry(histo6, "2nd decay lepton", "l");
	leg2->AddEntry(histo7, "3rd decay lepton", "l");
	leg2->AddEntry(histo8, "4th decay lepton", "l");
	leg3->AddEntry(histo9, "1st decay lepton", "l");
	leg3->AddEntry(histo10, "2nd decay lepton", "l");
	leg3->AddEntry(histo11, "3rd decay lepton", "l");
	leg3->AddEntry(histo12, "4th decay lepton", "l");
	leg4->AddEntry(histo13, "1st decay lepton", "l");
	leg4->AddEntry(histo14, "2nd decay lepton", "l");
	leg4->AddEntry(histo15, "3rd decay lepton", "l");
	leg4->AddEntry(histo16, "4th decay lepton", "l");
	//}
	
	/*inicijalizacija platna, crtanje i spremanje u pdf*/
	//{
	TCanvas *canv; //stvaranje platna
	//konstruktor za platno (const char* name, const char* title, Int_t wtopx, Int_t wtopy, Int_t ww, Int_t wh)
	//name - canvas name;	title - canvas title;	wtopx,wtopy - pixel coordinates of the top left corner of the canvas (if wtopx < 0 the menubar is not shown);
	//ww - canvas size in pixels along X;	wh - canvas size in pixels along Y
	canv = new TCanvas("canvas for distribution","Profile histogram example",200, 10,700,500);
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
	
	if(putanja == "/home/public/data/ggH125/ZZ4lAnalysis.root")
		canv->SaveAs("Histogram_Z1_signal.pdf");
	else
		canv->SaveAs("Histogram_Z1_background.pdf");
	//}
	
	/*brisanje pokazivaca*/
	//{
	delete lep1;
	delete lep2;
	delete lep3;
	delete lep4;
	delete Z1;
	delete Z2;
	delete Higgs;
	delete histo1;
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
	//}
}

void Analyzer::PlotMass(){//funkcija za plot mase
	THStack *stack;
	stack = new THStack("stack", "Stacked Higgs mass");
	
	/*uredivanje svojstava histograma - nazivi osi, boja linije, ispuna, yrange (maximum)*/
	//{
	mass_signal_histo->GetXaxis()->SetTitle("m_{4l} [GeV]"); //postavlja oznaku na x-osi
	mass_signal_histo->GetYaxis()->SetTitle("Events / 2 GeV"); //postavlja oznaku na y-osi
	mass_signal_histo->SetLineColor(kBlue+1); //postavlja boju linije, alpha - prozirnost
	mass_background_histo->SetLineColor(kOrange+6);
	mass_signal_histo->SetFillStyle(1001); //postavlja stil ispune
	mass_signal_histo->SetFillColor(kBlue+1);//postavlja boju ispune
	//}
	
	gStyle->SetOptStat(0); //uklanja statisticki opis

	/*legenda*/
	//{
	TLegend *leg1;
	//pozivanje konstruktora za legendu
	//(Double_t x1, Double_t y1, Double_t x2, Double_t y2, const char* header = "", Option_t* option = "brNDC")
	//x1,y1,x2,y2 - the coordinates of the Legend in the current pad
	//header - the title displayed at the top of the legend (default is no header (header = 0))
	//options - defines looks of the box, more at https://root.cern.ch/doc/master/classTPave.html#ac9ec1ee85b11f589e9a24c609872095d
	leg1 = new TLegend(0.7,0.75,0.9,0.9,"");
	leg1->SetTextSize(.025); //postavljanje velicine teksta - izrazeno u postotku velicine trenutkog odjeljka
	//povezivanje legende s histogramom (naziv histograma, labela, opcija)
	leg1->AddEntry(mass_signal_histo, "signal", "l");
	leg1->AddEntry(mass_background_histo, "background", "l");
	//}

	/*inicijalizacija platna, crtanje i spremanje u pdf*/
	//{
	TCanvas *canv; //stvaranje platna
	//konstruktor za platno (const char* name, const char* title, Int_t wtopx, Int_t wtopy, Int_t ww, Int_t wh)
	//name - canvas name;	title - canvas title;	wtopx,wtopy - pixel coordinates of the top left corner of the canvas (if wtopx < 0 the menubar is not shown);
	//ww - canvas size in pixels along X;	wh - canvas size in pixels along Y
	canv = new TCanvas("canvas for mass","Profile histogram example",200, 10,700,500);
	
	stack->Add(mass_background_histo);
	stack->Add(mass_signal_histo);
	stack->Draw("HISTO"); //nacrtaj histogram na danom platnu
	stack->GetXaxis()->SetTitle("m_{4l} [GeV]"); //postavlja oznaku na x-osi
	stack->GetYaxis()->SetTitle("Events / 2 GeV"); //postavlja oznaku na y-osi
	canv->Modified();
	leg1->Draw();
	canv->SaveAs("Histogram_Z2.pdf"); //spremi platno kao...
	//}

	/*brisanje pokazivaca*/
	//{
	delete leg1;
	delete canv;
	delete stack;
	//}
}

void Analyzer::PlotDiscriminator(){ //funkcija za plot diskriminatora
	Double_t x[number_of_bins_for_discriminator], y[number_of_bins_for_discriminator];
	/*uredivanje svojstava histograma - nazivi osi, boja linije, ispuna, yrange (maximum)*/
	//{
	disc_signal_histo_10->GetXaxis()->SetTitle("Kinematic discriminator");
	disc_signal_histo_10->GetYaxis()->SetTitle("Events / 0.1");
	disc_signal_histo_10->SetLineColor(kBlue+1);
	disc_background_histo_10->SetLineColor(kOrange+6);
	disc_signal_histo_10->SetFillStyle(1001);
	disc_signal_histo_10->SetFillColor(kBlue+1);
	//}

	gStyle->SetOptStat(0);
	
	/*legenda*/
	//{
	TLegend *leg1;
	leg1 = new TLegend(0.1,0.8,0.4,0.9,"");
	leg1->SetTextSize(.025);
	leg1->AddEntry(disc_signal_histo_10, "signal", "l");
	leg1->AddEntry(disc_background_histo_10, "background", "l");
	//}

	/*normalizacija*/
	//{
	Double_t factor = 1.;
	disc_signal_histo_10->Scale(factor/disc_signal_histo->Integral());
	disc_background_histo_10->Scale(factor/disc_background_histo->Integral());
	disc_signal_histo->Scale(factor/disc_signal_histo->Integral());
	disc_background_histo->Scale(factor/disc_background_histo->Integral());
	//}

	/*Receiver operating characteristic (ROC)*/
	//{

	for(int i=1;i<=number_of_bins_for_discriminator;i++){
		x[i] = disc_background_histo->Integral(1,i);
		y[i] = disc_signal_histo->Integral(1,i);
		//cout << i << ". bin: x = " << x[i] << " , y = " << y[i] << endl;
	}
	TGraph* gr = new TGraph(number_of_bins_for_discriminator,x,y);
	//}

	/*inicijalizacija platna, crtanje i spremanje u pdf*/
	//{
	TCanvas *canv;
	canv = new TCanvas("canvas for discriminator","Profile histogram example",200, 10,700,500);
	canv->Divide(2); //podjela platna na 2 stupca
	
	canv->cd(1); //postavljanje prvog odjeljka ("pad") kao aktivnog
	disc_signal_histo_10->Draw("HISTO"); //nacrtaj histogram na danom platnu
	disc_background_histo_10->Draw("HISTO same");
	leg1->Draw();
	
	canv->cd(2);
	gr->SetTitle("Receiver operating characteristic");
	gr->GetXaxis()->SetTitle("percent of background events");
	gr->GetYaxis()->SetTitle("percent of signal events");
	//gr->GetXaxis()->SetRangeUser(0.8,1.1);
	gr->Draw("AP");
	
	canv->SaveAs("Histogram_Z4.pdf"); //spremi platno kao...
	//}
	
	/*brisanje pokazivaca*/
	//{
	delete leg1;
	delete canv;
	delete gr;
	//}
}