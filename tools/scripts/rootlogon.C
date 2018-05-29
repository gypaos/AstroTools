{
   // config AstroUtilities 
   TString AstroPath = gSystem->Getenv("ASTROTOOLS");
   gROOT->ProcessLine(Form(".x %s/tools/scripts/LibsPersoAstroRootLogon.C+", AstroPath.Data()));
}
