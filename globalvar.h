
#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include "globals.hh"


//  VARIABLES THAT ARE NOT IN FILE NAME AND DO NOT AFFECT RESULTS
extern const G4bool visualization ;
extern const G4String trackOutput ; 
extern const G4double mininumDeposit ;
extern const G4String viewerString ; 

//  VARIABLES THAT AFFECT RESULTS AND ARE INDEPENDENT OF PARTICLE SOURCE
extern const G4String particleType ; 
extern const G4String seed ;
extern const G4String events ; 
extern const G4int gunType  ;  	

extern G4int nLevel ;
extern const G4int nLevelMax ;
extern const G4String energyLevel[];
extern const G4String angle ; 
 	
extern const G4String path ;
extern const G4String runNumber ;
extern const G4String hitsFile ;
extern const G4String eventNumberFile ;



//  VARIABLES THAT AFFECT RESULTS 
extern const G4double azimuthal ;   				
extern const G4String beamRadius  ;  		
extern const G4String energyMin  ; 	
extern const G4String energyMax ; 	 
extern const G4String energyDistribution ;


#endif
