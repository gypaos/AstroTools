#ifndef __NUCLEUSPROPERTIES__
#define __NUCLEUSPROPERTIES__
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
 
// STL header
#include <string>


class NucleusProperties 
{
   public:
      // constructors
      NucleusProperties();
      NucleusProperties(const std::string&, const int, const int, const double,
                        const double, const double, const std::string&);
      virtual ~NucleusProperties();

      // methods
      bool     isMassExcessExperimental() const    {return m_massExcessExperimental;}
      void     clear();
      void     print() const;

   public:
      // setters
      void setName(const std::string& name)              {m_name         = name;}
      void setAtomicCharge(const int atomicCharge)       {m_atomicCharge = atomicCharge;}
      void setMassNumber(const int massNumber)           {m_massNumber   = massNumber;}
      void setMassExcess(const double massExcess, 
                         const double massExcessUncertainty = 0)   {
         m_massExcess            = massExcess;
         m_massExcessUncertainty = massExcessUncertainty;
      }
      void setMassExcessExperimental(const bool massExcessExp) {m_massExcessExperimental = massExcessExp;}
      void setHalfLife(const double halfLife)            {m_halfLife     = halfLife;}
      void setSpinParity(const std::string& spinParity)  {m_spinParity   = spinParity;}

      // getters
      std::string    getName() const         {return m_name;}
      unsigned int   getAtomicCharge() const {return m_atomicCharge;}
      unsigned int   getMassNumber() const   {return m_massNumber;}
      double         getMassExcess() const   {return m_massExcess;}
      double         getHalfLife() const     {return m_halfLife;}
      std::string    getSpinPariy() const    {return m_spinParity;}
      double         getSpin() const         {return m_spin;}
      std::string    getParity() const       {return m_parity;}

   private:
      // static properties of nuclei
      std::string    m_name;
      unsigned int   m_atomicCharge;
      unsigned int   m_massNumber;
      double         m_massExcess;
      double         m_massExcessUncertainty;
      bool           m_massExcessExperimental;
      double         m_halfLife;    // in s
      std::string    m_spinParity;
      double         m_spin;
      std::string    m_parity;
};

#endif
