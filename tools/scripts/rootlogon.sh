# *****************************************************************************
# * Original Author: A. Matta  contact address: a.matta@surrey.ac.uk          *
# *                                                                           *
# * Creation Date  : 23/4/2014                                                *
# * Last update    :                                                          *
# *---------------------------------------------------------------------------*
# * Decription: This script edit the user .rootlogon.C file to load NPTool    *
# * Libraries.                                                                *
# *                                                                           *
# *---------------------------------------------------------------------------*
# * Comment:                                                                  *
# *                                                                           *
# *                                                                           *
# *****************************************************************************

#! /bin/bash

# test if the ~/.rootlogon.C file exist, if no create it
if [ -f ~/.rootlogon.C ];
then
  echo 'File .rootlogon.C already exists: attempt to modified it'
  # Check if AstroData stuff is already in
  SEARCH=$(grep ASTROTOOLS ~/.rootlogon.C)
  echo $SEARCH
  if [ ! -n "$SEARCH" ];
  then
    echo 'Appending AstroTools command lines to .rootlogon.C'
    sed -i -e 's#{#{\
   // config AstroTools\
   TString AstroPath = gSystem->Getenv(\"ASTROTOOLS\");\
   gROOT->ProcessLine(Form(\".x %s/tools/scripts/LibsPersoAstroRootLogon.C+\", AstroPath.Data()));\
#g' ~/.rootlogon.C 
  else
    echo 'Some AstroTools libraries already loaded in .rootlogon.C; please check the file'
  fi

else
  echo 'File .rootlogon.C was created'
  cp $ASTROTOOLS/tools/scripts/rootlogon.C ~/.rootlogon.C
fi





