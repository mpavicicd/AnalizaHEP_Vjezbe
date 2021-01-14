//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jan 13 12:07:29 2021 by ROOT version 6.22/06
// from TTree Tree/Height of woman in ...
// found on file: /home/public/data/Height/Height.root
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

using namespace std;

// Header file for the classes stored in the TTree if any.

class Analyzer {
public :
   TTree		*fChain;   //!pointer to the analyzed TTree or TChain
   Int_t		fCurrent; //!current Tree number in a TChain
   TRandom		*rand;
   TH1F			*histo_H0;
   TH1F			*histo_H1;
   TCanvas		*canv;
   TLine		*line;
   TLatex		*label;
   TLegend		*leg;

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         height;

   // List of branches
   TBranch        *b_height;   //!

   Analyzer(TTree *tree=0);
   virtual ~Analyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   void				CalculateTobs();
   void				FirstTask();
   void				SecondTask(TString country);
   
private:
	int		H0; //index of country for H0: 0-Spain, 1-France, 2-Italy, 3- Netherland
	int		H1; //index of country for H1
	int		bin_T_obs;
	double	T_obs;
	double	sum;
	double	sum_H0;
	double	sum_H1;
	double	p_value_H0;
	double	p_value_H1;
	double	mean[4] = {168.0, 164.7, 166.1, 170.3};
	double	sigma[4] = {7.0, 7.1, 6.5, 7.5};
	TString	title;
	TString	output;

	double	significance;

	

	
};

#endif

#ifdef Analyzer_cxx
Analyzer::Analyzer(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/public/data/Height/Height.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/public/data/Height/Height.root");
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

   fChain->SetBranchAddress("height", &height, &b_height);
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
