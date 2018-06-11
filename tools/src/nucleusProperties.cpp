/*****************************************************************************  
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *  
 *                                                                           *  
 * Creation Date  : june 2018                                                *  
 * Last update    :                                                          *  
 *---------------------------------------------------------------------------*  
 * Decription:                                                               *  
 *     This class holds static properties for atomic nuclei                  *
 *---------------------------------------------------------------------------*  
 * Comment:                                                                  *  
 *                                                                           *  
 *                                                                           *  
 *****************************************************************************/ 
 
// project header
#include "nucleusProperties.hpp"

// C++ headers
#include <iostream>


NucleusProperties::NucleusProperties()
   : m_name("unknown"),
     m_atomicCharge(0),
     m_massNumber(0),
     m_massExcess(0),
     m_massExcessUncertainty(0),
     m_massExcessExperimental(1),
     m_halfLife(0),
     m_spinParity("unknown"),
     m_spin(0),
     m_parity("unknown")
{
}



NucleusProperties::NucleusProperties(const std::string& name, const int atomicCharge, 
                                     const int massNumber, const double massExcess, 
                                     const double massExcessUncertainty, 
                                     const double halfLife, const std::string& spinParity)
   : m_name(name),
     m_atomicCharge(atomicCharge),
     m_massNumber(massNumber),
     m_massExcess(massExcess),
     m_massExcessUncertainty(massExcessUncertainty),
     m_massExcessExperimental(1),
     m_halfLife(halfLife),
     m_spinParity(spinParity),
     m_spin(0),
     m_parity("unknown")
{
}



NucleusProperties::~NucleusProperties()
{
}



void NucleusProperties::clear()
{
   m_name                  = "unknown";
   m_atomicCharge          = 0;
   m_massNumber            = 0;
   m_massExcess            = 0;
   m_massExcessUncertainty = 0;
   m_halfLife              = 0;
   m_spinParity            = "unknown";
   m_spin                  = 0;
   m_parity                = "unknown";
}



void NucleusProperties::print() const
{
   std::cout << std::endl;
   std::cout << "/////////////// NucleusProperties::print() ///////////////" << std::endl;
   std::cout << "NucleusProperties information" << std::endl;
   std::cout << " + Isotope: " << m_name << "\t(Z = " << m_atomicCharge << ", A = " << m_massNumber << ")\tJpi = " << m_spinParity << std::endl;
   std::cout << " + Mass excess: " << m_massExcess << " +/- " << m_massExcessUncertainty << " keV" << std::endl;
   std::cout << " + Half life: ";
   if (m_halfLife < 0) std::cout << "stable";
   else if (m_halfLife == 0) std::cout << "unknown";
   else std::cout << m_halfLife << " s";
   std::cout << std::endl;
}
