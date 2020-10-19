#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include <cmath>
#include <fstream>


using namespace std;

class ElementaryParticle {
	  public:
		float masacestice;
		string imecestice;
		bool ifbozon;
		double en, px, py, pz; //elementi cetverovektora
		double pT;
		ElementaryParticle(float masacestice, string imecestice, bool ifbozon);
		ElementaryParticle();
		void printInfo();
		void energija(double px1, double py1, double pz1);
		void printTrans();
		void bosonDecay(ElementaryParticle &obj1, ElementaryParticle &obj2);
};