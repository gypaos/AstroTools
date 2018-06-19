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
 
// project header
#include "starClusterMC.hpp"

// ROOT headers
#include "TRandom3.h"

// C++ headers
#include <iostream>


StarClusterMC::StarClusterMC()
   : m_numberOfStarsInCluster(),
     m_ageCluster(),
     m_numberOfClusters(m_numberOfStarsInCluster.size()),
     m_timeRange(17),
     m_timeStep(10),
     m_numberTimeSteps(m_timeRange*1e3/m_timeStep),
     m_massMin(8),
     m_massMax(120),
     m_massMinCCSN(m_massMin),
     m_massMaxCCSN(25),
     m_metallicity(1),
     m_initialVelocity(),
     m_isotope(),
     m_isotopicRatio(),
     m_isotopicRatioCorrelation(),
     m_numberOfIsotopes(m_isotope.size()),
     m_numberOfIsotopicRatios(m_isotopicRatio.size()),
     m_numberOfIsotopicRatioCorrelations(m_isotopicRatioCorrelation.size())
{
}



StarClusterMC::StarClusterMC(const std::string&)
{
}



StarClusterMC::~StarClusterMC()
{
}



void StarClusterMC::displayCanvasControl()
{
}



double StarClusterMC::kroupaGeneratingFunction(double random)
{
   // 0.01 comes from Gounelle et al. APJL 694 L1 (2009)                        
   //   return 0.01 + (0.19*pow(xi, 1.55) + 0.05*pow(xi, 0.6)) / pow(1-xi, 0.58);  

   // case with min stellar mass = 0.1                                          
   return 0.1 + (0.19*pow(random, 1.55) + 0.05*pow(random, 0.6)) / pow(1-random, 0.58);     
}



void StarClusterMC::prepareCanvasControl()
{
}



void StarClusterMC::readInputFile(const std::string& inputFile)
{
}



void StarClusterMC::run(int numberMCEvents)
{
   // random number initialization
   TRandom3 rndmMass, rndmVelocity;

   for (int iEvt = 0; iEvt < numberMCEvents; iEvt++) {                                        
      std::vector<double> Mass, ExplosionTime, LifeTime;                           
      for (int iNumberCluster = 0; iNumberCluster < m_numberOfClusters; iNumberCluster++) {    // loop on number of "clusters"
//         nbsncluster[j] = 0;                                                    
//         nbsnclusterTimeRange[j] = 0;                                           
         for (int iClusterSize = 0; iClusterSize < m_numberOfStarsInCluster[iNumberCluster]; iClusterSize++) {    // loop on number of stars in clusters
            // generate random number                                           
            double xi = rndmMass.Rndm();                                         
            // use the Kroupa's modified IMF                                    
            double mass = kroupaGeneratingFunction(xi);                       
            // calculate lifetime                                               
//            double death = lifetime->Eval(mass);                              
//            hcontrol4->Fill(mass, death);                                       
            // select only stars with 8 Mo < M < 120 Mo                         
            if (mass < m_massMin || mass > m_massMax) continue;                   
//            nbsncluster[j]++;                                                   
            // select only stars with lifetime < TIME_RANGE                     
//            if (death > TIME_RANGE) continue;                                   
//            nbsnclusterTimeRange[j]++;                                          
            Mass.push_back(mass);                                               
//            hcontrol2->Fill(mass);                                              
//            LifeTime.push_back(death);                                       
//            ExplosionTime.push_back(death + AGE_CLUSTER[0]-AGE_CLUSTER[j]);  
         } // end of loop on number of stars in cluster                         
//         hcontrol0[j]->Fill(nbsncluster[j]);                                    
//         hcontrol1[j]->Fill(nbsnclusterTimeRange[j]);                           
      } // end of loop on number of "clusters"                                  
   }
}



void StarClusterMC::clear()
{
}



void StarClusterMC::print() const
{
   std::cout << std::endl;
   std::cout << "/////////////// StarClusterMC::print() ///////////////" << std::endl;
}
