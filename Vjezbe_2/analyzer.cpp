#include "ElementaryParticle.h"

int main () {
  ElementaryParticle Higgs(125.09,"Higgsov bozon",true);
  ElementaryParticle topkv(173.1,"top kvark",false);
  ElementaryParticle Zbozon(80.4,"Z bozon",true);
  ElementaryParticle *pok;
  pok = &Zbozon;
  Higgs.printInfo();
  topkv.printInfo();
  pok->printInfo();
  delete pok;
  return 0;
}