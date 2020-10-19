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
		cout << "p_T = " << sqrt(px*px + py*py) << endl;
	}
	void ElementaryParticle::bosonDecay(ElementaryParticle &obj1, ElementaryParticle &obj2) {
		int r;
		double px1, px2, py1, py2, pz1, pz2;
		if(ifbozon!=1) //a - ako nije bozon
			cout << "Raspad nije moguc." << endl;
		else {
			r = rand() % 1000;
			if(r < 214){ //21.4% slucajeva raspad na W bozone (0-213)
				cout << "Raspad na W bozone." << endl;
				obj1.imecestice = "W bozon";
				obj2.imecestice = "W bozon";
				//trebalo bi dodati postavljanje mase i ifbozon
			}
			else if(r >= 214 && r < 278){ //6.4% slucajeva raspad na tau leptone (214-277)
				cout << "Raspad na tau leptone." << endl;
				obj1.imecestice = "tau lepton";
				obj2.imecestice = "tau lepton";
				//trebalo bi dodati postavljanje mase i ifbozon
			}
			else if(r >= 278 && r < 304){ //2.6% slucajeva raspad na tau leptone (278-303)
				cout << "Raspad na Z bozone." << endl;
				obj1.imecestice = "Z bozon";
				obj2.imecestice = "Z bozon";
				//trebalo bi dodati postavljanje mase i ifbozon
			}
			else{
				cout << "Raspad na b kvarkove." << endl;
				obj1.imecestice = "b kvark";
				obj2.imecestice = "b kvark";
				//trebalo bi dodati postavljanje mase i ifbozon
			}
			px1 = px * (double)(rand() % 1000)/1000;
			px2 = px - px1;
			py1 = py * (double)(rand() % 1000)/1000;
			py2 = py - py1;
			pz1 = pz * (double)(rand() % 1000)/1000;
			pz2 = pz - pz1;
			obj1.energija(px1,py1,pz1);
			obj2.energija(px2,py2,pz2);
		}
	}
