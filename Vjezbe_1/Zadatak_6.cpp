#include <iostream>
using namespace std;

class ElementaryParticle {
    float masacestice;
    string imecestice;
    bool ifbozon;
  public:
	ElementaryParticle(float m, string name, bool isboson) {
	masacestice = m;
	imecestice = name;
	ifbozon = isboson;
	}
    void printInfo() {
    	cout << "masa cestice: " << masacestice << endl;
    	cout << "ime cestice: " << imecestice << endl;
    	cout << "je li cestica bozon: " << ifbozon << endl;
    }
};



int main () {
  ElementaryParticle Higgs(125.09,"Higgsov bozon",true);
  ElementaryParticle topkv(173.1,"top kvark",false);
  ElementaryParticle *Zbozon;
  Zbozon = new ElementaryParticle(80.4,"Z bozon",true);
  Higgs.printInfo();
  topkv.printInfo();
  Zbozon->printInfo();
  delete Zbozon;
  return 0;
}
