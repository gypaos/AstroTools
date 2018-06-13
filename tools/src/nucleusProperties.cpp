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
#include <sstream>
#include <algorithm>


NucleusProperties::NucleusProperties()
   : m_name("unknown"),
     m_atomicCharge(0),
     m_massNumber(0),
     m_massExcess(0),
     m_massExcessUncertainty(0),
     m_massExcessExperimental(1),
     m_halfLifeString("unknown"),
     m_halfLife(0),
     m_halfLifeUncertainty(0),
     m_halfLifeUpperLower(" "),
     m_spinParity("unknown"),
     m_spin(0),
     m_parity("unknown")
{
}



NucleusProperties::NucleusProperties(const std::string& name, const int atomicCharge, 
                                     const int massNumber, const double massExcess, 
                                     const double massExcessUncertainty, 
                                     const std::string& halfLife, const std::string& spinParity)
   : m_name(name),
     m_atomicCharge(atomicCharge),
     m_massNumber(massNumber),
     m_massExcess(massExcess),
     m_massExcessUncertainty(massExcessUncertainty),
     m_massExcessExperimental(1),
     m_halfLifeString(halfLife),
     m_halfLife(0),
     m_halfLifeUncertainty(0),
     m_halfLifeUpperLower(" "),
     m_spinParity(spinParity),
     m_spin(0),
     m_parity("unknown")
{
   // parse jpi / half-life strings
   parseSpinParity();
   parseHalfLife();
}



NucleusProperties::~NucleusProperties()
{
}



// return isotope name in latex syntax (useful for ROOT labeling axis)
std::string NucleusProperties::getNameLatex() const
{
   std::string nameLatex = m_name;

   size_t found = m_name.find_last_of("0123456789");
   if (found != std::string::npos) {
      nameLatex.insert(found+1, "}");
      nameLatex.insert(0, "^{");
   }

   return nameLatex;
}



// m_halfLifeString is parsed to get half life and half life uncertainties in s
void NucleusProperties::parseHalfLife()
{
   // define variables
   std::string item;

   // converting half life in seconds
   double  s = 1;
   double  m = 60*s;
   double  h = 60*m;
   double  d = 24*h;
   double  y = 365*d;
   double ky = 1e3*y;
   double My = 1e6*y;
   double Gy = 1e9*y;
   double ms = 1e-3*s;
   double us = 1e-6*s;
   double ns = 1e-9*s;
   double ps = 1e-12*s;
   double fs = 1e-15*s;
   double as = 1e-18*s;
   double zs = 1e-21*s;
   double ys = 1e-24*s;
   double conversion = s;

   // local copy with removed white space
   std::string halfLifeString = m_halfLifeString;
   halfLifeString.erase(std::remove_if(halfLifeString.begin(), halfLifeString.end(), ::isspace), halfLifeString.end());

   // stable isotope case
   if (halfLifeString.find("stbl") != std::string::npos) {
      m_halfLife            = -1;
      m_halfLifeUncertainty =  0;
   }
   else if (halfLifeString.find("p-unst") != std::string::npos) {
      m_halfLife            = -2;
      m_halfLifeUncertainty =  0;
   }
   else if (halfLifeString.length() == 0) {
      m_halfLife            = -3;
      m_halfLifeUncertainty =  0;
   }
   else { // main case
      std::stringstream sHalfLifeString(m_halfLifeString);
      unsigned int index = 0;
      while (getline(sHalfLifeString, item, ' ')) {                              
         if (item.compare(0,1,"") != 0) {                              
            if (index == 0) { // half life
               size_t found = item.find(">");
               if (found != std::string::npos) {
                  m_halfLifeUpperLower = ">";
                  item.replace(found, 1, "");
               }
               found = item.find("<");
               if (found != std::string::npos) {
                  m_halfLifeUpperLower = "<";
                  item.replace(found, 1, "");
               }
               m_halfLife = atof(item.c_str());
            }
            if (index == 1) { // units
               if (item.compare(0,1,"s")  == 0) conversion = s;
               if (item.compare(0,1,"m")  == 0) conversion = m;
               if (item.compare(0,1,"h")  == 0) conversion = h;
               if (item.compare(0,1,"d")  == 0) conversion = d;
               if (item.compare(0,1,"y")  == 0) conversion = y;
               if (item.compare(0,2,"ky") == 0) conversion = ky;
               if (item.compare(0,2,"My") == 0) conversion = My;
               if (item.compare(0,2,"Gy") == 0) conversion = Gy;
               if (item.compare(0,2,"ys") == 0) conversion = ys;
               if (item.compare(0,2,"zs") == 0) conversion = zs;
               if (item.compare(0,2,"as") == 0) conversion = as;
               if (item.compare(0,2,"fs") == 0) conversion = fs;
               if (item.compare(0,2,"ps") == 0) conversion = ps;
               if (item.compare(0,2,"ns") == 0) conversion = ns;
               if (item.compare(0,2,"us") == 0) conversion = us;
               if (item.compare(0,2,"ms") == 0) conversion = ms;
            }
            if (index == 2) {
               m_halfLifeUncertainty = atof(item.c_str());
            }
            index++;
         }                                                             
      }                                                                
      // apply conversion to seconds
      m_halfLife            *= conversion;
      m_halfLifeUncertainty *= conversion;
   }
}



void NucleusProperties::parseSpinParity()
{
}



void NucleusProperties::clear()
{
   m_name                     = "unknown";
   m_atomicCharge             = 0;
   m_massNumber               = 0;
   m_massExcess               = 0;
   m_massExcessUncertainty    = 0;
   m_massExcessExperimental   = 1;
   m_halfLifeString           = "unknown";
   m_halfLife                 = 0;
   m_halfLifeUncertainty      = 0;
   m_halfLifeUpperLower       = " ";
   m_spinParity               = "unknown";
   m_spin                     = 0;
   m_parity                   = "unknown";
}



void NucleusProperties::print() const
{
   std::cout << std::endl;
   std::cout << "/////////////// NucleusProperties::print() ///////////////" << std::endl;
   std::cout << "NucleusProperties information" << std::endl;
   std::cout << " + Isotope: " << m_name << "\t(Z = " << m_atomicCharge << ", A = " << m_massNumber << ")\tJpi = " << m_spinParity << std::endl;
   std::cout << " + Mass excess: " << m_massExcess << " +/- " << m_massExcessUncertainty << " keV" << std::endl;
   std::cout << " + Half life: " << m_halfLifeString << "\t(" << m_halfLifeUpperLower << " " << m_halfLife << " +/- " << m_halfLifeUncertainty << " s)" << std::endl;
   std::cout << " + Jpi: " << m_spinParity << std::endl;
}
