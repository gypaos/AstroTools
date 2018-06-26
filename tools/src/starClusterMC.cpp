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
#include "star.hpp"

// ROOT headers
#include "TROOT.h"
#include "TRandom3.h"
#include "TString.h"
#include "TGraph.h"

// C++ headers
#include <iostream>
#include <fstream>


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
     m_initialVelocityFraction(),
     m_numberOfVelocities(m_initialVelocity.size()),
     m_lifeTime(),
     m_isotopeList(),
     m_isotopeRmin(),
     m_isotopeRmax(),
     m_isotopicRatio(),
     m_isotopicRatioCorrelation(),
     m_numberOfIsotopes(m_isotopeList.size()),
     m_numberOfIsotopicRatios(m_isotopicRatio.size()),
     m_numberOfIsotopicRatioCorrelations(m_isotopicRatioCorrelation.size()),
     m_can0(0),
     m_hcontrol0(new THStack),
     m_hcontrol1(new THStack),
     m_hcontrol2(0),
     m_hcontrol3(0),
     m_hcontrol4(0)
{
   readLifeTimeSchaller();
}



StarClusterMC::StarClusterMC(const std::string&)
{
}



StarClusterMC::~StarClusterMC()
{
}



void StarClusterMC::addCluster(int numberOfStarsInCluster, double ageCluster) 
{
   m_numberOfStarsInCluster.push_back(numberOfStarsInCluster);            
   m_ageCluster.push_back(ageCluster);                                    
   m_numberOfClusters = m_numberOfStarsInCluster.size();                  
}



void StarClusterMC::addInitialVelocity(double velocity, double fraction) 
{
   m_initialVelocity.push_back(velocity);                                 
   m_initialVelocityFraction.push_back(fraction);                         
   m_numberOfVelocities = m_initialVelocity.size();                       
}



void StarClusterMC::addIsotope(std::string isotope, double rmin, double rmax) 
{
   Isotope iso; iso.setIsotope(isotope);
   m_isotopeList.push_back(iso);
   m_isotopeRmin.push_back(rmin);
   m_isotopeRmax.push_back(rmax);
}



void StarClusterMC::displayCanvasControl() const
{
   // number of massive stars distribution                                      
   m_can0->cd(1); 
   for (Int_t i = 0; i < m_numberOfClusters; ++i) {                                  
      m_hcontrol0->Draw("nostack");                                                     
   }                                                                            
   m_can0->cd(2);                                                                 
   for (Int_t i = 0; i < m_numberOfClusters; ++i) {                                  
      m_hcontrol1->Draw("nostack");                                                     
   }                                                                            
   // imf                                                                       
   m_can0->cd(3); m_hcontrol2->DrawCopy(); delete m_hcontrol2;                                              
   // initial rotational velocity distribution                                  
   m_can0->cd(4); m_hcontrol3->DrawCopy(); delete m_hcontrol3;                                              
   // lifetime                                                                  
   m_can0->cd(5); m_hcontrol4->DrawCopy(); delete m_hcontrol4; 
}



double StarClusterMC::kroupaGeneratingFunction(double random) const
{
   // 0.01 comes from Gounelle et al. APJL 694 L1 (2009)                        
   //   return 0.01 + (0.19*pow(xi, 1.55) + 0.05*pow(xi, 0.6)) / pow(1-xi, 0.58);  

   // case with min stellar mass = 0.1                                          
   return 0.1 + (0.19*pow(random, 1.55) + 0.05*pow(random, 0.6)) / pow(1-random, 0.58);     
}



void StarClusterMC::prepareCanvasControl()
{
   // control canvas
   m_can0 = (TCanvas*) gROOT->GetListOfCanvases()->FindObject("can0");   
   if (m_can0) m_can0->Clear();                                                     
   else m_can0 = new TCanvas("can0", "MC control histograms", 1080, 720);         
   m_can0->Divide(3, 2);                                                          
   m_can0->Draw();

   // single control histograms
   m_hcontrol2 = new TH1F("hcontrol2", 
			  Form("initial mass function for t < %2.0f Myr", m_timeRange), 
			  100, 0, 120);
   m_hcontrol3 = new TH1F("hcontrol3", "initial rotational velocity distribution", 3, 0, 450);
   m_hcontrol4 = new TH2F("hcontrol4", "lifetime", 1000, 0, 120, 1000, 0, 40);

   // control histograms for each cluster
   TH1F *hcontrol0_tmp, *hcontrol1_tmp;
   for (int i = 0; i < m_numberOfClusters; ++i) {                                  
      hcontrol0_tmp = new TH1F(Form("hcontrol0_%d",i), 
			       Form("SN numbers in [%d, %d] Msun", 
			       (int)m_massMin, (int)m_massMax), 50, 0, 50);
      hcontrol0_tmp->SetLineColor(i+1);
      m_hcontrol0->Add(hcontrol0_tmp);
      hcontrol1_tmp = new TH1F(Form("hcontrol1_%d",i), 
			       Form("SN numbers for t < %2.0f Myr", m_timeRange), 
			       50, 0, 50);
      hcontrol1_tmp->SetLineColor(i+1);
      m_hcontrol1->Add(hcontrol1_tmp);
   }
   m_hcontrol0->SetTitle(Form("SN numbers in [%d, %d] Msun", (int)m_massMin, (int)m_massMax));
   m_hcontrol1->SetTitle(Form("SN numbers for t < %2.0f Myr", m_timeRange));
}



void StarClusterMC::readInputFile(const std::string& inputFile)
{
}



void StarClusterMC::readLifeTimeSchaller()
{
   std::string lifeTimeFile;
   // check and get ASTROTOOLS env. variable 
   char const* tmp = getenv("ASTROTOOLS");
   if (tmp == NULL) {
      std::cout << "ASTROTOOLS environment variable not defined" << '\n';
      exit(1);
   } else {
      lifeTimeFile = tmp;
   }
   lifeTimeFile += "/data/models/lifeTime/Schaller92.dat";

   // opening the data file                                                     
   std::string line;         
   int index = 0;
   TGraph *gr = new TGraph();                                             
   std::ifstream inputFile(lifeTimeFile.c_str());
   if (inputFile) {
      while (getline(inputFile, line)) {
         // skip empty line
         if (line.empty()) continue;
         // skip comment line
         if (line.compare(0,2,"//") == 0) continue;
         double mass    = atof(line.substr(0,5).c_str());
         double timeH   = atof(line.substr(6,10).c_str());
         double timeHe  = atof(line.substr(18,8).c_str());
         double timeC   = atof(line.substr(27,8).c_str());
         gr->SetPoint(index++, mass, timeH + timeHe + timeC);                            
      }
   }
   else {
      std::cout << "Problem opening stellar life time file " << lifeTimeFile << '\n';
      exit(1);
   }

   // close file
   inputFile.close();

   // build a spline                                                            
   m_lifeTime = TSpline3("sp", gr);                                        
   delete gr;
}



void StarClusterMC::run(int numberMCEvents)
{
   // build cumulative velocity distribution
   std::vector<double> cumulativeVelocityDistribution;
   cumulativeVelocityDistribution.push_back(m_initialVelocityFraction[0]);
   for (unsigned int i = 0; i < m_numberOfVelocities-1; ++i) {
      cumulativeVelocityDistribution.push_back(cumulativeVelocityDistribution[i] + m_initialVelocityFraction[i+1]);
   }

   // array for storing number of massive stars
   int nbMassiveStars[m_numberOfClusters];
   int nbMassiveStarsTimeRange[m_numberOfClusters];

   // declare Star object
   Star star(m_metallicity, m_initialVelocity[0]);

   // random number initialization
   TRandom3 rndmMass, rndmVelocity;

   for (int iEvt = 0; iEvt < numberMCEvents; iEvt++) {                                        
      std::vector<double> stellarMass, stellarLifeTime, explosionTime;                           
      for (int iNumberCluster = 0; iNumberCluster < m_numberOfClusters; iNumberCluster++) {    // loop on number of "clusters"
         // initialize arrays
         nbMassiveStars[iNumberCluster] = 0;
         nbMassiveStarsTimeRange[iNumberCluster] = 0;
         for (int iClusterSize = 0; iClusterSize < m_numberOfStarsInCluster[iNumberCluster]; iClusterSize++) {    // loop on number of stars in clusters
            // generate random number                                           
            double xi = rndmMass.Rndm();                                         
            // use the Kroupa's modified IMF                                    
            double mass = kroupaGeneratingFunction(xi);                       
            // calculate lifetime                                               
            double death = m_lifeTime.Eval(mass);                              
            m_hcontrol4->Fill(mass, death);                                       
            // select only stars with 8 Mo < M < 120 Mo                         
            if (mass < m_massMin || mass > m_massMax) continue;                   
            nbMassiveStars[iNumberCluster]++;                                                   
            // select only stars with lifetime < TIME_RANGE                     
            if (death > m_timeRange) continue;                                   
            nbMassiveStarsTimeRange[iNumberCluster]++;                                                   
            stellarMass.push_back(mass);                                               
            m_hcontrol2->Fill(mass);                                              
            stellarLifeTime.push_back(death);                                       
            explosionTime.push_back(death + m_ageCluster[0]-m_ageCluster[iNumberCluster]);  
            // determine initial rotational velocity
            double vi = rndmVelocity.Rndm();
            for (unsigned int r = 0; r < m_numberOfVelocities; ++r) {
               if (vi < cumulativeVelocityDistribution[r]) {
                  m_hcontrol3->Fill(m_initialVelocity[r]);
                  star.setInitialVelocity(m_initialVelocity[r]);
                  break;
               }
            }
            if (star.getInitialVelocity() < 0) std::cout << "Negative velocity" << '\n';
         } // end of loop on number of stars in cluster                         
         ((TH1F*)m_hcontrol0->GetHists()->At(iNumberCluster))->Fill(nbMassiveStars[iNumberCluster]); 
         ((TH1F*)m_hcontrol1->GetHists()->At(iNumberCluster))->Fill(nbMassiveStarsTimeRange[iNumberCluster]); 
      } // end of loop on number of "clusters"                                  
   }

}



void StarClusterMC::clear()
{
}



void StarClusterMC::print() const
{
   std::cout << '\n';
   std::cout << "/////////////// StarClusterMC::print() ///////////////" << '\n';
}
