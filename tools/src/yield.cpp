/*****************************************************************************  
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *  
 *                                                                           *  
 * Creation Date  : may 2018                                                 *  
 * Last update    :                                                          *  
 *---------------------------------------------------------------------------*  
 * Decription:                                                               *  
 *     This class holds yield = f(stellar mass) and provides some operations *
 *     such as yield interpolation, integration over Salpeter IMF..          *  
 *---------------------------------------------------------------------------*  
 * Comment:                                                                  *  
 *                                                                           *  
 *                                                                           *  
 *****************************************************************************/ 
 
// project header
#include "yield.hpp"

// C++ headers
#include <iostream>


Yield::Yield()
   : m_stellarMass(),
     m_yield(),
     m_minMass(0),
     m_maxMass(0),
     m_grYield(0)
{
}



Yield::Yield(std::vector<double> mass, std::vector<double> yield)
   : m_stellarMass(mass), 
     m_yield(yield),
     m_minMass(0),
     m_maxMass(0),
     m_grYield(0)
{
   // check if vectors have same size
   if (m_stellarMass.size() != m_yield.size()) {
      std::cout << "Yield: mass and yield don't have same size" << std::endl;
      std::cout << " mass  -> size = " << m_stellarMass.size() << std::endl;
      std::cout << " yield -> size = " << m_yield.size() << std::endl;
   }

   // find min/max mass
   m_minMass = mass[0];
   m_maxMass = mass[mass.size()-1];
}



double Yield::eval(double mass)
{
   unsigned int size = m_stellarMass.size();
   if (size < 3) {
      std::cout << "Yield::Eval(): more than two masses needed for interpolation" << std::endl;  
   }

   // interpolation is in log(y) v.s. log(m)
   mass = log10(mass);

   // cases where mass exceeds mass range
   if (mass < m_minMass) return pow(10, m_yield[0]);
   if (mass > m_maxMass) return pow(10, m_yield[m_yield.size()-1]);

   // general case
   // assumes m_stellarMass is sorted strictly monotonic increasing
   // find left edge of interpolation interval
   unsigned int i = 0;
   if (mass >= m_stellarMass[size - 2]) {
      i = size - 2;
   }
   else {
      while (mass > m_stellarMass[i+1] ) i++;
   }

   double massLow  = m_stellarMass[i], massHigh  = m_stellarMass[i+1]; 
   double yieldLow = m_yield[i],       yieldHigh = m_yield[i+1];
   double dydm = (yieldHigh - yieldLow) / (massHigh - massLow);
   return pow(10, yieldLow + dydm * (mass - massLow));
}



double Yield::integrateIMF()
{
   return 0;
}



void Yield::clear()
{
   m_stellarMass.clear();
   m_yield.clear();
}



TGraph* Yield::getGraph()
{
   // if TGraph not created, do it
   if (!m_grYield) {
      unsigned int size = m_stellarMass.size();
      m_grYield = new TGraph(size);
      for (unsigned int i = 0; i < size; ++i) {   // comment
         m_grYield->SetPoint(i, pow(10, m_stellarMass[i]), pow(10, m_yield[i]));
      } // end comment
   }

   return m_grYield;
}



void Yield::print() const
{
   std::cout << std::endl;
   std::cout << "/////////////// Yield::print() ///////////////" << std::endl;
   std::cout << "Yield information" << std::endl;
   std::cout << " + Mass = ";
   for (unsigned int i = 0; i < m_stellarMass.size(); ++i) {   // loop on stellar masses
      std::cout << pow(10, m_stellarMass[i]) << "\t";
   } // end loop on stellar masses
   std::cout << std::endl;
   std::cout << " + Yield = ";
   for (unsigned int i = 0; i < m_yield.size(); ++i) {   // loop on yields
      std::cout << pow(10, m_yield[i]) << "\t";
   } // end loop on yields
   std::cout << std::endl;
}
