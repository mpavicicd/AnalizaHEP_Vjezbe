#include "ElementaryParticle.h"

	ElementaryParticle::ElementaryParticle(float m, string name, bool isboson) {
	masacestice = m;
	imecestice = name;
	ifbozon = isboson;
	}
	ElementaryParticle::ElementaryParticle() { //overload konstruktora
	masacestice = 0.;
	imecestice = "";
	ifbozon = false;
	}
    void ElementaryParticle::printInfo() {
		cout << "Particle name: " << imecestice << endl;
    	cout << "Particle mass: " << masacestice << endl;
    	cout << "Particle is ";
		if(!ifbozon) cout << "not ";
		cout << "a boson" << endl;
    }
	void ElementaryParticle::energija(double px1, double py1, double pz1) { //racun energije
		px = px1;
		py = py1;
		pz = pz1;
		en = sqrt(px*px + py*py + pz*pz + masacestice*masacestice);
	}
	float ElementaryParticle::pT() { //racun transverzalne kol gibanja
		return sqrt(px*px + py*py);
	}
	void ElementaryParticle::bosonDecay(ElementaryParticle &obj1, ElementaryParticle &obj2) {
		int r, randx, randy, randz;
		double px1, px2, py1, py2, pz1, pz2;
		if(ifbozon!=1) //a - ako nije bozon
			cout << "Decay not possible." << endl;
		else {
			r = rand() % 1000;
			if(r < 214){ //21.4% slucajeva raspad na W bozone (0-213)
				obj1.imecestice = "W+";
				obj1.masacestice = 80.39;
				obj1.ifbozon = true;
				obj2.imecestice = "W-";
			}
			else if(r >= 214 && r < 278){ //6.4% slucajeva raspad na tau leptone (214-277)
				obj1.imecestice = "tau+";
				obj1.masacestice = 1.77;
				obj1.ifbozon = false;
				obj2.imecestice = "tau-";
			}
			else if(r >= 278 && r < 304){ //2.6% slucajeva raspad na tau leptone (278-303)
				obj1.imecestice = "Z";
				obj1.masacestice = 91.19;
				obj1.ifbozon = true;
				obj2.imecestice = "Z";
			}
			else{
				obj1.imecestice = "b";
				obj1.masacestice = 4.18;
				obj1.ifbozon = false;
				obj2.imecestice = "b";
			}
			obj2.masacestice = obj1.masacestice;
			obj2.ifbozon = obj1.ifbozon;
			
			randx = rand() % 1000;
			px1 = px * (double)randx/1000;
			if(randx == 100){
				randy = 0;
				randz = 0;
			}
			else{
				randy = rand() % (1000 - randx); //ocuvanje momenta
				randz = 1000 - randx - randy;
			}
			py1 = py * (double)randy/1000;
			pz1 = pz * (double)randz/1000;
			px2 = px - px1;
			py2 = py - py1;
			pz2 = pz - pz1;
			obj1.energija(px1,py1,pz1);
			obj2.energija(px2,py2,pz2);
			//cout << "4-vektor druge cestice (E, px, py, pz) iz fje: (" << obj2.en <<", "<< obj2.px <<", "<< obj2.py <<", "<< obj2.pz <<")"<< endl;
		}
	}
