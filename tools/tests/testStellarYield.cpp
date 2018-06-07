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
   // define yield and mass array
   double a_mass[] = {15, 20, 25, 30, 40, 60, 80, 100, 120};
   double a_yield[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
   double a_yield_uni[] = {3, 3, 3, 3, 3, 3, 3, 3, 3};
   vector<double> v_mass, v_yield, v_yield_uni;
   vector<double> v_mass_lin, v_yield_lin, v_yield_uni_lin;
   for (int i = 0; i < sizeof(a_mass) / sizeof(double); i++) {
      v_mass.push_back(log10(a_mass[i]));
      v_yield.push_back(log10(a_yield[i]));
      v_yield_uni.push_back(log10(a_yield_uni[i]));
      v_mass_lin.push_back(a_mass[i]);
      v_yield_lin.push_back(a_yield[i]);
      v_yield_uni_lin.push_back(a_yield_uni[i]);
   }

   // interpolation tests 
   // case where isLog10 = 1 (log(y) v.s. log(m)) interpolation
   Yield yield(v_mass,v_yield);
   yield.print();
   cout << "log10 lower edge "    << yield.eval(10)  << endl;
   cout << "log10 upper edge "    << yield.eval(140) << endl;
   cout << "log10 interpolation " << yield.eval(50)  << endl;
   // case where isLog10 = 0 (lin(y) v.s. lin(m)) interpolation
   Yield yield_lin(v_mass_lin,v_yield_lin);
   yield_lin.setLog10(0);
   yield_lin.print();
   cout << "lin lower edge "    << yield_lin.eval(10)  << endl;
   cout << "lin upper edge "    << yield_lin.eval(140) << endl;
   cout << "lin interpolation " << yield_lin.eval(50)  << endl;

   // getGraph() tests
   cout << "log10 graph size is " << yield.getGraph()->GetN() << endl;
   yield.getGraph()->Print();
   cout << "lin graph size is " << yield_lin.getGraph()->GetN() << endl;
   yield_lin.getGraph()->Print();

   // IMF integration test
   // uniform yield distribution 
   // log10 case
   Yield yield_uni(v_mass, v_yield_uni);
   yield_uni.print();
   cout << "log10 IMF uni = " << yield_uni.integrateIMF(1.35) << endl;
   // lin case
   Yield yield_uni_lin(v_mass_lin, v_yield_uni_lin);
   yield_uni_lin.setLog10(0);
   yield_uni_lin.print();
   cout << "lin IMF uni = " << yield_uni_lin.integrateIMF(1.35) << endl;

   // non uniform yield distribution 
   // log10 case
   yield.print();
   cout << "log10 IMF = " << yield.integrateIMF(1.35) << endl;
   yield_lin.print();
   cout << "lin IMF = " << yield_lin.integrateIMF(1.35) << endl;

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
//   yield_LC17.getGraph()->Print();
//   cout << "IMF = " << yield_LC17.integrateIMF() << endl;

   StellarYield Yields_LC17bis("LC17", "tab_yieldstot_iso_exp.nod", "setR");
   vector<double> velocity;
   velocity.push_back(0); velocity.push_back(150); velocity.push_back(300);
   vector<string> isotope;
   isotope.push_back("26Al"); isotope.push_back("60Fe");
   vector<double> imf(2,0);
   // interpolation in log(y) v.s. log(m)
   cout << "interpolation method: log/log" << endl;
   for (unsigned int vel = 0; vel < velocity.size(); vel++) {
      // define star
      Star star(1, velocity[vel]);
      // initialize
      imf.clear();
      for (unsigned int iso = 0; iso < isotope.size(); iso++) {
         imf[iso] = Yields_LC17bis[star][isotope[iso]].integrateIMF(2.35, 1);
         cout << isotope[iso] << "\t" << velocity[vel] << "\t" << imf[iso] << endl;
      }
      cout << "N(60Fe)/N(26Al) = " << 26./60. * imf[1]/imf[0] * 2.62/0.717 << endl;
   }
   // interpolation in lin(y) v.s. lin(m)
   cout << "interpolation method: lin/lin" << endl;
   Yields_LC17bis.setLog10(0);
   for (unsigned int vel = 0; vel < velocity.size(); vel++) {
      // define star
      Star star(1, velocity[vel]);
      // initialize
      imf.clear();
      for (unsigned int iso = 0; iso < isotope.size(); iso++) {
         imf[iso] = Yields_LC17bis[star][isotope[iso]].integrateIMF(2.35, 1);
         cout << isotope[iso] << "\t" << velocity[vel] << "\t" << imf[iso] << endl;
      }
      cout << "N(60Fe)/N(26Al) = " << 26./60. * imf[1]/imf[0] * 2.62/0.717 << endl;
   }
   // interpolation in lin(y) v.s. lin(m)
   StellarYield Yields_LC17ter("LC17", "tab_yieldstot_iso_exp.nod", "setR", 0);
   cout << "interpolation method: lin/lin" << endl;
   Yields_LC17ter.setLog10(0);
   for (unsigned int vel = 0; vel < velocity.size(); vel++) {
      // define star
      Star star(1, velocity[vel]);
      // initialize
      imf.clear();
      for (unsigned int iso = 0; iso < isotope.size(); iso++) {
         imf[iso] = Yields_LC17ter[star][isotope[iso]].integrateIMF(2.35, 1);
         cout << isotope[iso] << "\t" << velocity[vel] << "\t" << imf[iso] << endl;
      }
      cout << "N(60Fe)/N(26Al) = " << 26./60. * imf[1]/imf[0] * 2.62/0.717 << endl;
   }
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
   cout << "log10 1H: m = 50, y = " << Yields_CL13_R[sa300]["1H"].eval(50) << endl;
   Yields_CL13_R.setLog10(0);
   cout << "lin 1H: m = 50, y = " << Yields_CL13_R[sa300]["1H"].eval(50) << endl;


   delete yield_1H;

   return 0;
}
