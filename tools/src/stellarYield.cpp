/*****************************************************************************  
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *  
 *                                                                           *  
 * Creation Date  : may 2018                                                 *  
 * Last update    :                                                          *  
 *---------------------------------------------------------------------------*  
 * Decription:                                                               *  
 *     The StellarYield class reads yield files and store the results in the *
 *     Star class.                                                           *
 *---------------------------------------------------------------------------*  
 * Comment:                                                                  *  
 *                                                                           *  
 *                                                                           *  
 *****************************************************************************/ 

// project headers
#include "stellarYield.hpp"
#include "yield.hpp"

// C++ headers
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <cmath>


StellarYield::StellarYield()
   : m_YieldType(),
     m_YieldOption(),
     m_YieldFile(),
     m_isLog10(1),
     m_StellarYieldSet()
{
}


StellarYield::StellarYield(const std::string& type, const std::string& file, const std::string& option, bool islog10)
   : m_YieldType(type),
     m_YieldOption(option),
     m_YieldFile(),
     m_isLog10(islog10),
     m_StellarYieldSet()
{
   // check and get ASTROTOOLS env. variable
   char const* tmp = getenv("ASTROTOOLS");
   if (tmp == NULL) {
      std::cout << "ASTROTOOLS environment variable not defined" << '\n';
      exit(1);
   } else {
      m_YieldFile = tmp;
   }

   m_YieldFile += "/data/models/Yields";
   // construct yield file to read
   if (type=="LC17") {
      m_YieldFile += "/LC17";
      size_t found = option.find("setR");
      if (found != std::string::npos) m_YieldFile += "/setR/";
      found = option.find("setI");
      if (found != std::string::npos) m_YieldFile += "/setI/";
      found = option.find("setF");
      if (found != std::string::npos) m_YieldFile += "/setF/";
      found = option.find("setM");
      if (found != std::string::npos) m_YieldFile += "/setM/";
      m_YieldFile += file;
   }
   else if (type=="CL13") {
      m_YieldFile += "/CL13";
      if (option=="NR") {
         m_YieldFile += "/apj455654t8_mrt.txt";
      }
      else {
         m_YieldFile += "/apj455654t7_mrt.txt";
      }
   }
   else {
      std::cout << "Yield type not known" << '\n';
      exit(1);
   }

   // read yield file
   readFile();
}



StellarYield::~StellarYield()
{
   clear();
}



void StellarYield::readFile()
{
   if (m_YieldType=="LC17") {
      readFile_LC17();
   }
   else if (m_YieldType=="CL13") {
      readFile_CL13();
   }
}



void StellarYield::readFile_LC17()
{
   // variables
   bool isHeader;
   bool isHeaderRead = false;
   bool mustInsertStar = false;
   std::string line, item;
   std::string iso_ele;
   double metallicity = 0;
   double velocity    = 0;
   std::vector<double> v_mass;
   std::vector<double> v_yield;
   Star star;

   // open yield file
   std::ifstream inFile(m_YieldFile.c_str());
   if (inFile) {
      while (getline(inFile, line)) {
         // skip empty line
         if (line.empty()) continue;
         // skip lines for 'isotopes' N (neutron), P (proton), A (alpha)
         if (line.compare(0,2,"N ") == 0 ||
             line.compare(0,2,"P ") == 0 ||
             line.compare(0,2,"A ") == 0) continue;
         // read file
         if (line.compare(2,3,"ele") == 0) { // header
            // insert star object
            if (mustInsertStar) m_StellarYieldSet.insert(star);
            // clear star object
            star.clear();
            // identify header line
            isHeader = true;
            // determine metallicity
            std::string metal = line.substr(33,1);
            if (metal.compare(0,1,"a") == 0) metallicity = 1; 
            if (metal.compare(0,1,"b") == 0) metallicity = 0.1; 
            if (metal.compare(0,1,"c") == 0) metallicity = 0.01; 
            if (metal.compare(0,1,"d") == 0) metallicity = 0.001; 
            // determine initial rotational velocity
            velocity = atof(line.substr(34,3).c_str());
            // fill Star object
            star.setMetallicity(metallicity);
            star.setInitialVelocity(velocity);
            if (!isHeaderRead) {
               // fill stellar mass vector
               std::stringstream smass(line.substr(28)); 
               while (getline(smass, item, ' ')) {
                  if (item.compare(0,1,"") != 0) {
                     double mass = atof(item.substr(0,3).c_str());
                     if (m_isLog10) mass = log10(mass);
                     v_mass.push_back(mass);
                     //std::cout << item << '\n';
                     //std::cout << atof(item.substr(0,3).c_str()) << '\n';
                  }
               }
            }
            // header has been read
            isHeaderRead = true;
            // star object should be inserted next time a header is found
            mustInsertStar = true;
         }
         else { // yields
            isHeader = false;
            // construct isotope/element name
            std::string Z = line.substr(7,2);
            std::string A = line.substr(11,3);
            std::string name = line.substr(0,4);
            // remove possible white space
            Z.erase(std::remove_if(Z.begin(), Z.end(), ::isspace), Z.end());
            A.erase(std::remove_if(A.begin(), A.end(), ::isspace), A.end());
            name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());
            // test if file contains yields for isotopes or elements
            if ((A.length() == 1) && (atoi(A.c_str()) == 0)) { // element
               iso_ele = name;
            }
            else { // isotope
               // find position of first digit
               size_t found = name.find_first_of("0123456789");
               if (found != std::string::npos) {
                  iso_ele = A + name.substr(0, found);
               }
               else { // 1H case
                  iso_ele = "1" + name;
               }
            }
            // read yields
            std::stringstream syields(line.substr(28)); 
            while (getline(syields, item, ' ')) {
               if (item.compare(0,1,"") != 0) {
                  double yieldValue = atof(item.c_str());
                  if (m_isLog10) {
                     yieldValue = log10(yieldValue);
                     if (!std::isfinite(yieldValue)) yieldValue = -1000;
                  }
                  v_yield.push_back(yieldValue);
               }
            }
         }
         // declare Yield, feed Star and fill set if not header line
         if (!isHeader) {
            // declare Yield object
            //std::cout << "LC17 before yield construction" << '\n';
            Yield yield(v_mass, v_yield);
            yield.setLog10(m_isLog10);
            // feed Star class
            //std::cout << "LC17 before star getYield" << '\n';
            star.setYield(iso_ele, yield);
         }
         // clear yield vector
         v_yield.clear();
      }
      // insert last star object
      m_StellarYieldSet.insert(star);
   } 
   else {
      std::cout << "Problem opening yield file " << m_YieldFile << '\n';
      exit(1);
   }

   // close yield file
   inFile.close();
}



void StellarYield::readFile_CL13()
{
   // reading variables
   std::string line, item;
   std::string iso_ele;

   // physics variables
   double metallicity = 1;    // Z_sun
   double a_mass[] = {13, 15, 20, 25, 30, 40, 60, 80, 120};
   std::vector<double> v_mass, v_yield;
   if (m_isLog10) {
      for (int i = 0; i < sizeof(a_mass) / sizeof(double); i++) {
         v_mass.push_back(log10(a_mass[i]));
      }
   }
   else {
      for (int i = 0; i < sizeof(a_mass) / sizeof(double); i++) {
         v_mass.push_back(a_mass[i]);
      }
   }
   // initialize star object
   Star star;
   star.setMetallicity(metallicity);
   double velocity = ((m_YieldOption=="NR") ? 0 : 300);
   star.setInitialVelocity(velocity);

   // open yield file
   std::ifstream inFile(m_YieldFile.c_str());
   if (inFile) {
      // skip header lines (25 lines)
      for (int i = 0; i < 25; i++) getline(inFile, line);
      // read remaining lines
      while (getline(inFile, line)) {
         // skip empty line
         if (line.empty()) continue;
         // construct isotope/element name
         std::string A = line.substr(1,2);
         std::string name = line.substr(4,2);
         // remove possible white space
         A.erase(std::remove_if(A.begin(), A.end(), ::isspace), A.end());
         name.erase(std::remove_if(name.begin(), name.end(), ::isspace), name.end());
         iso_ele = A + name;
         // read yields
         std::stringstream syields(line.substr(7)); 
         while (getline(syields, item, ' ')) {
            if (item.compare(0,1,"") != 0) {
               double yieldValue = atof(item.c_str());
               if (m_isLog10) {
                  yieldValue = log10(yieldValue);
                  if (!std::isfinite(yieldValue)) yieldValue = -1000;
               }
               v_yield.push_back(yieldValue);
            }
         }
         // declare Yield object
         Yield yield(v_mass, v_yield);
         yield.setLog10(m_isLog10);
         // feed Star class
         star.setYield(iso_ele, yield);
         // clear yield
         v_yield.clear();
      }
      // insert star object
      m_StellarYieldSet.insert(star);
   }
   else {
      std::cout << "Problem opening yield file " << m_YieldFile << '\n';
      exit(1);
   }

   // close yield file
   inFile.close();
}



void StellarYield::clear()
{
   m_StellarYieldSet.clear();
}



void StellarYield::print() const
{
   std::cout << '\n';
   std::cout << "/////////////// StellarYield::print() ///////////////" << '\n';
   std::cout << "StellarYield information" << '\n';
   std::cout << " + Type: "   << m_YieldType   << '\n';
   std::cout << " + Option: " << m_YieldOption << '\n';
   std::cout << " + File: "   << m_YieldFile   << '\n';
   std::cout << '\n';
   std::cout << "Number of registered stars: " << m_StellarYieldSet.size() << '\n';
   std::cout << " [Fe/H]\tv (m/s)" << '\n';
   std::set<Star>::iterator it;
   for (it=m_StellarYieldSet.begin(); it!=m_StellarYieldSet.end(); ++it) {   // loop on set
      std::cout << "  " << (*it).getMetallicity() << "\t  " << (*it).getInitialVelocity() << '\n';
   } // end loop on set
}
