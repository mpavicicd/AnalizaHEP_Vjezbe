#include "ElementaryParticle.h"

int main () {
  srand((int)time(0));
  ElementaryParticle *pok1, *pok2;
  pok1 = new ElementaryParticle(125.18,"Higgsov bozon",true);
  pok2 = new ElementaryParticle(1,"Druga cestica",false);
  //pok1->printInfo();
  pok1->energija(1,2,3);
  pok1->printTrans();
  pok1->bosonDecay(*pok1, *pok2);
  delete pok1;
  delete pok2;
  return 0;
}