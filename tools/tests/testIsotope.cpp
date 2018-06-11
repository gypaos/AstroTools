// project headers
#include "nucleusProperties.hpp"

// C++ headers
#include <iostream>
using namespace std;


int main()
{
   ////////////////////////////////////////////////////////////////////////////
   // NucleusProperties class test
   cout << "********** test NucleusProperties class *****************************" << endl; 
   NucleusProperties h1("1H", 1, 1, 8071.3171, 0.0005, 613.9, "1/2+");
   h1.print();
   h1.clear();
   h1.print();
   h1.setName("2H");
   h1.setAtomicCharge(1);
   h1.setMassNumber(2);
   h1.setMassExcess(13135.7217, 0.0001);
   h1.setHalfLife(-1);
   h1.setSpinParity("1+");
   h1.print();

   return 0;
}
