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

void Analyzer::TimeDistribution(){ //funkcija za fill grafova i plot distribucija
	/*inicijalizacija i konstruktor histograma za distribuciju*/
	//{
	TH1F *h1_time_fit;
	h1_time_fit = new TH1F("Time histogram", "", 60, 0, 12);
	double sum_t = 0;
	double tau_hat;
	double sigma_t;
	double minimum;
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
		h1_time_fit->Fill(t);
		sum_t = sum_t + t; //za Z3
   }
	//}
   tau_hat = sum_t/nentries; //za Z3
   cout << "Z3 tau_hat = " << tau_hat << endl;
   sigma_t = sqrt(-pow(tau_hat,3)/(nentries*tau_hat - 2*sum_t));
   cout << "Z3 sigma_tau = " << sigma_t << endl;
   
	/*uredivanje svojstava histograma - nazivi osi, boja linije, ispuna, yrange (maximum)*/
	//{
	h1_time_fit->GetXaxis()->SetTitle("t"); //postavlja oznaku na x-osi
	h1_time_fit->GetYaxis()->SetTitle("Events / 0.2 GeV"); //postavlja oznaku na y-osi
	h1_time_fit->SetLineColor(kBlue+1); //postavlja boju linije
	h1_time_fit->SetFillStyle(1001); //postavlja stil ispune
	h1_time_fit->SetFillColor(kBlue+1);//postavlja boju ispune
	//h1_time_fit->SetMaximum(30); //postavljanje yrange
	//h1_time_fit->SetTitle("Transverse momentum for gluon-gluon fusion");
	//}

	/*legenda*/
	//{
	//}
	
	/*fit*/
	//{
	TF1 *PDF = new TF1("PDF","([1]/[0])*exp(-x/[0])",0,12); //za Z1
	PDF->SetParameter(0,1);
	PDF->SetParName(0,"#tau");
	PDF->SetParameter(1,100);
	PDF->SetParName(1,"const");
	h1_time_fit->Fit(PDF,"l");
	
	TF1 *ML = new TF1("ML","(2.00231e+02/x)*exp(-1/x)",0,10); //za Z2
	ML->SetTitle("Maximum Likelihood for 1 measurement");
	
	TF1 *LnL = new TF1("-2lnL","2*[0]*log(x)+2*[1]/x",1.14,1.35); //za Z4
	LnL->SetParameter(0,nentries);
	LnL->SetParName(0,"N");
	LnL->SetParameter(1,sum_t);
	LnL->SetParName(0,"sum_t");
	LnL->SetTitle("Maximum Likelihood");
	cout << "Z5 tau_hat: " << LnL->GetMinimumX(1.14, 1.35, 1.E-10, 100, false) << endl;
	minimum = LnL->GetMinimum(1.14, 1.35, 1.E-10, 100, false);
	cout << "LnL minimum = " << minimum << endl;
	cout << "Z5 sigma lower: " << LnL->GetMinimumX(1.14, 1.35, 1.E-10, 100, false) - LnL->GetX(minimum+1, 1.15, 1.24, 1.E-10, 100, false) << endl;
	cout << "Z5 sigma upper: " << LnL->GetX(minimum+1, 1.24, 1.35, 1.E-10, 100, false) - LnL->GetMinimumX(1.14, 1.35, 1.E-10, 100, false) << endl;
	
	
	gStyle->SetOptFit();
	//}
	
	/*inicijalizacija platna, crtanje i spremanje u pdf*/
	//zakomentirano jer ne treba za V8
	//{
	TCanvas *canv; //stvaranje platna
	//konstruktor za platno (const char* name, const char* title, Int_t wtopx, Int_t wtopy, Int_t ww, Int_t wh)
	//name - canvas name;	title - canvas title;	wtopx,wtopy - pixel coordinates of the top left corner of the canvas (if wtopx < 0 the menubar is not shown);
	//ww - canvas size in pixels along X;	wh - canvas size in pixels along Y
	canv = new TCanvas("canvas for distribution","Profile histogram example",200, 10,700,500);

	//h1_time_fit->Draw(); //nacrtaj histogram na danom platnu
	LnL->Draw();
	
	canv->SaveAs("Z4.pdf");
	canv->SaveAs("Z4.png");
	canv->SaveAs("Z4.root");
	//}
	
	/*brisanje pokazivaca*/
	//{
	delete h1_time_fit;
	delete canv;
	//}
}
