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
		int		Factorial(int N);
		double	Binomial(int r, double p, int N);
		void	ClopperPearson(int r, int N, double CL);
		double	CPLowerLimit(int r, double p, int N);
		double	CPUpperLimit(int r, double p, int N);
		void	RepeatClopperPearson(int N, double CL);
		void	PlotCPBelt(int r);
		double	DiceExperiment(int numofexp, int throws, int sigma);
		bool	CheckInterval(int count, int N, double prob, double conf);
		double		p_plus, p_minus;
		TH1F		*histo_p_plus, *histo_p_minus;
		TLine		*rightline, *upperline;
		TLine		*lines[3];
		TLatex		*labels[3];
	private:
		double sum;
};



#endif