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

void Analyzer::CalculateTobs(){ //calculating test statistic for given data
	if (fChain == 0) return;
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;
	sum = 0.0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		sum = sum + height;
   }
	T_obs = sum / nentries;
}

void Analyzer::FirstTask(){
	H0 = 1; //selecting France as H0

//##########building a PDF of test statistic for H0##########
	rand = new TRandom();
	histo_H0 = new TH1F("Histogram for H _{0}", "PDF for test statistic", 1000, 160, 170);
	for(int nE = 0; nE < 1000000; nE++){ //generating 10^6 pseudo-experiments
		sum_H0 = 0.0;
		for(int i=0; i<100; i++){
			sum_H0 = sum_H0 + rand->Gaus(mean[H0], sigma[H0]); //Gauss distribution
		}
			sum_H0 = sum_H0 / 100; //test statistic is average value
			histo_H0 -> Fill(sum_H0);
	}
	histo_H0->Scale(1/histo_H0->Integral());

//test statistic for given data is calculated in the function CalculateTobs()

//##########calculating p-value and significance##########
	bin_T_obs = histo_H0->FindBin(T_obs); //find in which bin of simmulated data fits test statistic of observed data
	p_value_H0 = histo_H0->Integral(bin_T_obs, 1000); //p-value = integral of PDF for test statistic from T_obs to +infinity
	cout << "p value = " << p_value_H0 << endl;
	significance = TMath::Sqrt(2)*TMath::ErfcInverse(2*p_value_H0);
	cout << "significance = " << significance << endl;

	histo_H0->SetLineColor(kBlue);
	histo_H0->SetTitle("PDF of test statistic for France as H  _{0}");
	histo_H0->GetXaxis()->SetTitle("T");
	histo_H0->GetYaxis()->SetTitle("g(T|H_{0})");

	line = new TLine(T_obs, 0, T_obs, histo_H0->Interpolate(mean[H0]));
	line->SetLineColor(kRed);
	label = new TLatex(T_obs-0.5, -0.0005, "T_obs");
	label->SetTextSize(0.03);
	label->SetTextColor(kRed);

	canv = new TCanvas("canv","canv",900,900);
	//gStyle->SetOptStat(0);
	gPad->SetLeftMargin(0.15);
	histo_H0->Draw("histo");
	line->Draw();
	label->Draw();
	canv->SaveAs("Z1_H0-France.pdf");

	delete histo_H0;
	delete line;
	delete label;
	delete canv;
}

void Analyzer::SecondTask(TString country){
	H0 = 0; //selecting Spain as H0
	if(country == "France")
		H1 = 1;
	else if(country == "Italy")
		H1 = 2;
	else if(country == "Netherland")
		H1 = 3;

//##########building a PDF of test statistic for H0 and H1##########
	rand = new TRandom();
	if(H1 == 1){
		histo_H0 = new TH1F("Histogram for H_{0}", "PDF for test statistic", 1000, 162, 171);
		histo_H1 = new TH1F("Histogram for H_{1}", "PDF for test statistic", 1000, 162, 171);
	}
	else if(H1 == 2){
		histo_H0 = new TH1F("Histogram for H_{0}", "PDF for test statistic", 1000, 163, 172);
		histo_H1 = new TH1F("Histogram for H_{1}", "PDF for test statistic", 1000, 163, 172);
	}
	else if(H1 == 3){
		histo_H0 = new TH1F("Histogram for H_{0}", "PDF for test statistic", 1000, 165, 174);
		histo_H1 = new TH1F("Histogram for H_{1}", "PDF for test statistic", 1000, 165, 174);
	}
	for(int nE = 0; nE < 1000000; nE++){ //generating 10^6 pseudo-experiments
		sum_H0 = 0.0;
		sum_H1 = 0.0;
		for(int i=0; i<100; i++){
			sum_H0 = sum_H0 + rand->Gaus(mean[H0], sigma[H0]); //Gauss distribution
			sum_H1 = sum_H1 + rand->Gaus(mean[H1], sigma[H1]);
		}
			sum_H0 = sum_H0 / 100; //test statistic is average value
			sum_H1 = sum_H1 / 100;
			histo_H0 -> Fill(sum_H0);
			histo_H1 -> Fill(sum_H1);
	}
	histo_H0->Scale(1/histo_H0->Integral());
	histo_H1->Scale(1/histo_H1->Integral());

//test statistic for given data is calculated in the function CalculateTobs()

//##########calculating p-value and confidence level##########
	bin_T_obs = histo_H0->FindBin(T_obs); //find in which bin of simmulated data fits test statistic of observed data
	if(mean[H0]>mean[H1]){
		p_value_H0 = histo_H0->Integral(0, bin_T_obs); //P(t<=t_obs | H0)
		p_value_H1 = histo_H1->Integral(bin_T_obs,1000); //P(t>=t_obs | H1)
	}
	else{
		p_value_H0 = histo_H0->Integral(bin_T_obs,1000); //P(t>=t_obs | H0)
		p_value_H1 = histo_H1->Integral(0, bin_T_obs); //P(t<=t_obs | H1)
	}
	cout << "CL (H0-Spain; H1-" << country << ") = " << 1-(p_value_H1/p_value_H0) << endl;

	histo_H0->SetLineColor(kBlue);
	histo_H1->SetLineColor(kOrange);
	histo_H0->SetFillStyle(1001);
	histo_H0->SetFillColorAlpha(kBlue,0.25);
	histo_H1->SetFillStyle(1001);
	histo_H1->SetFillColorAlpha(kOrange,0.25);
	title = "PDF of test statistic for Spain as H  _{0} and " + country + " as H  _{1}";
	histo_H0->SetTitle(title);
	histo_H0->GetXaxis()->SetTitle("T");
	histo_H0->GetYaxis()->SetTitle("g(T|H_{0})");
	histo_H0->SetMaximum(0.006);

	line = new TLine(T_obs, 0, T_obs, histo_H0->Interpolate(mean[H0]));
	line->SetLineColor(kRed);
	label = new TLatex(T_obs-0.5, -0.0005, "T_obs");
	label->SetTextSize(0.03);
	label->SetTextColor(kRed);
	
	leg = new TLegend(0.7,0.8,0.95,0.91,"");
	leg->AddEntry(histo_H0, "Spain", "l");
	leg->AddEntry(histo_H1, country, "l");
	leg->AddEntry(histo_H0,Form("CL = %6.4f%%",100*(1-(p_value_H1/p_value_H0))),""); 
	leg->SetTextSize(.03);
	
	canv = new TCanvas("canv","canv",900,900);
	gStyle->SetOptStat(0);
	gPad->SetLeftMargin(0.15);
	histo_H0->Draw("histo");
	histo_H1->Draw("histo same");
	line->Draw();
	label->Draw();
	leg->Draw();
	gPad->RedrawAxis();
	output = "Z2_H0-Spain_H1-" + country + ".pdf";
	canv->SaveAs(output);
	
	delete histo_H0;
	delete histo_H1;
	delete line;
	delete label;
	delete leg;
	delete canv;
}
