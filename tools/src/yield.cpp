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
     m_isLog10(1),
     m_grYield(0)
{
}



Yield::Yield(std::vector<double> mass, std::vector<double> yield)
   : m_stellarMass(mass), 
     m_yield(yield),
     m_minMass(0),
     m_maxMass(0),
     m_isLog10(1),
     m_grYield(0)
{
   // check if vectors have same size
   if (m_stellarMass.size() != m_yield.size()) {
      std::cout << "Yield: mass and yield don't have same size" << '\n';
      std::cout << " mass  -> size = " << m_stellarMass.size() << '\n';
      std::cout << " yield -> size = " << m_yield.size() << '\n';
   }

   // find min/max mass
   m_minMass = mass[0];
   m_maxMass = mass[mass.size()-1];
}



Yield::~Yield()
{
//   std::cout << "Yield::~Yield avant " << m_grYield << '\n';
//   if (m_grYield) {delete m_grYield; std::cout << "deleting tgraph" << '\n';}
//   std::cout << "Yield::~Yield apres " << m_grYield << '\n';
}



// Evaluate yield for a given mass 
// If mass is lower/higher than minimum/maximum mass, then lower/higher yield 
// is returned
// If m_isLog10 = 1, yield interpolation is done in log(y) v.s log(m) (default)
// If m_isLog10 = 0, yield interpolation is done in lin(y) v.s.lin(m)
double Yield::eval(double mass) const
{
   unsigned int size = m_stellarMass.size();
   if (size < 3) {
      std::cout << "Yield::Eval(): more than two masses needed for interpolation" << '\n';  
   }

   // interpolation is in log(y) v.s. log(m)
   if (m_isLog10) mass = log10(mass);

   // cases where mass exceeds mass range
   double yield;
   if (mass < m_minMass) {
      yield = m_yield[0];
      if (m_isLog10) yield = pow(10, yield);
      return yield;
   }
   if (mass > m_maxMass) {
      yield = m_yield[m_yield.size()-1];
      if (m_isLog10) yield = pow(10, yield);
      return yield;
   }

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

   yield = yieldLow + dydm * (mass - massLow);
   if (m_isLog10) yield = pow(10, yield);
   return yield;
}



// Integrate a given yield over a salpeter IMF (dN/dm) given in number of stars 
// per unit of mass. This corresponds to a typical dN/dm = m^-2.35 law
// If normalizedToMeanMass = 1, the yield is divided by the mean mass derived
// from the previous IMF: int_minf^msup mdN/dm * dm (case in LC17)
double Yield::integrateIMF(double slope, bool normalizedToMeanMass) const
{
   // define min/max range in integration range depending whether yields and
   // masses are in log10 or linear
   double massLowEdge  = m_minMass;
   double massHighEdge = m_maxMass;
   if (m_isLog10) {
      massLowEdge  = pow(10, massLowEdge);
      massHighEdge = pow(10, massHighEdge);
   }

   // integration step
   double massStep = 0.1;    // solar mass
   // for some reasons, casting to int rest one unit in nbSteps!!!!
   double nbSteps  = (massHighEdge - massLowEdge) / massStep;
//   std::cout << "nbsteps = " << massHighEdge << "\t" << massLowEdge << "\t" << nbSteps << '\n';

   // integrate over IMF (m^-slope)
   double integral = 0;
   for (unsigned int i = 0; i < nbSteps; ++i) {   // loop on masses
      double massLow   = massLowEdge + i*massStep;
      double massHigh  = massLow + massStep;
      double yieldLow  = eval(massLow);
      double yieldHigh = eval(massHigh);
      integral += (yieldLow  * pow(massLow, -slope) + 
                   yieldHigh * pow(massHigh, -slope));
//      std::cout << i << "\t" << massLow << "\t" << massHigh << "\t" << yieldLow << "\t" << yieldHigh << "\t" << integral << '\n';
   } // end loop on masses
   integral *= 0.5 * massStep;

   // normalized IMF over [m_minMass; m_maxMass]
   double norm = (1-slope) / (pow(massHighEdge, 1-slope) - pow(massLowEdge, 1-slope));
   integral *= norm;
//   std::cout << norm << '\n';

   double meanMass = 1;
   if (normalizedToMeanMass) {
      meanMass = norm * (pow(massHighEdge, 2-slope) - pow(massLowEdge, 2-slope)) / (2-slope);
   }

   return integral / meanMass;
}



void Yield::clear()
{
   m_stellarMass.clear();
   m_yield.clear();
}



TGraph* Yield::getGraph()
{
   // if TGraph not created, create it
   if (!m_grYield) {
      unsigned int size = m_stellarMass.size();
      m_grYield = new TGraph(size);
      for (unsigned int i = 0; i < size; ++i) {   // comment
         double mass  = m_stellarMass[i];
         double yield =  m_yield[i];
         if (m_isLog10) {
            mass  = pow(10, mass);
            yield = pow(10, yield);
         }
         m_grYield->SetPoint(i, mass, yield);
      } // end comment
   }

   return m_grYield;
}



void Yield::print() const
{
   std::cout << '\n';
   std::cout << "/////////////// Yield::print() ///////////////" << '\n';
   std::cout << "Yield information" << '\n';
   std::cout << " + Mass = ";
   for (unsigned int i = 0; i < m_stellarMass.size(); ++i) {   // loop on stellar masses
      double mass  = m_stellarMass[i];
      if (m_isLog10) mass  = pow(10, mass);
      std::cout << mass << "\t";
   } // end loop on stellar masses
   std::cout << '\n';
   std::cout << " + Yield = ";
   for (unsigned int i = 0; i < m_yield.size(); ++i) {   // loop on yields
      double yield =  m_yield[i];
      if (m_isLog10) yield  = pow(10, yield);
      std::cout << yield << "\t";
   } // end loop on yields
   std::cout << '\n';
}
