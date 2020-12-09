#ifndef Analyzer_h
#define Analyzer_h

#include <iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
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
#include <TF1.h>
#include <TGraphErrors.h>
#include <TLine.h>
#include <TLatex.h>

using namespace std;

// Header file for the classes stored in the TTree if any.

class Analyzer {
   /*user defined variables and functions*/
   public: 
		void	FitFunction();
	private:
		double	a[5] = {9.8, 21.2, 34.5, 39.9, 48.5};
		double	sigma [5] = {1.0, 1.9, 3.1, 3.9, 5.1};
		double	F [5] = {1, 2, 3, 4, 5};
		int		i;
		double	mass_fit, sigma_fit; //varijable za Z1 - fit fje na podatake
		double	theta_an, mass_an, sigma_t_an, sigma_m_an; //varijable za Z2 - analiticko rjesenje
		double	brojnik = 0.0, nazivnik = 0.0;
		double	theta_ex, sigma_t_ex_l, sigma_t_ex_u; //varijable za Z3 - rjesenje iz krivulje
		double	mass_ex, sigma_m_ex_l, sigma_m_ex_u, minCS;
		TGraphErrors	*graph;
		TF1				*FitFunc, *ChiSquare;
		TLine			*lines[5];
		TLatex			*labels[5];
};

#endif