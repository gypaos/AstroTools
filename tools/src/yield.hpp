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
      virtual ~Yield();

      // methods
      double  eval(double) const;
      double  integrateIMF(double = 2.35, bool = 0) const;
      TGraph* getGraph();
      void    clear();
      void    print() const;

   public:
      // setters
      void setStellarMass(const double mass)                {m_stellarMass.push_back(mass);}
      void setStellarMass(const std::vector<double>& mass)  {m_stellarMass = mass;}
      void setYield(const double yield)                     {m_yield.push_back(yield);}
      void setYield(const std::vector<double>&  yield)      {m_yield = yield;}
      void setLog10(const bool isLog10)                     {m_isLog10 = isLog10;}
      // getters
      double getStellarMass(const unsigned int i) const     {return m_stellarMass[i];}
      double getYield(const unsigned int i) const           {return m_yield[i];}

   private:
      std::vector<double>  m_stellarMass;
      std::vector<double>  m_yield;
      double               m_minMass;
      double               m_maxMass;
      // if m_isLog10 = 0/1, m_stellarMass, m_yield, m_minMass and m_maxMass
      // are in lin/log10 scale. Default is 1 (log10)
      bool                 m_isLog10;
      TGraph*              m_grYield;
};

#endif
