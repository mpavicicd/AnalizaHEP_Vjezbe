#include <iostream>
using namespace std;

class ElementaryParticle {
	  public:
		float masacestice;
		string imecestice;
		bool ifbozon;
		ElementaryParticle(float masacestice, string imecestice, bool ifbozon);
		void printInfo();
};