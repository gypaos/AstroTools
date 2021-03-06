# AstroTools 

AstroTools contains very basic libraries reading stellar yields, stellar lifetimes, nuclear properties and providing Monte Carlo simulation of stellar clusters.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

You need to install the following software
* [ROOT](https://root.cern.ch/) - The Data Analysis Framework from CERN

### Installing

First get the source code from github
```
$ git clone https://github.com/gypaos/AstroTools
```

Then define the ASTROTOOLS environment variable in your .bashrc file
```
$ export ASTROTOOLS=/path/to/AstroTools/directory
```
or in your .cshrc file
```
$ setenv ASTROTOOLS /path/to/AstroTools/directory
```

You can then build the project using the following commands
```
$ cd $ASTROTOOLS/tools
$ cmake ./
$ make
```
## Running the tests

There are a few automated tests which check that the build was properly done. Tests can be run with the following commands:
```
$ cd $ASTROTOOLS/tools/tests
$ ctest
```
All tests should be passed, otherwise something wrong happened during the build or with setting the ASTROTOOLS environment variable.


## Running example from a ROOT macro 
First thing is to add ROOT support for AstroTools in your .rootlogon.C file:
```
$ cd $ASTROTOOLS/tools/util
$ ./rootlogon.sh
```
This will add the following three lines in your .rootlogon.C if they don't exist already:
```
// config AstroUtilities 
TString AstroPath = gSystem->Getenv("ASTROTOOLS");
gROOT->ProcessLine(Form(".x %s/tools/util/LibsPersoAstroRootLogon.C+", AstroPath.Data()));
```

Then you can run the SLR.C example:
```
$ cd $ASTROTOOLS/tools/examples
$ root -l
root [0] .L SLR.C+
root [1] SLR()
```

You should obtain the following canvas:
![Alt text](./tools/examples/SLR.png "Title")

## Built With

* [cmake](https://cmake.org/) - Open-source, cross-platform family of tools designed to build, test and package software.

## Authors

* **Nicolas de Séréville** - *Initial work* - [gypaos](https://github.com/gypaos)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Thanks to [A. Matta](https://github.com/adrien-matta/) for useful discussions on the library structure and introduction to cmake.

