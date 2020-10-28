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

// Header file for the classes stored in the TTree if any.
using namespace std;

class Analyzer {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   string          *Ime1;
   Double_t        Masa1;
   Bool_t          IfBozon1;
   Double_t        En1;
   Double_t        Px1;
   Double_t        Py1;
   Double_t        Pz1;
   Double_t        Pt1;
   string          *Ime2;
   Double_t        Masa2;
   Bool_t          IfBozon2;
   Double_t        En2;
   Double_t        Px2;
   Double_t        Py2;
   Double_t        Pz2;
   Double_t        Pt2;

   // List of branches
   TBranch        *b_Ime1;   //!
   TBranch        *b_Masa1;   //!
   TBranch        *b_IfBozon1;   //!
   TBranch        *b_En1;   //!
   TBranch        *b_Px1;   //!
   TBranch        *b_Py1;   //!
   TBranch        *b_Pz1;   //!
   TBranch        *b_Pt1;   //!
   TBranch        *b_Ime2;   //!
   TBranch        *b_Masa2;   //!
   TBranch        *b_IfBozon2;   //!
   TBranch        *b_En2;   //!
   TBranch        *b_Px2;   //!
   TBranch        *b_Py2;   //!
   TBranch        *b_Pz2;   //!
   TBranch        *b_Pt2;   //!

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
   Ime1 = 0;
   Ime2 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Ime1", &Ime1, &b_Ime1);
   fChain->SetBranchAddress("Masa1", &Masa1, &b_Masa1);
   fChain->SetBranchAddress("IfBozon1", &IfBozon1, &b_IfBozon1);
   fChain->SetBranchAddress("En1", &En1, &b_En1);
   fChain->SetBranchAddress("Px1", &Px1, &b_Px1);
   fChain->SetBranchAddress("Py1", &Py1, &b_Py1);
   fChain->SetBranchAddress("Pz1", &Pz1, &b_Pz1);
   fChain->SetBranchAddress("Pt1", &Pt1, &b_Pt1);
   fChain->SetBranchAddress("Ime2", &Ime2, &b_Ime2);
   fChain->SetBranchAddress("Masa2", &Masa2, &b_Masa2);
   fChain->SetBranchAddress("IfBozon2", &IfBozon2, &b_IfBozon2);
   fChain->SetBranchAddress("En2", &En2, &b_En2);
   fChain->SetBranchAddress("Px2", &Px2, &b_Px2);
   fChain->SetBranchAddress("Py2", &Py2, &b_Py2);
   fChain->SetBranchAddress("Pz2", &Pz2, &b_Pz2);
   fChain->SetBranchAddress("Pt2", &Pt2, &b_Pt2);
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
