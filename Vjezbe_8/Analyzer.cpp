#define Analyzer_cxx
#include "Analyzer.h"

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
	
	h1_event_weights = (TH1F*)f->Get("ZZTree/Counters"); //histogram u kojem se nalazi event weights
	
	/*inicijalizacija i konstruktor histograma za distribuciju - ostali su u .h*/
	//{
	TH1F *histo1, *histo2, *histo3, *histo4; //4 histograma za 4 komponente pT
	TH1F *histo5, *histo6, *histo7, *histo8; //4 histograma za pseudorapiditet
	TH1F *histo9, *histo10, *histo11, *histo12; //4 histograma za azimutalni kut
	TH1F *histo13, *histo14, *histo15, *histo16; //4 histograma za BDT rezultat
	//pozivanje konstruktora (name of histogram, histogram title, number of bins, low edge of first bin, upper edge of last bin)
	histo1 = new TH1F("pt1", "", 70, 0, 140);
	histo2 = new TH1F("pt2", "", 70, 0, 140);
	histo3 = new TH1F("pt3", "", 70, 0, 140);
	histo4 = new TH1F("pt4", "", 70, 0, 140);
	histo5 = new TH1F("eta1", "", 60, -3, 3);
	histo6 = new TH1F("eta2", "", 60, -3, 3);
	histo7 = new TH1F("eta3", "", 60, -3, 3);
	histo8 = new TH1F("eta4", "", 60, -3, 3);
	histo9 = new TH1F("phi1", "", 70, -3.5, 3.5);
	histo10 = new TH1F("phi2", "", 70, -3.5, 3.5);
	histo11 = new TH1F("phi3", "", 70, -3.5, 3.5);
	histo12 = new TH1F("phi4", "", 70, -3.5, 3.5);
	histo13 = new TH1F("bdt1", "", 110, -1, 10);
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
		weight = (L*xsec*1000*overallEventWeight)/(h1_event_weights->GetBinContent(40));
		/*histo1->Fill(LepPt->at(0),weight);
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
		histo16->Fill(LepBDT->at(3),weight);*/
		/*dio za masu*/
		lep1->SetPtEtaPhiM(LepPt->at(0),LepEta->at(0),LepPhi->at(0), 0); //pp da je masa 0
		lep2->SetPtEtaPhiM(LepPt->at(1),LepEta->at(1),LepPhi->at(1), 0);
		lep3->SetPtEtaPhiM(LepPt->at(2),LepEta->at(2),LepPhi->at(2), 0);
		lep4->SetPtEtaPhiM(LepPt->at(3),LepEta->at(3),LepPhi->at(3), 0);
		*Z1 = *lep1 + *lep2;
		*Z2 = *lep3 + *lep4;
		*Higgs = *Z1 + *Z2;
		if(putanja == "/home/public/data/ggH125/ZZ4lAnalysis.root"){
			h1_mass_signal->Fill(Higgs->M(),weight);
			/*diskr = pow((1+((csig* p_QQB_BKG_MCFM)/p_GG_SIG_ghg2_1_ghz1_1_JHUGen)),-1);
			h1_disc_signal_10->Fill(diskr,weight);
			h1_disc_signal->Fill(diskr,weight);
			h2_mass_KD_signal->Fill(Higgs->M(), diskr, weight);*/
		}
		else{
			h1_mass_back->Fill(Higgs->M(),weight);
			/*diskr = pow((1+((cback* p_QQB_BKG_MCFM)/p_GG_SIG_ghg2_1_ghz1_1_JHUGen)),-1);
			h1_disc_back_10->Fill(diskr,weight);
			h1_disc_back->Fill(diskr,weight);
			h2_mass_KD_back->Fill(Higgs->M(), diskr, weight);*/
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
	if(putanja == "/home/public/data/ggH125/ZZ4lAnalysis.root"){
		histo1->SetMaximum(30); //postavljanje yrange
		histo1->SetTitle("Transverse momentum for gluon-gluon fusion");
	}
	else{
		histo1->SetMaximum(200);
		histo1->SetTitle("Transverse momentum for q #bar{q} #rightarrow ZZ");
	}
	
	histo5->GetXaxis()->SetTitle("#eta");
	histo5->GetYaxis()->SetTitle("Events / 0.1");
	histo5->SetLineColor(kBlue+1);
	histo6->SetLineColor(kOrange+6);
	histo7->SetLineColor(kMagenta+2);
	histo8->SetLineColorAlpha(kGreen+2,0.35);
	histo5->SetFillStyle(1001);
	histo5->SetFillColor(kBlue+1);
	histo8->SetFillColorAlpha(kGreen+2,0.35);
	if(putanja == "/home/public/data/ggH125/ZZ4lAnalysis.root"){
		histo5->SetMaximum(10);
		histo5->SetTitle("Pseudorapidity for gluon-gluon fusion");
	}
	else{
		histo5->SetMaximum(150);
		histo5->SetTitle("Pseudorapidity for q #bar{q} #rightarrow ZZ");
	}
	
	histo9->GetXaxis()->SetTitle("#phi [rad]");
	histo9->GetYaxis()->SetTitle("Events / 0.1");
	histo9->SetLineColor(kBlue+1);
	histo10->SetLineColor(kOrange+6);
	histo11->SetLineColor(kMagenta+2);
	histo12->SetLineColorAlpha(kGreen+2,0.35);
	histo9->SetFillStyle(1001);
	histo9->SetFillColor(kBlue+1);
	histo12->SetFillColorAlpha(kGreen+2,0.35);
	if(putanja == "/home/public/data/ggH125/ZZ4lAnalysis.root"){
		histo9->SetMaximum(6);
		histo9->SetTitle("Azimuthal angle for gluon-gluon fusion");
	}
	else{
		histo9->SetMaximum(100);
		histo9->SetTitle("Azimuthal angle for q #bar{q} #rightarrow ZZ");
	}
	
	histo13->GetXaxis()->SetTitle("BDT");
	histo13->GetYaxis()->SetTitle("Events / 0.1");
	histo13->SetLineColor(kBlue+1);
	histo14->SetLineColor(kOrange+6);
	histo15->SetLineColor(kMagenta+2);
	histo16->SetLineColorAlpha(kGreen+2,0.35);
	histo13->SetFillStyle(1001);
	histo13->SetFillColor(kBlue+1);
	histo16->SetFillColorAlpha(kGreen+2,0.35);
	if(putanja == "/home/public/data/ggH125/ZZ4lAnalysis.root"){
		histo13->SetMaximum(100);
		histo13->SetTitle("BDT result for gluon-gluon fusion");
	}
	else{
		histo13->SetMaximum(1600);
		histo13->SetTitle(" BDT result for q #bar{q} #rightarrow ZZ");
	}
	//}
	
	gStyle->SetOptStat(); //uklanja statisticki opis
	
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
	//}
	
	/*inicijalizacija platna, crtanje i spremanje u pdf*/
	//zakomentirano jer ne treba za V8
	//{
	/*TCanvas *canv; //stvaranje platna
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
	
	if(putanja == "/home/public/data/ggH125/ZZ4lAnalysis.root"){
		canv->SaveAs("Histogram_Z1_signal.pdf");
		canv->SaveAs("Histogram_Z1_signal.png");
		canv->SaveAs("Histogram_Z1_signal.root");
	}
	else{
		canv->SaveAs("Histogram_Z1_background.pdf");
		canv->SaveAs("Histogram_Z1_background.png");
		canv->SaveAs("Histogram_Z1_background.root");
	}*/
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
	delete h1_event_weights;
	delete leg1;
	delete leg2;
	delete leg3;
	delete leg4;
	//delete canv;
	//}
}

void Analyzer::PlotMass(){//funkcija za plot mase
	THStack *stack;
	stack = new THStack("stack", "Reconstructed four-lepton mass");
	
	/*uredivanje svojstava histograma - nazivi osi, boja linije, ispuna, yrange (maximum)*/
	//{
	h1_mass_signal->GetXaxis()->SetTitle("m_{4l} [GeV]"); //postavlja oznaku na x-osi
	h1_mass_signal->GetYaxis()->SetTitle("Events / 2 GeV"); //postavlja oznaku na y-osi
	h1_mass_signal->SetLineColor(kOrange+6); //postavlja boju linije, alpha - prozirnost
	h1_mass_back->SetLineColor(kBlue+1);
	h1_mass_signal->SetFillStyle(1001); //postavlja stil ispune
	h1_mass_signal->SetFillColor(kOrange+6);//postavlja boju ispune
	h1_mass_back->SetFillStyle(1001);
	h1_mass_back->SetFillColor(kBlue+1);
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
	leg1->AddEntry(h1_mass_signal, "gg #rightarrow ZZ", "f");
	leg1->AddEntry(h1_mass_back, "q#bar{q} #rightarrow ZZ", "f");
	//}

	/*inicijalizacija platna, crtanje i spremanje u pdf*/
	//{
	TCanvas *canv; //stvaranje platna
	//konstruktor za platno (const char* name, const char* title, Int_t wtopx, Int_t wtopy, Int_t ww, Int_t wh)
	//name - canvas name;	title - canvas title;	wtopx,wtopy - pixel coordinates of the top left corner of the canvas (if wtopx < 0 the menubar is not shown);
	//ww - canvas size in pixels along X;	wh - canvas size in pixels along Y
	canv = new TCanvas("canvas for mass","Profile histogram example",200, 10,700,500);
	
	stack->Add(h1_mass_back);
	stack->Add(h1_mass_signal);
	stack->Draw("HISTO"); //nacrtaj histogram na danom platnu
	stack->GetXaxis()->SetTitle("m_{4l} [GeV]"); //postavlja oznaku na x-osi
	stack->GetYaxis()->SetTitle("Events / 2 GeV"); //postavlja oznaku na y-osi
	canv->Modified();
	leg1->Draw();
	canv->SaveAs("Histogram_Z2.pdf"); //spremi platno kao...
	canv->SaveAs("Histogram_Z2.png");
	canv->SaveAs("Histogram_Z2.root");
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
	h1_disc_signal_10->GetXaxis()->SetTitle("D^{kin}");
	h1_disc_signal_10->GetYaxis()->SetTitle("Events / 0.1");
	h1_disc_signal_10->SetLineColor(kBlue+1);
	h1_disc_back_10->SetLineColor(kOrange+6);
	h1_disc_signal_10->SetFillStyle(1001);
	h1_disc_signal_10->SetFillColor(kBlue+1);
	//}

	gStyle->SetOptStat(0);
	
	/*legenda*/
	//{
	TLegend *leg1;
	leg1 = new TLegend(0.1,0.8,0.4,0.9,"");
	leg1->SetTextSize(.025);
	leg1->AddEntry(h1_disc_signal_10, "gg #rightarrow ZZ", "f");
	leg1->AddEntry(h1_disc_back_10, "q#bar{q} #rightarrow ZZ", "f");
	//}

	/*normalizacija*/
	//{
	h1_disc_signal_10->Scale(1./h1_disc_signal->Integral());
	h1_disc_back_10->Scale(1./h1_disc_back->Integral());
	h1_disc_signal->Scale(1./h1_disc_signal->Integral());
	h1_disc_back->Scale(1./h1_disc_back->Integral());
	//}

	/*Receiver operating characteristic (ROC)*/
	//{
	TGraph* ROC = new TGraph();
	for(int i=1;i<=number_of_bins_for_discriminator;i++){
		float x = 1. - h1_disc_back->Integral(1,i);
		float y = 1. - h1_disc_signal->Integral(1,i);
		//cout << i << ". bin: x = " << x << " , y = " << y << endl;
		if ( x > 0.001 && y > 0.001 && x < 1.0 && y < 1.0) ROC->SetPoint(int(i),x,y);
	}
	//}

	/*inicijalizacija platna, crtanje i spremanje u pdf*/
	//{
	TCanvas *canv;
	canv = new TCanvas("canvas for discriminator and ROC","Profile histogram example",200, 10,700,500);
	canv->Divide(2,2); //podjela platna na 2 stupca
	
	canv->cd(1); //postavljanje prvog odjeljka ("pad") kao aktivnog
	h1_disc_signal_10->Draw("HISTO"); //nacrtaj histogram na danom platnu
	h1_disc_back_10->Draw("HISTO same");
	leg1->Draw();
	
	canv->cd(2);
	gPad->SetLeftMargin(0.15);
	ROC->SetTitle("Receiver operating characteristic");
	ROC->GetXaxis()->SetTitle("Background efficiency");
	ROC->GetYaxis()->SetTitle("Signal efficiency");
	ROC->SetMinimum(0.95);
	ROC->SetMaximum(1.0);
	ROC->GetXaxis()->SetLimits(0.00,0.05);
	ROC->SetMarkerStyle(20);
	ROC->SetMarkerSize(0.4);
	ROC->Draw("AP");
	
	canv->cd(3);
	h2_mass_KD_back->Draw("COLZ");
	//COLZ - opcija za draw koja crta i paletu boja
	//vise na https://root.cern/doc/master/classTHistPainter.html -> Options supported for 2D histograms 
	h2_mass_KD_back->SetStats(0);
	h2_mass_KD_back->SetTitle("m_{4l} vs D^{kin} for q #bar{q} #rightarrow ZZ");
	h2_mass_KD_back->GetXaxis()->SetTitle("m_{4l} [GeV]");
	h2_mass_KD_back->GetYaxis()->SetTitle("D^{kin}");
	
	canv->cd(4);
	h2_mass_KD_signal->Draw("COLZ");
	//COLZ - opcija za draw koja crta i paletu boja
	//vise na https://root.cern/doc/master/classTHistPainter.html -> Options supported for 2D histograms 
	h2_mass_KD_signal->SetStats(0);
	h2_mass_KD_signal->SetTitle("m_{4l} vs D^{kin} for gluon-gluon fusion");
	h2_mass_KD_signal->GetXaxis()->SetTitle("m_{4l} [GeV]");
	h2_mass_KD_signal->GetYaxis()->SetTitle("D^{kin}");
	
	canv->SaveAs("Histogram_Z5.pdf");
	canv->SaveAs("Histogram_Z5.png");
	canv->SaveAs("Histogram_Z5.root");
	//}
	
	/*brisanje pokazivaca*/
	//{
	delete leg1;
	delete canv;
	delete ROC;
	//}
}

void Analyzer::DefaultFit(){
	TF1 *BW = new TF1("BW","([0]*[1])/(pow(x*x-[2]*[2], 2)+0.25*[1]*[1])",110,150);
	TF1 *Q = new TF1("Q","[0] + [1]*x + [2]*x*x",110,150);
	TF1 *SUM = new TF1("BW+Q","([0]*[1])/(pow(x*x-[2]*[2], 2)+0.25*[1]*[1]) + [3] + [4]*x + [5]*x*x",110,150);
	BW->SetParameter(0,2.04149e+04);
	BW->SetParameter(1,8.29917e+02);
	BW->SetParameter(2,1.24443e+02);
	Q->SetParameter(0,5.18024e+01);
	Q->SetParameter(1,-6.21294e-01);
	Q->SetParameter(2,2.45079e-03);
	BW->SetParName(0,"D");
	BW->SetParName(1,"#Gamma");
	BW->SetParName(2,"M");
	Q->SetParName(0,"A");
	Q->SetParName(1,"B");
	Q->SetParName(2,"C");
	SUM->SetParameter(0,pow(10,4));
	SUM->SetParameter(1,800);
	SUM->SetParameter(2,125);
	SUM->SetParameter(3,50);
	SUM->SetParameter(4,-0.1);
	SUM->SetParameter(5,-0.01);
	/*najbolje
	SUM->SetParameter(0,pow(10,4));
	SUM->SetParameter(1,800);
	SUM->SetParameter(2,125);
	SUM->SetParameter(3,-10);
	SUM->SetParameter(4,-0.1);
	SUM->SetParameter(5,-0.01);*/
	SUM->SetParName(0,"D");
	SUM->SetParName(1,"#Gamma");
	SUM->SetParName(2,"M");
	SUM->SetParName(3,"A");
	SUM->SetParName(4,"B");
	SUM->SetParName(5,"C");
	
	h1_mass_s_plus_b->Add(h1_mass_signal);
	h1_mass_s_plus_b->Add(h1_mass_back);
	h1_mass_s_plus_b->GetXaxis()->SetRangeUser(110,150);
	h1_mass_s_plus_b->Fit(SUM, "0");
	
	SUM->SetTitle("Fit functions");
	BW->SetLineColor(kGreen);
	BW->SetLineWidth(1);
	Q->SetLineColor(kBlue);
	Q->SetLineWidth(1);
	SUM->SetLineColor(kRed);
	SUM->SetLineWidth(1);
	SUM->GetXaxis()->SetTitle("x"); 
	SUM->GetYaxis()->SetTitle("f(x)");
	
	h1_mass_s_plus_b->GetXaxis()->SetTitle("m_{4l} [GeV]"); 
	h1_mass_s_plus_b->GetYaxis()->SetTitle("Events / 2 GeV");
	h1_mass_s_plus_b->SetTitle("Sum of gg #rightarrow ZZ and q  #bar{q} #rightarrow ZZ events");
	gStyle->SetOptFit();
	
	/*legenda*/
	//{
	TLegend *leg1;
	leg1 = new TLegend(0.5,0.75,0.9,0.9,"");
	leg1->SetTextSize(.035);
	leg1->AddEntry(BW, "signal - B-W", "l");
	leg1->AddEntry(Q, "background - Q", "l");
	leg1->AddEntry(SUM, "signal+background", "l");
	//}
	
	/*inicijalizacija platna, crtanje i spremanje u pdf*/
	//{
	TCanvas *canv; //stvaranje platna
	canv = new TCanvas("canvas for Z1","Profile histogram example",200, 10,700,500);
	canv->Divide(2);
	
	canv->cd(1);
	gPad->SetLeftMargin(0.15);
	SUM->Draw();
	Q->Draw("same");
	BW->Draw("same");
	leg1->Draw();
	
	canv->cd(2);
	gPad->SetLeftMargin(0.15);
	h1_mass_s_plus_b->Draw("PE1X0");
	canv->SaveAs("Z1.pdf"); //spremi platno kao...
	canv->SaveAs("Z1.png");
	canv->SaveAs("Z1.root");
	//}
	
	/*brisanje pokazivaca*/
	//{
	delete BW;
	delete Q;
	delete SUM;
	delete h1_mass_s_plus_b;
	delete canv;
	//}
}

void Analyzer::MaximumLikelihoodFit(){
	TF1 *FIT = new TF1("BW+Q+BW","([0]*[1])/(pow(x*x-[2]*[2], 2)+0.25*[1]*[1]) + [6]+[7]*x+[8]*x*x + ([3]*[4])/(pow(x*x-[5]*[5], 2)+0.25*[4]*[4])",110,150);
	FIT->SetParName(0,"D_{q#bar{q}#rightarrowZZ}");
	FIT->SetParameter(0,1e+04);
	FIT->SetParName(1,"#Gamma_{q#bar{q} #rightarrowZZ}");
	FIT->SetParameter(1,800);
	FIT->SetParName(2,"M_{q#bar{q}#rightarrowZZ}");
	FIT->SetParameter(2,90);
	FIT->SetParName(3,"D_{gg#rightarrowZZ}");
	FIT->SetParameter(3,1e+04);
	FIT->SetParName(4,"#Gamma_{gg#rightarrowZZ}");
	FIT->SetParameter(4,900);
	FIT->SetParName(5,"M_{gg#rightarrowZZ}");
	FIT->SetParameter(5,125);
	FIT->SetParName(6,"A");
	FIT->SetParameter(6,-20);
	FIT->SetParName(7,"B");
	FIT->SetParameter(7,0.1);
	FIT->SetParName(8,"C");
	FIT->SetParameter(8,-1e-04);
		
	h1_mass_s_plus_b_2->Add(h1_mass_signal);
	h1_mass_s_plus_b_2->Add(h1_mass_back);
	h1_mass_s_plus_b_2->Fit(FIT, "L");
	
	h1_mass_s_plus_b_2->GetXaxis()->SetTitle("m_{4l} [GeV]"); 
	h1_mass_s_plus_b_2->GetYaxis()->SetTitle("Events / 2 GeV");
	h1_mass_s_plus_b_2->SetTitle("Sum of gg #rightarrow ZZ and q  #bar{q} #rightarrow ZZ events");
	gStyle->SetOptFit();
	
	TCanvas *canv; //stvaranje platna
	canv = new TCanvas("canvas for Z2","Profile histogram example",200, 10,700,500);
	gPad->SetLeftMargin(0.15);
	h1_mass_s_plus_b_2->Draw("PE1X0");
	canv->SaveAs("Z2.pdf"); //spremi platno kao...
	canv->SaveAs("Z2.png");
	canv->SaveAs("Z2.root");
	
	/*brisanje pokazivaca*/
	//{
	delete FIT;
	delete h1_mass_s_plus_b_2;
	delete canv;
	//}
}