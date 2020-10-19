#include "ElementaryParticle.h"

int main () {
  srand((int)time(0));
  ElementaryParticle *pok1, *pok2, *pok3;
  pok1 = new ElementaryParticle(124.97,"Higgsov bozon",true);
  pok2 = new ElementaryParticle();
  pok3 = new ElementaryParticle();
  //pok1->printInfo();
  pok1->energija(1,1,1);
  pok1->printTrans();
  pok1->bosonDecay(*pok2, *pok3);
  //cout << "4-vektor druge cestice (E, px, py, pz): (" << pok3->en <<", "<< pok3->px <<", "<< pok3->py <<", "<< pok3->pz <<")"<< endl;
  cout << "cestice\tmase\tifbozon\tE1\tpx1\tpy1\tpz1\tE2\tpx2\tpy2\tpz2"<< endl;
  cout << pok2->imecestice <<"\t"<< pok2->masacestice <<"\t"<< pok2->ifbozon <<"\t"<< pok2->en <<"\t"<< pok2->px <<"\t"<< pok2->py <<"\t"<< pok2->pz <<"\t"<< pok3->en <<"\t"<< pok3->px <<"\t"<< pok3->py <<"\t"<< pok3->pz << endl;
  
  delete pok1;
  delete pok2;
  return 0;
}