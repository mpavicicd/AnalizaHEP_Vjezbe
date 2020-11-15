#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include <cmath>

using namespace std;

class ElementaryParticle {
	  public:
		float masacestice;
		string imecestice;
		bool ifbozon;
		double en, px, py, pz; //elementi cetverovektora
		ElementaryParticle(float masacestice, string imecestice, bool ifbozon);
		ElementaryParticle();
		void printInfo();
		void energija(double px1, double py1, double pz1);
		float pT();
		void bosonDecay(ElementaryParticle &obj1, ElementaryParticle &obj2);
};