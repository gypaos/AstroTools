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

// project header
#include "star.hpp"

// C++ headers
#include <iostream>


Star::Star()
   : m_Metallicity(-1),
     m_InitialVelocity(-1),
     m_YieldTable()
{
}


Star::Star(double metallicity, double velocity)
   : m_Metallicity(metallicity),
     m_InitialVelocity(velocity),
     m_YieldTable()
{
}



Star::~Star()
{
   clear();
}



TGraph* Star::getIsotopicGraph(const std::string& isotope)
{
   return m_YieldTable[isotope].getGraph();
}



TGraph* Star::getIsotopicRatioGraph(const std::string& isotope1, const std::string& isotope2, double factor)
{
   // get isotopic yields
   TGraph *gr1 = m_YieldTable[isotope1].getGraph();
   TGraph *gr2 = m_YieldTable[isotope2].getGraph();

   TGraph *gr = 0;
   if (gr1->GetN() == gr2->GetN()) {
      gr = new TGraph(gr1->GetN());
      for (int i = 0; i < gr1->GetN(); i++) {
         gr->SetPoint(i, gr1->GetX()[i], gr1->GetY()[i] / gr2->GetY()[i] * factor);
      }
   }

   return gr;
}


void Star::clear()
{
   m_YieldTable.clear();
}



void Star::print() const
{
   std::cout << std::endl;
   std::cout << "/////////////// Star::Print() ///////////////" << std::endl;
   std::cout << "Star information" << std::endl;
   std::cout << " + Metallicity: "     << m_Metallicity << std::endl;
   std::cout << " + InitialVelocity: " << m_InitialVelocity << std::endl;
   std::cout << " + Number of isotopes/elements: " << m_YieldTable.size() << std::endl;
   std::cout << " + List of isotopes/elements: ";
   std::map<std::string, Yield>::iterator it; // = m_YieldTable.begin();
   //it = m_YieldTable.begin();
/*   while (it != m_YieldTable.end()) {
      std::cout << it->first << "  ";
      ++it;
   }*/
   std::cout << std::endl;
}
