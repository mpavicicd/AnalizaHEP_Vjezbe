//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jan 20 12:02:54 2021 by ROOT version 6.22/06
// from TTree Tree/DiPhoton events
// found on file: /home/public/data/HiggsSearch/CMSData.root
//////////////////////////////////////////////////////////

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
#include <TRandom.h>
#include <TRandom3.h>
#include <TMultiGraph.h>

using namespace std;

// Header file for the classes stored in the TTree if any.

class Analyzer {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
	TF1			*PDF;
	TH1F		*histo_exp;
	TH1F		*histo_chisq;
	TH1F		*histo_sens;
	TH1F		*histo_inv_mass;
	TCanvas		*canv;
	TRandom3	*r3;
	TGraph		*graph_exp_p_value;
	TGraph		*graph_obs_p_value;
	TLorentzVector	*Higgs;
	TLegend			*leg;
	TMultiGraph		*mg;

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         particle1_px;
   Float_t         particle1_py;
   Float_t         particle1_pz;
   Float_t         particle1_E;
   Float_t         particle2_px;
   Float_t         particle2_py;
   Float_t         particle2_pz;
   Float_t         particle2_E;

   // List of branches
   TBranch        *b_particle1_px;   //!
   TBranch        *b_particle1_py;   //!
   TBranch        *b_particle1_pz;   //!
   TBranch        *b_particle1_E;   //!
   TBranch        *b_particle2_px;   //!
   TBranch        *b_particle2_py;   //!
   TBranch        *b_particle2_pz;   //!
   TBranch        *b_particle2_E;   //!

   Analyzer(TTree *tree=0);
   virtual ~Analyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   void		TestStatistic();
   void		PValue();
   void		InvariantMass();
   
private:
	int			r;
	int			bin_T_obs;
	int			counter;
	double		N_SM;
	double		zeta_SM;
	double		mass;
	double		m;
	double		s_events;
	double		chi_square;
	double		p_value;

};

#endif

#ifdef Analyzer_cxx
Analyzer::Analyzer(TTree *tree) : fChain(0) 
{
	r3 = new TRandom3();
	histo_exp = new TH1F("Histogram of mass distribution", "", 200, 0, 700); //histogram for experiment
	histo_chisq = new TH1F("Histogram for #chi^{2}", "Distribution of test statistic", 200, 0, 50);
	histo_sens = new TH1F("Histogram for calculating sensitivity", "", 200, 0, 700);
	PDF = new TF1("PDF","[0]*exp(((-1.0)*x)/[1])",0,700);
	graph_exp_p_value = new TGraph();
	graph_obs_p_value = new TGraph();

	Higgs = new TLorentzVector();
	histo_inv_mass = new TH1F("Histogram of invariant mass distribution", "Distribution of invariant mass", 200, 0, 700); 

	leg = new TLegend(0.75,0.1,0.9,0.25,"P-value");
	mg = new TMultiGraph();

// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/public/data/HiggsSearch/CMSData.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/public/data/HiggsSearch/CMSData.root");
      }
      f->GetObject("Tree",tree);

   }
   Init(tree);
}

Analyzer::~Analyzer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Analyzer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Analyzer::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Analyzer::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("particle1_px", &particle1_px, &b_particle1_px);
   fChain->SetBranchAddress("particle1_py", &particle1_py, &b_particle1_py);
   fChain->SetBranchAddress("particle1_pz", &particle1_pz, &b_particle1_pz);
   fChain->SetBranchAddress("particle1_E", &particle1_E, &b_particle1_E);
   fChain->SetBranchAddress("particle2_px", &particle2_px, &b_particle2_px);
   fChain->SetBranchAddress("particle2_py", &particle2_py, &b_particle2_py);
   fChain->SetBranchAddress("particle2_pz", &particle2_pz, &b_particle2_pz);
   fChain->SetBranchAddress("particle2_E", &particle2_E, &b_particle2_E);
   Notify();
}

Bool_t Analyzer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Analyzer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Analyzer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Analyzer_cxx
