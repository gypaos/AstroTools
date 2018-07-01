{
   // config AstroUtilities 
   TString AstroPath = gSystem->Getenv("ASTROTOOLS");
   gROOT->ProcessLine(Form(".x %s/tools/util/LibsPersoAstroRootLogon.C+", AstroPath.Data()));
}
