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
	h1_time_fit = new TH1F("Distribution of half-life measurement", "", 60, 0, 12);
	double sum_t = 0;
	double minimum;
	double tau_hat_1, tau_hat_3, tau_hat_4;
	double sigma_fit, sigma_analytical, sigma_exact_lower, sigma_exact_upper;
	double x_for_min;
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
   
	/*uredivanje svojstava histograma - nazivi osi, boja linije, ispuna, yrange (maximum)*/
	//{
	h1_time_fit->GetXaxis()->SetTitle("t [s]"); //postavlja oznaku na x-osi
	h1_time_fit->GetYaxis()->SetTitle("Events / 0.2 GeV"); //postavlja oznaku na y-osi
	h1_time_fit->SetLineColor(kBlue+1); //postavlja boju linije
	h1_time_fit->SetFillStyle(1001); //postavlja stil ispune
	h1_time_fit->SetFillColor(kBlue+1);//postavlja boju ispune
	h1_time_fit->SetTitle("Fit for    #frac{c}{#tau} e^{-t/#tau}");
	//}
	
	/*fit*/
	//{
	cout << "\t\t**********Fit of exponential decay PDF**********" << endl; //za Z1
	TF1 *PDF = new TF1("PDF","([1]/[0])*exp(-x/[0])",0,12);
	PDF->SetParameter(0,1);
	PDF->SetParName(0,"#tau");
	PDF->SetParameter(1,100);
	PDF->SetParName(1,"const.");
	h1_time_fit->Fit(PDF,"l");
	tau_hat_1 = PDF->GetParameter(0);
	sigma_fit = PDF->GetParError(0);
	
	
	TF1 *Likelihood = new TF1("Likelihood","(2.00231e+02/x)*exp(-1/x)",0,10); //za Z2
	Likelihood->SetTitle("Likelihood function L(#tau) = #frac{c}{#tau} e^{-t/#tau} for t = 1 s");
	Likelihood->GetXaxis()->SetTitle("#tau [s]"); //postavlja oznaku na x-osi
	Likelihood->GetYaxis()->SetTitle("L(#tau)"); //postavlja oznaku na y-osi
	
	TF1 *LnL = new TF1("-2lnL","2*[0]*log(x)+2*[1]/x",1.14,1.35); //za Z4
	LnL->SetParameter(0,nentries);
	LnL->SetParName(0,"N");
	LnL->SetParameter(1,sum_t);
	LnL->SetParName(0,"sum_t");
	LnL->SetTitle("Maximum Likelihood -2lnL = 2Nln  #tau + #frac{2}{#tau} #Sigma_{i}t_{i}");
	LnL->GetXaxis()->SetTitle("#tau [s]");
	LnL->GetYaxis()->SetTitle("-2lnL(#tau)");
	
	//cout << "tau_hat from fit of exponential decay: " <<  tau_hat_1 << endl; //Z1
	//cout << "sigma from fit of exponential decay: " <<  sigma_fit << endl;
	
	tau_hat_3 = sum_t/nentries; //za Z3
	//cout << "tau_hat from analytical solution: " << tau_hat_3 << endl;
	sigma_analytical = sqrt(-pow(tau_hat_3,3)/(nentries*tau_hat_3 - 2*sum_t));
	cout << "sigma from analytical solution = " << sigma_analytical << endl;
	
	tau_hat_4 = LnL->GetMinimumX(1.14, 1.35, 1.E-10, 100, false); //Z4
	//cout << "tau_hat from minimisation of -2lnL: " << tau_hat_4 << endl; 
	minimum = LnL->GetMinimum(1.14, 1.35, 1.E-10, 100, false); //Z5
	x_for_min = LnL->GetMinimumX(1.14, 1.35, 1.E-10, 100, false);
	sigma_exact_lower = x_for_min - LnL->GetX(minimum+1, 1.15, 1.24, 1.E-10, 100, false);
	sigma_exact_upper = LnL->GetX(minimum+1, 1.24, 1.35, 1.E-10, 100, false) - x_for_min;
	//cout << "sigma lower from -2lnL curve: " << sigma_exact_lower << endl;
	//cout << "sigma upper from -2lnL curve: " << sigma_exact_upper << endl;
	
	cout << endl << "\t\t**********Results comparison**********" << endl;
	cout << "method\t\t\t\ttau_hat\t\tsigma" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "fit of exponential decay\t" << tau_hat_1 << "\t\t+- " << sigma_fit << endl;
	cout << "analytical solution\t\t" << tau_hat_3 << "\t\t+- " << sigma_analytical << endl;
	cout << "from -2lnL curve\t\t" << tau_hat_4 << "\t\t- " << sigma_exact_lower << "\t+ " << sigma_exact_upper << endl << endl;
	
	gStyle->SetOptFit();
	//}
	
	/*inicijalizacija platna, crtanje i spremanje u pdf*/
	//zakomentirano jer ne treba za V8
	//{
	TCanvas *canv1, *canv2, *canv4; //stvaranje platna
	//konstruktor za platno (const char* name, const char* title, Int_t wtopx, Int_t wtopy, Int_t ww, Int_t wh)
	//name - canvas name;	title - canvas title;	wtopx,wtopy - pixel coordinates of the top left corner of the canvas (if wtopx < 0 the menubar is not shown);
	//ww - canvas size in pixels along X;	wh - canvas size in pixels along Y
	canv1 = new TCanvas("Canvas for Z1","Profile histogram example",200, 10,700,500);
	canv2 = new TCanvas("Canvas for Z2","Profile histogram example",200, 10,700,500);
	canv4 = new TCanvas("Canvas for Z4","Profile histogram example",200, 10,700,500);
	
	canv1->cd();
	h1_time_fit->Draw();
	
	canv2->cd();
	Likelihood->Draw();
	
	canv4->cd();
	LnL->Draw();
	
	canv1->SaveAs("Z1.pdf");
	canv1->SaveAs("Z1.png");
	canv1->SaveAs("Z1.root");
	canv2->SaveAs("Z2.pdf");
	canv2->SaveAs("Z2.png");
	canv2->SaveAs("Z2.root");
	canv4->SaveAs("Z4.pdf");
	canv4->SaveAs("Z4.png");
	canv4->SaveAs("Z4.root");
	//}
	
	/*brisanje pokazivaca*/
	//{
	delete h1_time_fit;
	delete PDF;
	delete Likelihood;
	delete LnL;
	delete canv1;
	delete canv2;
	delete canv4;
	//}
}
