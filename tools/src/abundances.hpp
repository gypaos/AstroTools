#ifndef __ABUNDANCES__
#define __ABUNDANCES__
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
 
// STL header
#include <string>


class Abundances 
{
   public:
      // constructors
      Abundances();
      virtual ~Abundances();

      // methods
      void clear();
      void print() const;

   public:
      // setters
      void setName(const std::string& name)              {m_name          = name;}
      void setAtomicCharge(const int atomicCharge)       {m_atomicCharge  = atomicCharge;}
      void setMassNumber(const int massNumber)           {m_massNumber    = massNumber;}
      void setNumberOfAtoms(const double nOfAtoms)       {m_numberOfAtoms = nOfAtoms;}
      // getters
      std::string    getName() const            {return m_name;}
      unsigned int   getAtomicCharge() const    {return m_atomicCharge;}
      unsigned int   getMassNumber() const      {return m_massNumber;}
      double         getNumberOfAtomes() const  {return m_numberOfAtoms;}

   private:
      std::string    m_name;
      unsigned int   m_atomicCharge;
      unsigned int   m_massNumber;
      double         m_numberOfAtoms;
};

#endif
