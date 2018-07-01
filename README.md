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
$ setenv ASTROTOOLS=/path/to/AstroTools/directory
```

You can then build the project using the following commands
```
$ cd $ASTROTOOLS/tools
$ cmake ./
$ make
```


A step by step series of examples that tell you how to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Running the tests

There are a few automated tests which check that the build was properly done. Tests can be run with the following commands:
```
$ cd tests
$ ctest
```
All tests should be passed, otherwise something wrong happened during the build.


## Running the example 

## Built With

* [cmake](https://cmake.org/) - Open-source, cross-platform family of tools designed to build, test and package software.

## Authors

* **Nicolas de Séréville** - *Initial work* - [gypaos](https://github.com/gypaos)

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Thanks to [A. Matta](https://github.com/adrien-matta/) for useful discussions on the library structure, introduction to cmake.

