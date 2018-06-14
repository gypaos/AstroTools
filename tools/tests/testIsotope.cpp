// project headers
#include "nucleusProperties.hpp"
#include "isotope.hpp"

// C++ headers
#include <iostream>
using namespace std;


int main()
{
   ////////////////////////////////////////////////////////////////////////////
   // NucleusProperties class test
   cout << "********** test NucleusProperties class *****************************" << endl; 
   NucleusProperties h1("1H", 1, 1, 8071.3171, 0.0005, "613.9", "1/2+");
   h1.print();
   cout << h1.getNameLatex() << endl;
   h1.clear();
   h1.print();
   h1.setName("2H");
   h1.setAtomicCharge(1);
   h1.setMassNumber(2);
   h1.setMassExcess(13135.7217, 0.0001);
   h1.setHalfLife(-1);
   h1.setSpinParity("1+");
   h1.print();
   cout << endl;

   ////////////////////////////////////////////////////////////////////////////
   // Isotope class test
   cout << "********** test Isotope class *****************************" << endl; 
   Isotope iso;
//   Isotope iso("pipo", "nubase2016.txt");
//   Isotope iso("pipo", "nubtab97.asc");
   iso.print();
   iso.setIsotope("4He");
   cout << "is stable? " << iso.getProperties().isStable() << endl;
   iso.print();
   iso.setIsotope("3Li");
   cout << "is stable? " << iso.getProperties().isStable() << endl;
   iso.print();
   iso.setIsotope("5Be");
   cout << "is stable? " << iso.getProperties().isStable() << endl;
   iso.print();
   iso.setIsotope("7Be");
   cout << "is stable? " << iso.getProperties().isStable() << endl;
   iso.print();
   iso.setIsotope("5H");
   cout << "is stable? " << iso.getProperties().isStable() << endl;
   iso.print();
   iso.setIsotope("16F");
   cout << "is stable? " << iso.getProperties().isStable() << endl;
   iso.print();
   iso.setIsotope("16Ne");
   cout << "is stable? " << iso.getProperties().isStable() << endl;
   iso.print();
   iso.setIsotope("18B");
   cout << "is stable? " << iso.getProperties().isStable() << endl;
   iso.print();
   iso.setIsotope("18Bul");
   cout << "is stable? " << iso.getProperties().isStable() << endl;
   iso.print();
   iso.setIsotope("27Al");
   cout << "is stable? " << iso.getProperties().isStable() << endl;
   iso.print();

   return 0;
}
