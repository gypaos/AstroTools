/*****************************************************************************  
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *  
 *                                                                           *  
 * Creation Date  : june 2018                                                *  
 * Last update    :                                                          *  
 *---------------------------------------------------------------------------*  
 * Decription:                                                               *  
 *     This class holds abundances of atomic nuclei                          *
 *---------------------------------------------------------------------------*  
 * Comment:                                                                  *  
 *                                                                           *  
 *                                                                           *  
 *****************************************************************************/ 
 
// project header
#include "abundances.hpp"

// C++ headers
#include <iostream>
#include <sstream>
#include <algorithm>


Abundances::Abundances()
   : m_name("unknown"),
     m_atomicCharge(0),
     m_massNumber(0),
     m_numberOfAtoms(0)
{
}



Abundances::~Abundances()
{
}



void Abundances::clear()
{
   m_name          = "unknown";
   m_atomicCharge  = 0;
   m_massNumber    = 0;
   m_numberOfAtoms = 0;
}



void Abundances::print() const
{
   std::cout << std::endl;
   std::cout << "/////////////// Abundances::print() ///////////////" << std::endl;
   std::cout << "Abundances information" << std::endl;
   std::cout << " + Isotope: " << m_name <<  "\t(Z = " << m_atomicCharge << ", A = " << m_massNumber << ")" << std::endl;
   std::cout << " + N = " << m_numberOfAtoms << " atoms" << std::endl;
}
