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

void Analyzer::FirstTask(){
	canv = new TCanvas("canvas for Z1","Profile histogram example",200, 10,700,500);
	zeta_SM = 100.0;
	PDF->SetParameter(0,500);
	PDF->FixParameter(1,zeta_SM);
	PDF->SetParName(0,"N_{SM}");
	PDF->SetParName(1,"zeta_{SM}");
	for(int nE = 0; nE < 1000; nE++){ //generating 1000 pseudo-experiments
		for(int i=0; i<100000; i++){ //10^5 events for each experiment
			mass = r3->Exp(zeta_SM); //exponential distribution of mass - root exp(a) = exp(-x/a)
			histo_exp->Fill(mass);
		}
		for(int k=10; k<=690; k = k+5){ //fitting in windows; mass range is 0-700
				m = 1.0*k;
				histo_exp->Fit(PDF, "Q", "", m-10, m+10); //window width is 20 GeV
				histo_chisq->Fill(PDF->GetChisquare()); //using chi sqare as test statistic
		}
		histo_exp->Reset(); //otherwise, data would cummulate
	}
	
	histo_chisq->GetXaxis()->SetTitle("T = #chi^{2}");
	histo_chisq->GetYaxis()->SetTitle("g(T|H_{0})");

	gPad->SetLeftMargin(0.15);
	gStyle->SetOptFit();

	histo_chisq->Draw();
	canv->SaveAs("Z1_Test_statistic.pdf");

	delete histo_exp;
	delete canv;
}

void Analyzer::SecondTask(){
	canv = new TCanvas("canvas for Z2","Profile histogram example",200, 10,700,500);
	counter = 0;
	histo_chisq->Scale(1/histo_chisq->Integral()); //normalasing the histogram
	for(int nE = 10; nE <= 690; nE = nE + 5){ //scanning the area [10,690]GeV with 5 Gev steps
		mass = 1.0 * nE;
		s_events = (-1.0)*pow(mass - 190, 2) + 0.5;
		for(int i=0; i<10000; i++){ //10^4 events
			r = rand()%100;
			if(r > s_events){ //background events
				histo_sens->Fill(r3->Exp(zeta_SM));
			}
			else{ //signal events
				histo_sens->Fill(r3->Gaus(mass, 0.0236*mass));
			}
		}
		histo_sens->Fit(PDF, "Q", "", mass-10, mass+10);
		chi_square = PDF->GetChisquare(); //current chi-square = T_obs
		bin_T_obs = histo_chisq->FindBin(chi_square);
		p_value = histo_chisq->Integral(bin_T_obs, 200); //p-value = integral of PDF for test statistic from T_obs to +infinity
		cout << "step: " << counter+1 << "\tmass: " << mass << "\tchi-sq: " << chi_square << "\tp-value: " << p_value << endl;
		histo_sens->Reset();
		graph_p_value->SetPoint(counter,mass,p_value);
		counter++;
	}

	graph_p_value->GetXaxis()->SetTitle("m_{H} [GeV]");
	graph_p_value->GetYaxis()->SetTitle("local p-value");
	
	gPad->SetLogy();
	gPad->SetLeftMargin(0.15);

	graph_p_value->Draw("APL");
	canv->SaveAs("Z2_p-value.pdf");
}
