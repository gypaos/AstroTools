#ifndef __STARCLUSTERMC__
#define __STARCLUSTERMC__
/*****************************************************************************  
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *  
 *                                                                           *  
 * Creation Date  : june 2018                                                *  
 * Last update    :                                                          *  
 *---------------------------------------------------------------------------*  
 * Decription:                                                               *  
 *     This class performs a MC simulation of (several) star cluster(s)      *
 *     It calculates the time evolution of any isotope / isotopic ratio      *
 *     abundance                                                             *
 *---------------------------------------------------------------------------*  
 * Comment:                                                                  *  
 *                                                                           *  
 *                                                                           *  
 *****************************************************************************/ 
 
// STL header
#include <string>
#include <vector>


class StarClusterMC 
{
   public:
      // constructors
      StarClusterMC();
      StarClusterMC(const std::string&);
      virtual ~StarClusterMC();

      // methods
      void     displayCanvasControl();
      double   kroupaGeneratingFunction(double);
      void     prepareCanvasControl();
      void     readInputFile(const std::string&);
      void     readLifeTimeSchaller();
      void     run(int);
      void     clear();
      void     print() const;

   public:
      // setters
      // getters

   private:
      std::vector<int>                    m_numberOfStarsInCluster;
      std::vector<double>                 m_ageCluster;
      unsigned int                        m_numberOfClusters;
      double                              m_timeRange;                  // in Myr
      double                              m_timeStep;                   // in kyr
      int                                 m_numberTimeSteps;
      double                              m_massMin;                    // in M_sun
      double                              m_massMax;                    // in M_sun
      double                              m_massMinCCSN;                // in M_sun
      double                              m_massMaxCCSN;                // in M_sun
      double                              m_metallicity;                // star metallicity in Z_sun
      std::vector<double>                 m_initialVelocity; // star initial velocity
      std::vector<std::string>            m_isotope;    // list of isotopes
      std::vector<std::pair<int, int> >   m_isotopicRatio;
      std::vector<std::pair<int, int> >   m_isotopicRatioCorrelation;
      unsigned int                        m_numberOfIsotopes;
      unsigned int                        m_numberOfIsotopicRatios;
      unsigned int                        m_numberOfIsotopicRatioCorrelations;
};

#endif
