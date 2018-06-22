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


Abundances::Abundances()
   : m_name("unknown"),
     m_atomicCharge(0),
     m_massNumber(0),
     m_numberOfAtoms(0),
     m_log10Xatoms(0),
     m_log10Xmass(0),
     m_percentElement(0)
{
}



Abundances::~Abundances()
{
}



void Abundances::clear()
{
   m_name           = "unknown";
   m_atomicCharge   = 0;
   m_massNumber     = 0;
   m_numberOfAtoms  = 0;
   m_log10Xatoms    = 0;
   m_log10Xmass     = 0;
   m_percentElement = 0;
}



void Abundances::print() const
{
   std::cout << '\n';
   std::cout << "/////////////// Abundances::print() ///////////////" << '\n';
   std::cout << "Abundances information" << '\n';
   std::cout << " + Isotope: " << m_name <<  "\t(Z = " << m_atomicCharge << ", A = " << m_massNumber << ")" << '\n';
   std::cout << " + N = " << m_numberOfAtoms << " atoms" << '\n';
   std::cout << " + mass fraction = " << pow(10, m_log10Xmass) << '\n';
   std::cout << " + percent of element = " << m_percentElement << " %"  << '\n';
}
