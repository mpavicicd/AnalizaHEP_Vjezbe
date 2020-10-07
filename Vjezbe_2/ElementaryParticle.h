#include <iostream>
using namespace std;

class ElementaryParticle {
	  public:
		float masacestice;
		string imecestice;
		bool ifbozon;
		ElementaryParticle(float m, string name, bool isboson);
		void printInfo();
};