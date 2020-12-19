#define Analyzer_cxx
#include "Analyzer.h"

int Analyzer::Factorial(int N){ //function for calculation of a factorial
	int fact=1;
	if(N == 0)
		return 1;
	else{
		for(int i=1; i<=N; i++){
			fact = fact*i;
		}
		return fact;
	}
}

double Analyzer::Binomial(int r, double p, int N){ //binomial distribution
	return (Factorial(N)/(Factorial(r)*Factorial(N-r)))*pow(p,r)*pow(1-p,N-r);
}

void Analyzer::ClopperPearson(int r, int N, double CL){ //function for finding upper and lower limits using auxiliary functions for sum of probabilities
	p_plus = 0.001;
	p_minus = 1.0;
	while(CPUpperLimit(r, p_plus, N) < (1-((1-CL)/2))){ //1 - sum = (1-C)/2 -> sum = 1 - (1-C)/2
		p_plus = p_plus + 0.001;
		if(p_plus > 1.0)
			break;
	}
	while(CPLowerLimit(r, p_minus, N) < (1-((1-CL)/2))){
		p_minus = p_minus - 0.001;
		if(p_minus < 0.001){
			p_minus = 0.0;
			break;
		}
	}
}

double Analyzer::CPUpperLimit(int r, double p, int N){ //auxiliary function for calculating sum of probabilities for upper limit
	sum = 0.0;
	for(int i=r+1; i<=N; i++){
		sum = sum + Binomial(i, p, N);
	}
	return sum;
}

double Analyzer::CPLowerLimit(int r, double p, int N){ //auxiliary function for calculating sum of probabilities for lower limit
	sum = 0.0;
	for(int i=0; i<=r-1; i++){
		sum = sum + Binomial(i, p, N);
	}
	return sum;
}

void Analyzer::RepeatClopperPearson(int N, double CL){
//function that repets ClopperPearson for all possibilities of r, prints all intervals and fills histograms for plotting the belt
	histo_p_plus = new TH1F("histogram_for_upper_limit", "Upper limit", N, 0, N);
	histo_p_minus = new TH1F("histogram_for_lower_limit", "Lower limit", N, 0, N);
	cout << endl << "68.27% Clopper Pearson intervals for r successes out of 10 events" << endl;
	cout << "\tr\tp-\t\tp+" << endl;
	for(int r_in=0; r_in<= N; r_in++){
		ClopperPearson(r_in, N, CL); //r, N, C
		cout << "\t" << r_in << "\t" << p_minus << "\t\t" << p_plus << endl;
		histo_p_plus -> SetBinContent(r_in, p_plus); //set the content of bin r_in to value p_plus
		histo_p_minus -> SetBinContent(r_in, p_minus); //set the content of bin r_in to value p_minus
	}
}

void Analyzer::PlotCPBelt(int r){
	histo_p_plus->GetXaxis()->SetTitle("r");
	histo_p_plus->GetYaxis()->SetTitle("p");
	histo_p_plus->SetLineColor(kRed+2);
	histo_p_plus->SetFillStyle(1001);
	histo_p_plus->SetFillColor(kRed-4);
	histo_p_minus->SetLineColor(kRed+2);
	histo_p_minus->SetFillStyle(1001);
	histo_p_minus->SetFillColor(10); //kWhite is not working, 0 either
	histo_p_plus->SetMinimum(0);
	histo_p_plus->SetMaximum(1);
	histo_p_plus->SetTitle("Clopper-Pearson confidence belt");

	histo_p_plus->GetXaxis()->SetLabelSize(0.025); //size of numerical labels
	histo_p_plus->GetYaxis()->SetLabelSize(0.025);

	lines[0] = new TLine(r, 0, r, histo_p_plus->GetBinContent(r));
	lines[1] = new TLine(0, histo_p_plus->GetBinContent(r), r, histo_p_plus->GetBinContent(r));
	lines[2] = new TLine(0, histo_p_minus->GetBinContent(r), r, histo_p_minus->GetBinContent(r));
	labels[0] = new TLatex(r-0.1, -0.06, "r_{0}");
	labels[1] = new TLatex(-1, histo_p_minus->GetBinContent(r)-0.01, "p_{-}(r_{0})");
	labels[2] = new TLatex(-1, histo_p_plus->GetBinContent(r)-0.01, "p_{+}(r_{0})");
	rightline = new TLine(histo_p_plus->GetMaximumBin(), 0, histo_p_plus->GetMaximumBin(), histo_p_plus->GetMaximum()); //right part of the frame that is covered by histogram fill
	upperline = new TLine(0, histo_p_plus->GetMaximum(), histo_p_plus->GetMaximumBin(), histo_p_plus->GetMaximum()); //upper part of the frame that is covered by histogram fill


	for(int i=0; i<3; i++){
		lines[i]->SetLineWidth(1);
		lines[i]->SetLineStyle(7);
		lines[i]->SetLineColor(kBlue);
		labels[i]->SetTextSize(0.035);
		labels[i]->SetTextColor(kBlue);
	}
	gStyle->SetOptStat(0);

	TCanvas *canv;
	canv = new TCanvas("canvas for mass","Profile histogram example",200, 10,700,500);

	histo_p_plus->Draw();
	histo_p_minus->Draw("same");
	rightline->Draw();
	upperline->Draw();
	for(int i=0; i<3; i++){
		lines[i]->Draw();
		labels[i]->Draw();
	}
	gPad->RedrawAxis(); //otherwise segment on x axis is not visible

	canv->SaveAs("Clopper-Pearson_belt.pdf");
	canv->SaveAs("Clopper-Pearson_belt.png");
	canv->SaveAs("Clopper-Pearson_belt.root");
	
	delete canv;
	delete histo_p_minus;
	delete histo_p_plus;
	delete lines[3];
	delete rightline;
	delete upperline;
}

double Analyzer::DiceExperiment(int numofexp, int throws, int sigma){ //simmulation of "numofexp" experiments with "throws" number of dice throws with confidence "sigma"
	int dice, count6, counttrue = 0;
	//dice - random variable
	//count6 - counter for how any times 6 was thrown
	//counttrue - counter for how many times Clopper-Pearson interval covers the true value
	double conf;
	double ptrue = 1./6;
	if (sigma == 1)
		conf = 0.6827;
	else if (sigma == 2)
		conf = 0.9544;
	else{
		cout << "Wrong input of sigma" << endl;
		return 0;
	}
	for(int n=0; n<numofexp; n++){ //repeating the experiment for numofexp times
		count6 = 0;
		for(int i=0; i<throws; i++){ //throwing the dice for throws times
			dice = rand() % 6 + 1;
			if(dice == 6) //counting how many times the number of dice the was 6
				count6 = count6 + 1;
		}
	if(CheckInterval(count6, throws, ptrue, conf))
		counttrue = counttrue + 1;
	}
	return 100.0*counttrue/numofexp;
}

bool Analyzer::CheckInterval(int count, int N, double prob, double conf){ //for Z4, function is checking if Clopper-Pearson interval covers the true value
	ClopperPearson(count, N, conf);
	if (prob <= p_plus && prob >= p_minus)
		return true;
	else
		return false;
}