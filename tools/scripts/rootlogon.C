{
   // config AstroUtilities 
   TString AstroPath = gSystem->Getenv("DATAASTRO");
   gROOT->ProcessLine(Form(".x %s/AstroUtilities/scripts/LibsPersoAstroRootLogon.C+", AstroPath.Data()));
}
