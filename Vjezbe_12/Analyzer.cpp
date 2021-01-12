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
		cout << ele_pt << endl;
	}
}

void Analyzer::LoopBackground(){
		Init(Background);
		if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;
		histo_back[0]->Fill(ele_pt);
		histo_back[1]->Fill(scl_eta);
		histo_back[2]->Fill(ele_hadronicOverEm);
		histo_back[3]->Fill(ele_gsfchi2);
		histo_back[4]->Fill(ele_fbrem);
		histo_back[5]->Fill(ele_ep);
		histo_back[6]->Fill(ele_eelepout);
		histo_back[7]->Fill(ele_pfChargedHadIso);
		//if(jentry == nentries-1)
		//	cout << "background: "<< ele_pt << endl;
	}
}

void Analyzer::LoopSignal(){
		Init(Signal);
		if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntriesFast();

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;
		histo_sign[0]->Fill(ele_pt);
		histo_sign[1]->Fill(scl_eta);
		histo_sign[2]->Fill(ele_hadronicOverEm);
		histo_sign[3]->Fill(ele_gsfchi2);
		histo_sign[4]->Fill(ele_fbrem);
		histo_sign[5]->Fill(ele_ep);
		histo_sign[6]->Fill(ele_eelepout);
		histo_sign[7]->Fill(ele_pfChargedHadIso);
		//if(jentry == nentries-1)
		//	cout << "signal: "<< ele_pt << endl;
	}
}

void Analyzer::PlotDistributions(){
	canv = new TCanvas("canv","canv",900,900);
	canv->Divide(2,4);
	for(int i=0; i<8; i++){
		histo_back[i]->SetStats(0);
		histo_sign[i]->SetStats(0);
		histo_back[i]->SetLineColor(kBlue);
		histo_sign[i]->SetLineColor(kRed);
		histo_back[i]->GetXaxis()->SetTitle(variables[i]);
		histo_back[i]->GetYaxis()->SetTitle("Events");
		histo_sign[i]->GetXaxis()->SetTitle(variables[i]);
		histo_sign[i]->GetYaxis()->SetTitle("Events");
		
		legend[i] = new TLegend(0.8,0.8,0.95,0.95,"");
		legend[i]->SetTextSize(.035);
		legend[i]->AddEntry(histo_sign[i], "signal", "f");
		legend[i]->AddEntry(histo_back[i], "background", "f");
		
		canv->cd(i+1);
		gPad->SetLeftMargin(0.15);

		//racun koji histogram ima visi peak tako da tog plota prvog i prema tom odredi yrange
		maxS = histo_sign[i]->GetBinContent(histo_sign[i]->GetMaximumBin());
		maxB = histo_back[i]->GetBinContent(histo_back[i]->GetMaximumBin());
		if(maxB >= maxS){
			histo_back[i]->Draw();
			histo_sign[i]->Draw("same");
		}
		else{
			histo_sign[i]->Draw();
			histo_back[i]->Draw("same");
		}
		legend[i]->Draw();
	}

	canv->SaveAs("Distributions.pdf");
	
	delete canv;
}

void Analyzer::MVATraining(){
   // The explicit loading of the shared libTMVA is done in TMVAlogon.C, defined in .rootrc
   // if you use your private .rootrc, or run from a different directory, please copy the
   // corresponding lines from .rootrc
 
   // Methods to be processed can be given as an argument; use format:
   //
   //     mylinux~> root -l TMVAClassification.C\‍(\"myMethod1,myMethod2,myMethod3\"\‍)
 
   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();
 
   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use; //kod Tamare izbrisano
 
   // Neural Networks (all are feed-forward Multilayer Perceptrons)
   Use["MLP"]             = 0; // Recommended ANN
   Use["MLPBFGS"]         = 0; // Recommended ANN with optional training method
   Use["MLPBNN"]          = 0; // Recommended ANN with BFGS training method and bayesian regulator
   Use["CFMlpANN"]        = 0; // Depreciated ANN from ALEPH
   Use["TMlpANN"]         = 0; // ROOT's own ANN

   // Boosted Decision Trees
   Use["BDT"]             = 1; // uses Adaptive Boost
   Use["BDTG"]            = 0; // uses Gradient Boost
   Use["BDTB"]            = 0; // uses Bagging
   Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
   Use["BDTF"]            = 0; // allow usage of fisher discriminant for node splitting
   // ---------------------------------------------------------------
   std::cout << std::endl;
   std::cout << "==> Start TMVAClassification" << std::endl; //----------------------------------------------------------------
 
   // Here the preparation phase begins

   // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
   TString outfileName( "TMVA.root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
 
   // Create the factory object. Later you can choose the methods
   // whose performance you'd like to investigate. The factory is
   // the only TMVA object you have to interact with
   //
   // The first argument is the base of the name of all the
   // weightfiles in the directory weight/
   //
   // The second argument is the output file for the training results
   // All TMVA output can be suppressed by removing the "!" (not) in
   // front of the "Silent" argument in the option string
   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
 
   TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");
   // If you wish to modify default settings
   // (please check "src/Config.h" to see all available global options)
   //
   //    (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
   //    (TMVA::gConfig().GetIONames()).fWeightFileDir = "myWeightDirectory";
 
   // Define the input variables that shall be used for the MVA training
   // note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
   // [all types of expressions that can also be parsed by TTree::Draw( "expression" )]
   dataloader->AddVariable( "ele_pt", 'F');
   dataloader->AddVariable( "ele_fbrem", 'F');
   dataloader->AddVariable( "ele_ep", 'F');
   dataloader->AddVariable( "ele_pfChargedHadIso", 'F'); 
 
   // global event weights per tree (see below for setting event-wise weights)
   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;
 
   // You can add an arbitrary number of signal or background trees
   dataloader->AddSignalTree (Signal, signalWeight);
   dataloader->AddBackgroundTree(Background, backgroundWeight);
   // End of tree registration
 
   /*// Set individual event weights (the variables must exist in the original TTree)
   // -  for signal    : `dataloader->SetSignalWeightExpression    ("weight1*weight2");`
   // -  for background: `dataloader->SetBackgroundWeightExpression("weight1*weight2");`
   dataloader->SetBackgroundWeightExpression( "weight" );*/ //kod Tamare ovog nema
 
   // Apply additional cuts on the signal and background samples (can be different)
   TCut mycuts = ""; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
   TCut mycutb = ""; // for example: TCut mycutb = "abs(var1)<0.5";
 
   // Tell the dataloader how to use the training and testing events
   //
   // If no numbers of events are given, half of the events in the tree are used
   // for training, and the other half for testing:
   //
   //    dataloader->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );
   //
   // To also specify the number of testing events, use:
   //
   //    dataloader->PrepareTrainingAndTestTree( mycut,
   //         "NSigTrain=3000:NBkgTrain=3000:NSigTest=3000:NBkgTest=3000:SplitMode=Random:!V" );
   dataloader->PrepareTrainingAndTestTree( mycuts, mycutb,
                                        "nTrain_Signal=1000:nTrain_Background=1000:SplitMode=Random:NormMode=NumEvents:!V" );
 
   // ### Book MVA methods
   //
   // Please lookup the various method configuration options in the corresponding cxx files, eg:
   // src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/optionRef.html
   // it is possible to preset ranges in the option string in which the cut optimisation should be done:
   // "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable
 
   // TMVA ANN: MLP (recommended ANN) -- all ANNs in TMVA are Multilayer Perceptrons
   if (Use["MLP"])
      factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=1:!UseRegulator" );
 
   if (Use["MLPBFGS"])
      factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLPBFGS", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:!UseRegulator" );
 
   if (Use["MLPBNN"])
      factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLPBNN", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=60:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:UseRegulator" ); // BFGS training with bayesian regulators
 
   // CF(Clermont-Ferrand)ANN
   if (Use["CFMlpANN"])
      factory->BookMethod( dataloader, TMVA::Types::kCFMlpANN, "CFMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N"  ); // n_cycles:#nodes:#nodes:...
 
   // Tmlp(Root)ANN
   if (Use["TMlpANN"])
      factory->BookMethod( dataloader, TMVA::Types::kTMlpANN, "TMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N:LearningMethod=BFGS:ValidationFraction=0.3"  ); // n_cycles:#nodes:#nodes:...
 
   // Boosted Decision Trees
   if (Use["BDT"])  // Adaptive Boost
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT",
                           "!H:!V:NTrees=899:MinNodeSize=1.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.3:UseBaggedBoost:BaggedSampleFraction=0.4:SeparationType=GiniIndex:nCuts=100" );
 
   if (Use["BDTG"]) // Gradient Boost
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG",
                           "!H:!V:NTrees=900:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.1:UseBaggedBoost:BaggedSampleFraction=0.1:nCuts=20:MaxDepth=2" );
 
   if (Use["BDTB"]) // Bagging
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTB",
                           "!H:!V:NTrees=900:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20" );
 
   if (Use["BDTD"]) // Decorrelation + Adaptive Boost
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTD",
                           "!H:!V:NTrees=40:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=100:VarTransform=Decorrelate" );
 
   if (Use["BDTF"])  // Allow Using Fisher discriminant in node splitting for (strong) linearly correlated variables
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTF",
                           "!H:!V:NTrees=50:MinNodeSize=2.0%:UseFisherCuts:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=50" );
 
   // For an example of the category classifier usage, see: TMVAClassificationCategory
   //
   // --------------------------------------------------------------------------------------------------
   //  Now you can optimize the setting (configuration) of the MVAs using the set of training events
   // STILL EXPERIMENTAL and only implemented for BDT's !
   //
   //     factory->OptimizeAllMethods("SigEffAtBkg0.01","Scan");
   //     factory->OptimizeAllMethods("ROCIntegral","FitGA");
   //
   // --------------------------------------------------------------------------------------------------
 
   // Now you can tell the factory to train, test, and evaluate the MVAs
   //
   // Train MVAs using the set of training events
   factory->TrainAllMethods();
 
   // Evaluate all MVAs using the set of test events
   factory->TestAllMethods();
 
   // Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();
 
   // --------------------------------------------------------------
 
   // Save the output
   outputFile->Close();
 
   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;
 
   delete factory;
   delete dataloader;
   // Launch the GUI for the root macros
   //if (!gROOT->IsBatch()) TMVA::TMVAGui( outfileName );
}

void Analyzer::MVAanalysis(){
	//##########Plotanje distribucije MVA##################
	TFile *f_tmva = new TFile("TMVA.root");
	tmva_s = (TGraph*)f_tmva->Get("dataset/Method_BDT/BDT/MVA_BDT_S");
	tmva_b = (TGraph*)f_tmva->Get("dataset/Method_BDT/BDT/MVA_BDT_B");
	histo_BvsS = (TH1F*)f_tmva->Get("dataset/Method_BDT/BDT/MVA_BDT_effBvsS");

	percent = histo_BvsS->Interpolate(0.9);


	tmva_s->SetLineColor(kRed);
	tmva_b->SetLineColor(kBlue);
	gStyle->SetOptStat(0);
	tmva_b->SetTitle("Distribution of MVA result for test data");
	//tmva_b->GetXaxis()->SetTitle("");
	//tmva_b->GetYaxis()->SetTitle("");
	tmva_b->SetMaximum(2.4);

	histo_BvsS->SetLineColor(kRed+1);
	histo_BvsS->SetLineWidth(2);
	histo_BvsS->SetTitle("ROC curve for test data");
	histo_BvsS->GetXaxis()->SetTitle("Signal efficiency");
	histo_BvsS->GetYaxis()->SetTitle("Background efficiency");
	line1 = new TLine(0.9, 0, 0.9, percent);
	line2 = new TLine(0, percent, 0.9, percent);
	line1->SetLineWidth(1);
	line2->SetLineWidth(1);
	line1->SetLineStyle(7);
	line2->SetLineStyle(7);
	line1->SetLineColor(kBlack);
	line2->SetLineColor(kBlack);
	text = "S = 90%; B = " + to_string(percent*100) + "%";
	label = new TLatex(0.2, percent+0.003, text);
	label->SetTextSize(0.03);

	legend2 = new TLegend(0.7,0.82,0.95,0.92,"");
	legend2->SetTextSize(.03);
	legend2->AddEntry(tmva_s, "signal", "l");
	legend2->AddEntry(tmva_b, "background", "l");

	canv2 = new TCanvas("canv2","canv2",900,900);
	gPad->SetLeftMargin(0.15);
	tmva_b->Draw();
	tmva_s->Draw("same");
	legend2->Draw();
	canv2->SaveAs("MVA_result.pdf");

	canv3 = new TCanvas("canv3","canv3",900,900);
	gPad->SetLeftMargin(0.15);
	histo_BvsS->Draw();
	line1->Draw();
	line2->Draw();
	label->Draw();
	canv3->SaveAs("Efficiency.pdf");

	cout << "Background efficiency for 90% of signal: "<< 100*percent << endl;

	delete canv2;
}