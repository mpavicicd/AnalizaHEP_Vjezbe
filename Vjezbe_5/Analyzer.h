//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Oct 28 12:30:04 2020 by ROOT version 6.22/02
// from TTree Tree/Vjezbe_4
// found on file: Analysis.root
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
#include <TLorentzVector.h>

// Header file for the classes stored in the TTree if any.
using namespace std;

class Analyzer {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   string          *Name1;
   Double_t        Mass1;
   Bool_t          IfBoson1;
   Double_t        En1;
   Double_t        px1;
   Double_t        py1;
   Double_t        pz1;
   Double_t        pT1;
   string          *Name2;
   Double_t        Mass2;
   Bool_t          IfBoson2;
   Double_t        En2;
   Double_t        px2;
   Double_t        py2;
   Double_t        pz2;
   Double_t        pT2;

   // List of branches
   TBranch        *b_Name1;   //!
   TBranch        *b_Mass1;   //!
   TBranch        *b_IfBoson1;   //!
   TBranch        *b_En1;   //!
   TBranch        *b_px1;   //!
   TBranch        *b_py1;   //!
   TBranch        *b_pz1;   //!
   TBranch        *b_pT1;   //!
   TBranch        *b_Name2;   //!
   TBranch        *b_Mass2;   //!
   TBranch        *b_IfBoson2;   //!
   TBranch        *b_En2;   //!
   TBranch        *b_px2;   //!
   TBranch        *b_py2;   //!
   TBranch        *b_pz2;   //!
   TBranch        *b_pT2;   //!

   Analyzer(TTree *tree=0);
   virtual ~Analyzer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   public:
		void		PlotHistogram();
};

#endif

#ifdef Analyzer_cxx
Analyzer::Analyzer(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Analysis.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("Analysis.root");
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

   // Set object pointer
   Name1 = 0;
   Name2 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Name1", &Name1, &b_Name1);
   fChain->SetBranchAddress("Mass1", &Mass1, &b_Mass1);
   fChain->SetBranchAddress("IfBoson1", &IfBoson1, &b_IfBoson1);
   fChain->SetBranchAddress("En1", &En1, &b_En1);
   fChain->SetBranchAddress("px1", &px1, &b_px1);
   fChain->SetBranchAddress("py1", &py1, &b_py1);
   fChain->SetBranchAddress("pz1", &pz1, &b_pz1);
   fChain->SetBranchAddress("pT1", &pT1, &b_pT1);
   fChain->SetBranchAddress("Name2", &Name2, &b_Name2);
   fChain->SetBranchAddress("Mass2", &Mass2, &b_Mass2);
   fChain->SetBranchAddress("IfBoson2", &IfBoson2, &b_IfBoson2);
   fChain->SetBranchAddress("En2", &En2, &b_En2);
   fChain->SetBranchAddress("px2", &px2, &b_px2);
   fChain->SetBranchAddress("py2", &py2, &b_py2);
   fChain->SetBranchAddress("pz2", &pz2, &b_pz2);
   fChain->SetBranchAddress("pT2", &pT2, &b_pT2);
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
