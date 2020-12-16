#define Analyzer_cxx
#include "Analyzer.h"

int Analyzer::Factorial(int N){
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

double Analyzer::Binomial(int r, double p, int N){
	return (Factorial(N)/(Factorial(r)*Factorial(N-r)))*pow(p,r)*pow(1-p,N-r);
}

void Analyzer::ClopperPearson(int r, int N, double CL){
	p_plus = 0.001;
	p_minus = 1.0;
	while(CPUpperLimit(r, p_plus, N) < (1-((1-CL)/2))){ //1- je prebaceno s desne strane
		p_plus = p_plus + 0.001;
		if(p_plus > 1.0)
			break;
	}
	while(CPLowerLimit(r, p_minus, N) < (1-((1-CL)/2))){
	p_minus = p_minus - 0.001;
	if(p_minus < 0.0)
		break;
	}
	//cout << "p_- = " << p_minus << endl;
	//cout << "p_+ = " << p_plus << endl;
}

double Analyzer::CPUpperLimit(int r, double p, int N){ //fja samo vraca sve sume
	sum = 0.0;
	for(int i=r+1; i<=N; i++){
		sum = sum + Binomial(i, p, N);
	}
	//cout << "sum = " << sum << endl;;
	return sum;
}

double Analyzer::CPLowerLimit(int r, double p, int N){
	sum = 0.0;
	for(int i=0; i<=r-1; i++){
		sum = sum + Binomial(i, p, N);
	}
	//cout << "sum = " << sum << endl;;
	return sum;
}

bool Analyzer::CheckInterval(int count, int N, double prob){ //za Z4, fja provjerava je li vjerojatnost u Clopper-Pearson intervalu
	ClopperPearson(count, N, 0.68);
	if (prob <= p_plus && prob >= p_minus)
		return true;
	else
		return false;
}