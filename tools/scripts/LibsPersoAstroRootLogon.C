/*****************************************************************************
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *
 *                                                                           *
 * Creation Date  : may 2018                                                 *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription: This script loads automatically the kinematics include path   *
 *             and shared libraries.                                         *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment: This script should be called in your rootlogon.C file            *
 *                                                                           *
 *                                                                           *
 *****************************************************************************/
// ROOT headers
#include "TSystem.h"
#include "TROOT.h"
#include "TList.h"
#include "TSystemDirectory.h"
#include "TString.h"

// C++ headers
#include <iostream>

void LibsPersoAstroRootLogon(bool verbosemode = false)
{
   TString currentpath = gSystem->Getenv("PWD");
   TString path = gSystem->Getenv("ASTROTOOLS");
   path += "/tools";
   
   // Add include path
   if (verbosemode) std::cout << "LibsPersoAstro: adding include path : " << path << std::endl;
   gROOT->ProcessLine(Form(".include %s/src", path.Data()));

   // Add shared libraries
   if (verbosemode) std::cout << "LibsPerso: loading shared libraries ..." << std::endl;
   TString libpath = Form("%s/lib", path.Data());
   TSystemDirectory libdir("libdir", libpath);
   TList* listfile = libdir.GetListOfFiles();

   // Test if the lib directory is empty or not
   if (listfile->GetEntries() > 2) {
   }
    
   // Loop on all libraries
   Int_t i = 0;
   while (listfile->At(i)) {
      TString libname = listfile->At(i++)->GetName();
      if (libname.Contains(".so")) {
         TString lib     = libpath + "/" + libname;
         gSystem->Load(lib);
      }
   }
   
   // Since the libdir.GetListOfFiles() commands cds to the
   // libidr directory, one has to return to the initial
   // directory
   gSystem->cd(currentpath);
   
   if (verbosemode) std::cout << "LibsPersoAstro: Ready" << std::endl;
}
