
/********************************************************************************
*										*
*		Most of the parameters that change (i.e. particle type) 	*		
*		from one run to another are changed here.  I am gradually 	*
*		modifying the program so that ALL possible variations		*
*		can be done from this file.					*
*										*
********************************************************************************/





#include "globalvar.h"

//  VARIABLES THAT ARE NOT IN FILE NAME AND DO NOT AFFECT RESULTS
const G4bool visualization = false ;  	 		//  true or false
const G4String viewerString = "OGLIX" ; 			//  OGLI (to look at detector, easily rotate, pan, etc.) or OGLIX (to see particles and rotate with commands)
//  USE OGLI TO SAVE IMAGES, SELECT SCREEN DUMP, PIXELS discovered that in OGLI, can click on "Exit to G4Vis" once to show particles, 2nd time to zoom and pan as in stis.cc code and then have access to command line

const G4String trackOutput = "0" ;  	 		//  tracking verbosity
const G4double mininumDeposit = 0;//1.0E-10 ; 		//  minumum deposit necessary for event to be recorded in main data file (0 or 1.0E-10) 	


//  VARIABLES THAT AFFECT RESULTS AND ARE INDEPENDENT OF PARTICLE SOURCE

const G4String particleType = "gamma" ;		//  e-, proton, gamma, alpha, OxygenPlus, geantino	
const G4String seed = "00" ; 			// seed for randomized initial position of particle within beam
const G4String events  = "1";//00000000" ;  		// events per azimuthal angle  [MAXIUM POSSIBLE IS (2^32)-1 = 2,147,483,647, OR JUST OVER 2 BILLION]

const G4int gunType = 9	;			//  1 ->  directly at center of pZ Foil detector (AF)
						//  2 ->  directly at center of pZ Open detector (AO)
						//  3 ->  directly at center of mZ Open detector (BO)
						//  4 ->  directly at center of mZ Foil detector (BF)
						//  5 ->  uniformly distributed grid, projected at normal incidence from specified x,y range
						// 	  initial z position = 100 mm, momentum = (0,0,-1)
						//  6 ->  all variables unspecified, use when hard coding at command line (visualization on)
						//  7 ->  isotropic, random location on surface of 15 cm radius sphere with random momentum
						//  8 ->  source located at center of each detector (in xy plane) at varying distances (z-direction) from detectors,
						//		random momentum within 2pi sphere
						//  9 ->  random location within circular area centered above/below center of detectors, momenta of (0,0,-1) or (0,0,1)
						//  0 ->  random location within circular area with distribution which projects uniformly onto source sphere
						



//  VARIABLES THAT AFFECT FILE NAME
G4int nLevel = 0;
const G4int nLevelMax = 1 ;  						  	// size of energy array
const G4String energyLevel[nLevelMax] = {"40"};//, "30", "35", "40"} ;   	// array of energies (keV)
const G4String angle  = "00" ;  						// polar angle (degrees) 




//  VARIABLES THAT AFFECT RESULTS
const G4double azimuthal  = 360 ;  		// azimuthal resolution (degrees)
const G4String beamRadius = "1.5" ; 		// particle gun beam radius (mm)

const G4String energyMin = "0" ; 		// minimum energy (keV), in power of 10 to the given value 
const G4String energyMax = "6" ; 		// maximum energy (keV), in power of 10 to the given value 
const G4String energyDistribution = "log10" ; 	// distribution of energy, choices are "linear" or "log10" 



const G4String path = "./results/" ;
const G4String runNumber = "00" ;
//const G4String hitsFile = path + "simulation_results_run" + runNumber + "_seed"+ seed + "_" + particleType + ".dat" ;
const G4String hitsFile = "./results/practice.dat" ;







