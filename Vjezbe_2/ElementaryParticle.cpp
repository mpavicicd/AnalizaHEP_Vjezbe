#include "ElementaryParticle.h"

	ElementaryParticle::ElementaryParticle(float m, string name, bool isboson) { //konstruktor
	masacestice = m;
	imecestice = name;
	ifbozon = isboson;
	}
    void ElementaryParticle::printInfo() {
		cout << "Particle name: " << imecestice << endl;
    	cout << "Particle mass: " << masacestice << endl;
    	cout << "Particle is ";
		if(!ifbozon) cout << "not ";
		cout << "a boson" << endl;
    }
