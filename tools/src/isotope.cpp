/*****************************************************************************  
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *  
 *                                                                           *  
 * Creation Date  : may 2018                                                 *  
 * Last update    :                                                          *  
 *---------------------------------------------------------------------------*  
 * Decription:                                                               *  
 *     The Isotope class holds information concerning abundances and nuclear *  
 *     properties                                                            *  
 *---------------------------------------------------------------------------*  
 * Comment:                                                                  *  
 *                                                                           *  
 *                                                                           *  
 *****************************************************************************/ 

// project header
#include "isotope.hpp"

// C++ headers
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <cmath>


Isotope::Isotope()
   : m_fileNameAbundances("Lodders09.txt"),
     m_fileNameProperties("nubase2016.txt"),
     m_isotopeAbundancesTable(),
     m_isotopePropertiesTable(),
     m_properties(),
     m_abundances()
{
   // construct absolute file name path
   constructFileNames();

   // read abundances and nuclear properties files
   readAbundanceFile();
   readPropertiesFile();
}


Isotope::Isotope(const std::string& fileNameAbundances, 
                 const std::string& fileNameProperties)
   : m_fileNameAbundances(fileNameAbundances),
     m_fileNameProperties(fileNameProperties),
     m_isotopeAbundancesTable(),
     m_isotopePropertiesTable(),
     m_properties(),
     m_abundances()
{
   // construct absolute file name path
   constructFileNames();

   // read abundances and nuclear properties files
   readAbundanceFile();
   readPropertiesFile();
}



Isotope::~Isotope()
{
   clear();
}



// construct file name including full path
void Isotope::constructFileNames()
{
   // append relative path wrt ASTROTOOLS
   m_fileNameAbundances.insert(0, "/data/observations/abundances/");
   m_fileNameProperties.insert(0, "/data/masses/");

   // check and get ASTROTOOLS env. variable 
   char const* tmp = getenv("ASTROTOOLS");                                      
   if (tmp == NULL) {                                                           
      std::cout << "ASTROTOOLS environment variable not defined" << std::endl;  
      exit(1);                                                                  
   } else {                                                                     
      m_fileNameProperties.insert(0, tmp);
      m_fileNameAbundances.insert(0, tmp);
   }                                                                            
}



void Isotope::readAbundanceFile()
{
   if (m_fileNameAbundances.find("Lodders09.txt") != std::string::npos) {
      readAbundanceFile_Lodders09();
   }
   else if (m_fileNameAbundances.find("AG89.txt") != std::string::npos) {
      readAbundanceFile_AG89();
   }
   else {
      std::cout << "Abundances file " << m_fileNameAbundances << " not yet supported" << std::endl;
   }
}



void Isotope::readAbundanceFile_AG89()
{
}



void Isotope::readAbundanceFile_Lodders09()
{
   // variables
   std::string line;
   Abundances abundances; 

   // open file
   std::ifstream inputFile(m_fileNameAbundances.c_str());
   if (inputFile) {
      // skip first 6 lines
      unsigned int nCommentLines = 6;
      for (unsigned int i = 0; i < nCommentLines; i++) getline(inputFile, line);
      while (getline(inputFile, line)) {
         // skip empty lines
         if (line.empty()) continue;
         // skip element lines
         if (line.compare(0,1," ") == 0) continue;
         // get atomic charge & mass number
         unsigned int atomicCharge = atoi(line.substr(0,2).c_str());
         unsigned int massNumber   = atoi(line.substr(7,3).c_str());
         // build isotope name
         std::string elementName = line.substr(3,4);
         elementName.erase(std::remove_if(elementName.begin(), elementName.end(), ::isspace), elementName.end());
         std::stringstream sstm;
         sstm << massNumber << elementName;
         std::string isotopeName = sstm.str();
         // get number of atoms
         double numberOfAtoms = atof(line.substr(21,line.length()-21).c_str());
         // fill NucleusProperties object
         abundances.setName(isotopeName);
         abundances.setAtomicCharge(atomicCharge);
         abundances.setMassNumber(massNumber);
         abundances.setNumberOfAtoms(numberOfAtoms);
         // populate map
         m_isotopeAbundancesTable[isotopeName] = abundances;
         m_isotopeAbundancesTable[isotopeName].print();
         // clear Abundances object
         abundances.clear();
      }
   }
   else {
      std::cout << "Problem opening isotopic abundance file " << m_fileNameAbundances << std::endl;
      exit(1);
   }

   // close file
   inputFile.close();
}



void Isotope::readPropertiesFile()
{
   // variables
   std::string line, item;
   NucleusProperties nucleusProperties; 

   // open file
   std::ifstream inputFile(m_fileNameProperties.c_str());
   if (inputFile) {
      while (getline(inputFile, line)) {
         // skip empty lines
         if (line.empty()) continue;
         // get atomic charge and mass number
         unsigned int atomicCharge = floor(atoi(line.substr(4,4).c_str())/10);
         unsigned int massNumber   = atoi(line.substr(0,3).c_str());
         // get isotope name without trailing white space
         std::string isotopeName   = line.substr(11,6);
         isotopeName.erase(std::remove_if(isotopeName.begin(), isotopeName.end(), ::isspace), isotopeName.end());
         // get mass excess and uncertainty
         // is it determined theoretically or not?
         bool massExcessExperimental = true;
         if (line.compare(24,1,"#") == 0) { // detect theoretically determination
            massExcessExperimental = false;
            line.replace(24,1,".");    // mass excess case
            line.replace(33,1,".");    // mass excess uncertainty case
         }
         double massExcess = atof(line.substr(18,11).c_str());
         double massExcessUncertainty = atof(line.substr(29,9).c_str());
         // get half-life and half-life uncertainty
         std::string halfLife = "";
         if (line.length() > 60) { // must check that halfLife exist
            halfLife = line.substr(60,19);
         }
         std::string spinParity = "";
         if (line.length() > 79) { // must check that Jpi exist
            spinParity = line.substr(79,14);
         }
         // fill NucleusProperties object
         nucleusProperties.setName(isotopeName);
         nucleusProperties.setAtomicCharge(atomicCharge);
         nucleusProperties.setMassNumber(massNumber);
         nucleusProperties.setMassExcess(massExcess, massExcessUncertainty);
         nucleusProperties.setMassExcessExperimental(massExcessExperimental);
         nucleusProperties.setHalfLife(halfLife);
         nucleusProperties.setSpinParity(spinParity);
         // populate map
         m_isotopePropertiesTable[isotopeName] = nucleusProperties;
         // clear NucleusProperties object
         nucleusProperties.clear();
      }
   }
   else {
      std::cout << "Problem opening isotope nuclear properties file " << m_fileNameProperties << std::endl;
      exit(1);
   }

   // close file
   inputFile.close();
}



void Isotope::setIsotope(const std::string& isotope)
{
   //  
   if (m_isotopePropertiesTable.find(isotope) != m_isotopePropertiesTable.end()) {
      m_properties = m_isotopePropertiesTable[isotope];
   }
   else {
      std::cout << isotope << " is not registered in m_isotopePropertiesTable" << std::endl;
      m_properties.clear();
   }

   // 
   if (m_isotopeAbundancesTable.find(isotope) != m_isotopeAbundancesTable.end()) {
      m_abundances = m_isotopeAbundancesTable[isotope];
   }
   else {
      std::cout << isotope << " is not registered in m_isotopeAbundancesTable" << std::endl;
      m_abundances.clear();
   }
}



void Isotope::clear()
{
   m_isotopeAbundancesTable.clear();
   m_isotopePropertiesTable.clear();
}



void Isotope::print() const
{
   std::cout << std::endl;
   std::cout << "/////////////// Isotope::Print() ///////////////" << std::endl;
   std::cout << "Isotope tables information" << std::endl;
   std::cout << " + Nuclear properties file: " << m_fileNameProperties << std::endl;
   std::cout << " + Abundances file: " << m_fileNameAbundances << std::endl;
   std::cout << " + Number of isotopes having nuclear properties: " << m_isotopePropertiesTable.size() << std::endl;
   std::cout << " + Number of isotopes having abundances: " << m_isotopeAbundancesTable.size() << std::endl;

   if (m_properties.getName() != "unknown") m_properties.print();
   if (m_abundances.getName() != "unknown") m_abundances.print();
}
