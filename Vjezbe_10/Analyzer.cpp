#define Analyzer_cxx
#include "Analyzer.h"

void Analyzer::FitFunction(){
	//#########Z1#########
	graph = new TGraphErrors(5, F, a, 0, sigma);
	graph->SetTitle("Fit of linear function to data");
	graph->GetXaxis()->SetTitle("F [N]");
	graph->GetYaxis()->SetTitle("a [m/s^{2}]");
	graph->SetMarkerColor(kBlue);
	cout << "\t\t**********Mass fit**********" << endl;
	FitFunc = new TF1("Fit", "x/[0]", 0, 5.5);
	FitFunc->SetParameter(0,1);
	FitFunc->SetParName(0,"m");
	graph->Fit(FitFunc);
	gStyle->SetOptFit();
	mass_fit = FitFunc->GetParameter(0);
	sigma_fit = FitFunc->GetParError(0);
		
	//#########Z2#########
	for(i=0; i<5; i++){
		brojnik = brojnik + (F[i]*a[i])/pow(sigma[i],2);
		nazivnik = nazivnik + pow(F[i]/sigma[i],2);
	}
	theta_an = brojnik/nazivnik;
	mass_an = 1/theta_an;
	sigma_t_an = pow(nazivnik, -0.5);
	sigma_m_an = sigma_t_an / pow(theta_an,2); //racun pogreske mase kao pogreske izvedene velicine
	
	//#########Z3#########
	ChiSquare = new TF1("CS","pow([0]-[1]*x,2)/pow([2],2) + pow([3]-[4]*x,2)/pow([5],2) + pow([6]-[7]*x,2)/pow([8],2) + pow([9]-[10]*x,2)/pow([11],2) + pow([12]-[13]*x,2)/pow([14],2)", 9.5, 11.1);
	for(i=0; i<15; i=i+3){
		ChiSquare->SetParameter(i,a[i/3]);
		ChiSquare->SetParameter(i+1,F[i/3]);
		ChiSquare->SetParameter(i+2,sigma[i/3]);
	}
	ChiSquare->SetTitle("Chi-Square curve with confidence intervals");
	ChiSquare->GetXaxis()->SetTitle("#theta");
	ChiSquare->GetYaxis()->SetTitle("#chi^{2}");
	ChiSquare->SetMinimum(2.0);
	theta_ex = ChiSquare->GetMinimumX(9, 11, 1.E-10, 100, false); //theta_hat je vrijednost od x u kojoj Chi-Square krivulja ima minimum
	mass_ex = 1/theta_ex;
	minCS = ChiSquare->GetMinimum(9, 11, 1.E-10, 100, false); //minimum Chi-Square krivulje
	sigma_t_ex_l = theta_ex - ChiSquare->GetX(minCS+1, 9.5, 10.3, 1.E-10, 100, false); //sigma_theta_lower je razlika theta_hat i vrijednosti od x u kojoj Chi-Square krivulja postize minimum+1
	sigma_t_ex_u = ChiSquare->GetX(minCS+1, 10.3, 10.9, 1.E-10, 100, false) - theta_ex;
	sigma_m_ex_l = sigma_t_ex_l / pow(theta_ex,2); //racun pogreske mase kao pogreske izvedene velicine
	sigma_m_ex_u = sigma_t_ex_u / pow(theta_ex,2);
	
	//#########Z4#########
	lines[0] = new TLine(theta_ex, 2.0, theta_ex, minCS);
	lines[1] = new TLine(theta_ex-sigma_t_ex_l, 2.0, theta_ex-sigma_t_ex_l, minCS+1);
	lines[2] = new TLine(theta_ex+sigma_t_ex_u, 2.0, theta_ex+sigma_t_ex_u, minCS+1);
	lines[3] = new TLine(9.5, minCS, theta_ex, minCS);
	lines[4] = new TLine(9.5, minCS+1, theta_ex+sigma_t_ex_u, minCS+1);
	ChiSquare->GetXaxis()->SetLabelSize(0.025); //velicina brojevnih oznaka
	ChiSquare->GetYaxis()->SetLabelSize(0.025);
	ChiSquare->GetXaxis()->SetLabelColor(kBlue); //boja brojevne oznake
	ChiSquare->GetYaxis()->SetLabelColor(kBlue);
	labels[0] = new TLatex(theta_ex-0.01, 1.75, "#hat#theta");
	labels[1] = new TLatex(theta_ex-sigma_t_ex_l-0.04, 1.75, "#hat{#theta} - #sigma_{#theta}");
	labels[2] = new TLatex(theta_ex+sigma_t_ex_u-0.04, 1.75, "#hat{#theta} + #sigma_{#theta}");
	labels[3] = new TLatex(9.4, minCS-0.05, "#chi^{2}_{min}");
	labels[4] = new TLatex(9.34, minCS+1-0.055, "#chi^{2}_{min} + 1");
	for(i=0; i<5; i++){
		lines[i]->SetLineWidth(1);
		lines[i]->SetLineStyle(9);
		labels[i]->SetTextSize(0.035);
	}
	
	//#########Ispis usporedbe rezultata#########
	cout << endl << "\t\t**********Results comparison**********" << endl;
	cout << "method\t\t\t\tmass_hat\t\tsigma_mass" << endl;
	cout << "----------------------------------------------------------------------------" << endl;
	cout << "fit of linear function\t\t" << mass_fit << "\t\t+- " << sigma_fit << endl;
	cout << "analytical solution\t\t" << mass_an << "\t\t+- " << sigma_m_an << endl;
	cout << "from Chi-Square curve\t\t" << mass_ex << "\t\t- " << sigma_m_ex_l << "\t+ " << sigma_m_ex_u << endl << endl;
	
	/*inicijalizacija platna, crtanje i spremanje*/
	TCanvas *canv1, *canv2;
	canv1 = new TCanvas("Canvas for Z1","Profile histogram example",200, 10,700,500);
	canv2 = new TCanvas("Canvas for Z2","Profile histogram example",200, 10,700,500);
	
	canv1->cd();
	graph->Draw("AP");
	
	canv2->cd();
	ChiSquare->Draw();
	for(i=0; i<5; i++){
		lines[i]->Draw();
		labels[i]->Draw();
	}
	
	canv1->SaveAs("Z1_fit.pdf");
	canv1->SaveAs("Z1_fit.png");
	canv1->SaveAs("Z1_fit.root");
	canv2->SaveAs("Z4_Chi-Square.pdf");
	canv2->SaveAs("Z4_Chi-Square.png");
	canv2->SaveAs("Z4_Chi-Square.root");
	
	/*brisanje pokazivaca*/
	delete graph;
	delete FitFunc;
	delete ChiSquare;
	delete canv1;
	delete canv2;
	delete lines[5];
	delete labels[5];
}
