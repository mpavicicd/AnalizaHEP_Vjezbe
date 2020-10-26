#include "ElementaryParticle.h"
#include "Analyzer.h"

int main () {
	Analyzer *pok;
	pok->ConvertTxtToRootFile();
	delete pok;
  /*srand((int)time(0));
  int i;
  int pxH, pyH, pzH;
  ofstream File("Analysis.txt");
  ElementaryParticle *pok1, *pok2, *pok3;
  for(i=0; i<10000; i++){
	pok1 = new ElementaryParticle(124.97,"Higgsov bozon",true);
	pok2 = new ElementaryParticle();
	pok3 = new ElementaryParticle();
	pxH = rand() % 200 - 100;
	pyH = rand() % 200 - 100;
	pzH = rand() % 200 - 100;
	pok1->energija(pxH,pyH,pzH);
	pok1->bosonDecay(*pok2, *pok3);
	File << pok2->imecestice <<"\t"<< pok2->masacestice <<"\t"<< pok2->ifbozon <<"\t"<< pok2->en <<"\t"<< pok2->px <<"\t"<< pok2->py <<"\t"<< pok2->pz <<"\t"<< pok2->pT <<"\t"<< pok3->imecestice <<"\t"<< pok3->masacestice <<"\t"<< pok3->ifbozon <<"\t"<< pok3->en <<"\t"<< pok3->px <<"\t"<< pok3->py <<"\t"<< pok3->pz <<"\t"<< pok3->pT << endl;
  }
  delete pok1;
  delete pok2;
  delete pok3;
  File.close();*/
  return 0;
}