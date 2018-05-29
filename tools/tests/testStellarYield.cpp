// project headers
#include "star.hpp"
#include "yield.hpp"
#include "stellarYield.hpp"

// ROOT headers
#include "TGraph.h"

// C++ headers
#include <iostream>
using namespace std;


int main()
{
   ////////////////////////////////////////////////////////////////////////////
   // Star class test
   cout << "********** test Star class ******************************" << endl; 
   Star star1(0.1, 0);
   Star star2(0.2, 150);
   Star star3(0.2, 150);
   Star star4(0.15, 300);
   Star star5(0.03, 74);

   if (star1 < star2) {
      cout << "operator< good" << endl;
   }
   else {
      cout << "operator< bad" << endl;
   }

   if (star2 == star3) {
      cout << "operator== good" << endl;
   }
   else {
      cout << "operator== bad" << endl;
   }
   cout << endl;

   ////////////////////////////////////////////////////////////////////////////
   // Yield class test
   cout << "********** test Yield class *****************************" << endl; 
   // Yield class
   double a_mass[] = {15, 20, 25, 30, 40, 60, 80, 100, 120};
   double a_yield[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
   vector<double> v_mass, v_yield;
   for (int i = 0; i < sizeof(a_mass) / sizeof(double); i++) {
      v_mass.push_back(log10(a_mass[i]));
      v_yield.push_back(log10(a_yield[i]));
   }

   Yield yield(v_mass,v_yield);
   yield.print();
   cout << "lower edge " << yield.eval(10) << endl;
   cout << "upper edge " << yield.eval(140) << endl;
   cout << "interpolation " << yield.eval(50) << endl;

   cout << "graph size is " << yield.getGraph()->GetN() << endl;
   yield.getGraph()->Print();
   cout << endl;

   ////////////////////////////////////////////////////////////////////////////
   // StellarYield class test
   cout << "********** test StellarYield class **********************" << endl; 
   cout << "********** LC17                    **********************" << endl;
   Star sa0(1, 0);
   Star sa150(1, 150);
   Star sa300(1, 300);
   StellarYield Yields_LC17("LC17", "tab_yieldstot_iso_exp.nod", "setM");
//   StellarYield Yields_LC17("LC17", "tab_yieldstot_ele_exp.dec", "setM");
   Yields_LC17.print();
   Yields_LC17[sa0].print();
   Yields_LC17[sa0]["2H"].print();
   Yields_LC17[sa0].getIsotopicGraph("2H")->Print();
   Yields_LC17[sa150].print();
   Yields_LC17[sa150]["1H"].print();
   Yields_LC17[sa300].print();
   Yields_LC17[sa300]["1H"].print();
   cout << "1H: m = 12, y = " << Yields_LC17[sa300]["1H"].eval(12) << endl;
   cout << "1H: m = 13, y = " << Yields_LC17[sa300]["1H"].eval(13) << endl;
   cout << "1H: m = 14, y = " << Yields_LC17[sa300]["1H"].eval(14) << endl;
   cout << "1H: m = 15, y = " << Yields_LC17[sa300]["1H"].eval(15) << endl;
   TGraph *yield_1H = Yields_LC17[sa300]["1H"].getGraph();
   yield_1H->Print();
   Yield yield_LC17 = Yields_LC17[sa300]["1H"];
   cout << yield_LC17.eval(100) << endl;
   yield_LC17.getGraph()->Print();
   cout << endl;

   cout << "********** test StellarYield class **********************" << endl; 
   cout << "********** CL13                    **********************" << endl;
   StellarYield Yields_CL13_NR("CL13", "", "NR");
   Yields_CL13_NR.print();
   Yields_CL13_NR[sa0].print();
   Yields_CL13_NR[sa0]["56Fe"].print();
   StellarYield Yields_CL13_R("CL13", "", "R");
   Yields_CL13_R.print();
   Yields_CL13_R[sa300].print();
   Yields_CL13_R[sa300]["1H"].print();
   cout << "1H: m = 50, y = " << Yields_CL13_R[sa300]["1H"].eval(50) << endl;

   return 0;
}
