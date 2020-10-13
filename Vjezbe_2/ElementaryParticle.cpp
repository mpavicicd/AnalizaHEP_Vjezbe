#include "ElementaryParticle.h"

	ElementaryParticle::ElementaryParticle(float m, string name, bool isboson) {
	masacestice = m;
	imecestice = name;
	ifbozon = isboson;
	}
    void ElementaryParticle::printInfo() {
    	cout << "masa cestice: " << masacestice << endl;
    	cout << "ime cestice: " << imecestice << endl;
    	cout << "je li cestica bozon: " << ifbozon << endl;
    }
