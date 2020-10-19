#include "ElementaryParticle.h"

int main () {
  srand((int)time(0));
  ElementaryParticle *pok1, *pok2, *pok3;
  pok1 = new ElementaryParticle(125.18,"Higgsov bozon",true);
  pok2 = new ElementaryParticle();
  pok3 = new ElementaryParticle();
  //pok1->printInfo();
  pok1->energija(1,1,1);
  pok1->printTrans();
  pok1->bosonDecay(*pok2, *pok3);
  cout << "4-vektor prve cestice (E, px, py, pz): (" << pok2->en <<", "<< pok2->px <<", "<< pok2->py <<", "<< pok2->pz <<")"<< endl;
  cout << "4-vektor druge cestice (E, px, py, pz): (" << pok3->en <<", "<< pok3->px <<", "<< pok3->py <<", "<< pok3->pz <<")"<< endl;
  cout << "Nastala cestica: " << pok2->imecestice << endl;
  delete pok1;
  delete pok2;
  return 0;
}