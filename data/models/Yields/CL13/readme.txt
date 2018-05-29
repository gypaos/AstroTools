Explanation of the files' content


The first 8 characters of each filename correspond to a specific model with a given initial mass and rotation rate. In particular, for each filename:
- the first character refers to the initial rotation rate, i.e. 'm' corresponds to vini=0 km/s while 'r' corrsponds to vini=300 km/s;
- the next three characters indicate the initial mass, for example '013' means 13 Msun;
- zsun means that these models have initial solar composition.

For any given mass and initial rotation rate there are 6 files:
*.10: Ejected masses computed for a mass cut that allows the ejection of 0.1 Msun of Ni56
Col. 1 = Name of isotope
Col. 2 = Atomic Charge
Col. 3 = Atomic Weight
Col. 4 = Initial abundance (solar) in mass fraction
Col. 5 = Production factor
Col. 6 = Total ejected mass (after full decay of all the unstable isotopes)
Col. 7 = Ejected mass of the stable isotope with the given A and Z

The columns following the 7th one report the ejected masses of all the unstable isotopes, decaying into the stable isotope with the given A and Z, before their full decay. Therefore, for example, for the 13 Msun non rotating star (m013zsun.10) the total ejected mass of Fe56 is 1.1727D-01 Msun of which 1.3506D-02 comes from Fe56 itself, while 3.2315D-08 Msun, 3.3411D-06 Msun and 1.0376 Msun comes from the decay of Mn56, Co56 and Ni56 into Fe56, respectively.

*.cum_ele: cumulative abundance of the elements in solar masses from the surface to the initial mass cut, after full decay of all the unstable isotopes. The first column is the interior mass in solar masses, therefore each line provides the ejected masses of all the elements corresponding to the mass cut reported in the first column.

*.cum_iso_dec: cumulative abundance of the isotopes in solar masses from the surface to the initial mass cut, after full decay of all the unstable isotopes. The first column is the interior mass in solar masses, therefore each line provides the ejected masses of all the isotopes corresponding to the mass cut reported in the first column.

*.cum_iso_nod: cumulative abundance of the isotopes in solar masses from the surface to the initial mass cut. The first column is the interior mass in solar masses, therefore each line provides the ejected masses of all the isotopes corresponding to the mass cut reported in the first column.

*.yele: Ejected masses of the elements from H to Mo98, computed for a mass cut that allows the ejection of 0.1 Msun of Ni56, after full decay of all the unstable isotopes:
Col. 1 = Total ejected mass
Col. 2 = Production factor
Col. 3 = Initial abundance (solar) in mass fraction

*.yiso: Ejected masses of all the stable isotopes between H and Mo98, computed for a mass cut that allows the ejection of 0.1 Msun of Ni56, after full decay of all the unstable isotopes.
Col. 1 = Name of the isotope
Col. 2 = Atomic charge
Col. 3 = Atomic weight
Col. 4 = Initial abundance (solar) in mass fraction
Col. 5 = Production factor
Col. 6 = Total ejected mass 
