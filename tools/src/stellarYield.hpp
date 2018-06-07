#ifndef __STELLARYIELD__
#define __STELLARYIELD__
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
 *     + 2018/05: support for Limongi & Chieffi 2017 yields                  *
 *     + 2018/05: support for Chieffi & Limongi 2013 yields                  *
 *                                                                           *  
 *                                                                           *  
 *****************************************************************************/ 

// project headers
#include "star.hpp"

// STL headers
#include <string>
#include <set>


class StellarYield 
{
   public:
      // constructors
      StellarYield();
      StellarYield(const std::string&, const std::string&, const std::string&, bool = 1);
      virtual ~StellarYield();

      // overload [] operator
      Star operator[] (Star& star) {
         std::set<Star>::iterator it;
         it = m_StellarYieldSet.find(star);
         return *it;
      }

      // getters
      const Star& getStar(const Star& star) const {
         std::set<Star>::iterator it;
         it = m_StellarYieldSet.find(star);
         return *it;
      }

      // methods
      void readFile();
      void readFile_LC17();
      void readFile_CL13();
      void clear();
      void print() const;

      // setters
      void  setLog10(const bool isLog10)     {m_isLog10 = isLog10; clear(); readFile();}
      // getters
      const std::string& getType() const     {return m_YieldType;}
      const std::string& getOption() const   {return m_YieldOption;}
      const std::string& getFile() const     {return m_YieldFile;}

   private:
      std::string    m_YieldType;
      std::string    m_YieldOption;
      std::string    m_YieldFile;
      bool           m_isLog10;
      std::set<Star> m_StellarYieldSet;
};

#endif
