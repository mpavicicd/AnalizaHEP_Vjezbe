#include "ElementaryParticle.h"

	ElementaryParticle::ElementaryParticle(float m, string name, bool isboson) { //konstruktor
	masacestice = m;
	imecestice = name;
	ifbozon = isboson;
	}
	ElementaryParticle::ElementaryParticle() { //overload konstruktora
	}
    void ElementaryParticle::printInfo() {
    	cout << "masa cestice: " << masacestice << endl;
    	cout << "ime cestice: " << imecestice << endl;
    	cout << "je li cestica bozon: " << ifbozon << endl;
    }
	void ElementaryParticle::energija(double px1, double py1, double pz1) { //racun energije
		px = px1;
		py = py1;
		pz = pz1;
		en = sqrt(px*px + py*py + pz*pz + masacestice*masacestice);
	}
	void ElementaryParticle::printTrans() { //racun transverzalne kol gibanja
		cout << "transverzalna kolicina gibanja: " << sqrt(px*px + py*py) << endl;
	}
	void ElementaryParticle::bosonDecay(ElementaryParticle obj1, ElementaryParticle obj2) {
		int r;
		if(ifbozon!=1) //a - ako nije bozon
			cout << "Raspad nije moguc." << endl;
		r = rand() % 1000;
		if(r < 214) //21.4% slucajeva raspad na W bozone (0-213)
			cout << "Raspad na W bozone." << endl;
		else if(r >= 214 && r < 278) //6.4% slucajeva raspad na tau leptone (214-277)
			cout << "Raspad na tau leptone." << endl;
		else if(r >= 278 && r < 304) //2.6% slucajeva raspad na tau leptone (278-303)
			cout << "Raspad na Z bozone." << endl;
		else
			cout << "Raspad na b kvarkove." << endl;
	}
