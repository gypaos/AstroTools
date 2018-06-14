#ifndef __ISOTOPE__
#define __ISOTOPE__
/*****************************************************************************  
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *  
 *                                                                           *  
 * Creation Date  : june 2018                                                *  
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

// project headers
#include "nucleusProperties.hpp"
#include "abundances.hpp"

// STL headers
#include <map>
#include <string>


class Isotope 
{
   public:
      // constructors
      Isotope();
      Isotope(const std::string&, const std::string&);
      virtual ~Isotope();

      // methods
      void constructFileNames();
      void readAbundanceFile();
      void readAbundanceFile_AG89();
      void readAbundanceFile_Lodders09();
      void readPropertiesFile();
      void setIsotope(const std::string&);
      void clear();
      void print() const;

   public:
      // setters
      void setAbundancesFile(const std::string& fileNameAbundances) {
         m_fileNameAbundances = fileNameAbundances;
         constructFileNames();
      }
      void setPropertiesFile(const std::string& fileNameProperties) {
         m_fileNameProperties = fileNameProperties;
         constructFileNames();
      }
      // getters
      NucleusProperties getProperties() const   {return m_properties;}
      Abundances        getAbundances() const   {return m_abundances;}

   private:
      std::string                               m_fileNameAbundances;
      std::string                               m_fileNameProperties;
      std::map<std::string, Abundances>         m_isotopeAbundancesTable;
      std::map<std::string, NucleusProperties>  m_isotopePropertiesTable;
      NucleusProperties                         m_properties;
      Abundances                                m_abundances;
};

#endif
