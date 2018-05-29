#ifndef __YIELD__
#define __YIELD__
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
 
// ROOT headers
#include "TGraph.h"

// STL header
#include <vector>


class Yield 
{
   public:
      // constructors
      Yield();
      Yield(std::vector<double>, std::vector<double>);

      // methods
      double  eval(double);
      double  integrateIMF();
      TGraph* getGraph();
      void    clear();
      void    print() const;

   public:
      // setters
      void setStellarMass(const double mass)                {m_stellarMass.push_back(mass);}
      void setYield(const double yield)                     {m_yield.push_back(yield);}
      void setStellarMass(const std::vector<double>& mass)  {m_stellarMass = mass;}
      void setYield(const std::vector<double>&  yield)      {m_yield = yield;}
      // getters
      double getStellarMass(const unsigned int i) const     {return m_stellarMass[i];}
      double getYield(const unsigned int i) const           {return m_yield[i];}

   private:
      std::vector<double> m_stellarMass;  // in log10
      std::vector<double> m_yield;        // in log10
      double              m_minMass;
      double              m_maxMass;
      TGraph*             m_grYield;
};

#endif
