#ifndef __STAR__
#define __STAR__
/*****************************************************************************  
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *  
 *                                                                           *  
 * Creation Date  : may 2018                                                 *  
 * Last update    :                                                          *  
 *---------------------------------------------------------------------------*  
 * Decription:                                                               *  
 *     The Star class defines a "star" by its metlallicity, initial          *
 *     rotational velocity and a table of yields (Yield class) for each      *
 *     isotope/element                                                       *
 *---------------------------------------------------------------------------*  
 * Comment:                                                                  *  
 *                                                                           *  
 *                                                                           *  
 *****************************************************************************/ 

// project headers
#include "yield.hpp"

// ROOT headers
#include "TGraph.h"

// STL headers
#include <utility>
#include <map>
#include <string>


class Star 
{
   public:
      // constructors
      Star();
      Star(double, double);
      virtual ~Star();

      // overloading operators
      // <
      bool operator<(const Star& star) const {
         return (m_Metallicity+m_InitialVelocity) < 
                (star.m_Metallicity + star.m_InitialVelocity);
      }
      // ==
      bool operator==(const Star& star) const {
         return (m_Metallicity == star.m_Metallicity) && 
                (m_InitialVelocity == star.m_InitialVelocity);
      }
      // []
      Yield operator[](const std::string& isotope) {                         
         return m_YieldTable[isotope];                                                          
      }                                                                         

      // methods
      TGraph*  getIsotopicGraph(const std::string&);
      TGraph*  getIsotopicRatioGraph(const std::string&, const std::string&, double = 1);
      void     clear();
      void     print() const;

   public:
      // setters
      void setMetallicity(const double metal)                        {m_Metallicity = metal;}
      void setInitialVelocity(const double velocity)                 {m_InitialVelocity = velocity;}
      void setYield(const std::string& isotope, const Yield& yield) {
         m_YieldTable.insert(std::pair<std::string,Yield>(isotope,yield));
      }
      // getters
      double getMetallicity() const               {return m_Metallicity;}
      double getInitialVelocity() const           {return m_InitialVelocity;}
      Yield& getYield(const std::string& isotope) {return m_YieldTable[isotope];}

   private:
      double                        m_Metallicity;       // in Z_sun
      double                        m_InitialVelocity;   // in m.s^-1
      std::map<std::string, Yield>  m_YieldTable;
};

#endif
