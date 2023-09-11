
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
//#include "TrackingAction.hh"

#include "G4Step.hh"
#include "G4Event.hh"

#include <fstream>  
#include <stdlib.h>  
#include <iostream>  

#include "G4SteppingManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

#include "globalvar.h"

using namespace std ;




SteppingAction::SteppingAction()
					 
{ }



SteppingAction::~SteppingAction()
{ }



  	G4double deposit = 0;
 	G4double KE = 0;
  	G4double depositSum = 0;


  	G4double hitSum = 0;
 /*	G4double flagF = 0;
  	G4double flagT = 0;
  	G4double flagO = 0;
  	G4String detectorFlag = " ";*/
  	G4double X ;
  	G4double Y ;
  	G4double Z ;
  	G4double momentumX ;
  	G4double momentumY ;
  	G4double momentumZ ;

  	G4double deposit_detector001 = 0;
  	G4double deposit_detector002 = 0;
  	G4double deposit_detector003 = 0;
  	G4double deposit_detector004 = 0;
  	G4double deposit_detector005 = 0;
  	G4double deposit_detector006 = 0;
  	G4double deposit_detector007 = 0;
  	G4double deposit_detector008 = 0;

/*
  	G4double deposit_IonAR1 = 0;
  	G4double deposit_IonAR2 = 0;
  	G4double deposit_IonT = 0;
  	G4double deposit_ElectronAR1 = 0;
  	G4double deposit_ElectronAR2 = 0;
  	G4double deposit_ElectronT = 0;
*/


	G4int eventNumberCheck = -1 ;

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{


  	//getting volume, trackID, step # 
  	G4VPhysicalVolume* volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();  
  	G4int trackID = aStep->GetTrack()->GetTrackID();
  	G4int parentID = aStep->GetTrack()->GetParentID();
  	G4int stepNumber = aStep->GetTrack()->GetCurrentStepNumber();
     	G4String name = volume->GetName();

  	G4String particle ;
  	G4double initKE;
  	//G4double stepEnergy;



	
	//getting event number from file
  /*	ifstream eventNo (eventNumberFile);
  	G4String line; 
  	getline(eventNo, line);
  	G4int eventID = atoi (line);*/
/*
	//getting azimuthal angle from file
  	ifstream degrees(angleFile);
  	getline(degrees, line);
*/
	//G4int numberOfEvents = atoi (events);



	//if (eventID%numberOfEvents==0){hitSum=0;}

  	// getting primary initial kinetic energy
  	G4double* KEpointer = &KE;

	// creating pointers for energy deposit by detector
  	G4double* depositPointer = &depositSum;
  	G4double* deposit_detector001_Pointer = &deposit_detector001;
  	G4double* deposit_detector002_Pointer = &deposit_detector002;
  	G4double* deposit_detector003_Pointer = &deposit_detector003;
  	G4double* deposit_detector004_Pointer = &deposit_detector004;
  	G4double* deposit_detector005_Pointer = &deposit_detector005;
  	G4double* deposit_detector006_Pointer = &deposit_detector006;
  	G4double* deposit_detector007_Pointer = &deposit_detector007;
  	G4double* deposit_detector008_Pointer = &deposit_detector008;

	/*
  	G4double* deposit_IonAR1_Pointer = &deposit_IonAR1;
  	G4double* deposit_IonAR2_Pointer = &deposit_IonAR2;
  	G4double* deposit_IonT_Pointer = &deposit_IonT;
  	G4double* deposit_ElectronAR1_Pointer = &deposit_ElectronAR1;
  	G4double* deposit_ElectronAR2_Pointer = &deposit_ElectronAR2;
  	G4double* deposit_ElectronT_Pointer = &deposit_ElectronT;
*/

/*
  	G4double* flagFpointer = &flagF;
  	G4double* flagTpointer = &flagT;
  	G4double* flagOpointer = &flagO;
*/
  	G4double* Xpointer = &X;
  	G4double* Ypointer = &Y;
  	G4double* Zpointer = &Z;

  	G4double* momentumXpointer = &momentumX;
  	G4double* momentumYpointer = &momentumY;
  	G4double* momentumZpointer = &momentumZ;
/*
  	if(flagF==1 && flagT==0 && flagO==0){ detectorFlag = "F";}
  	else if (flagF==0 && flagT==1 && flagO==0){ detectorFlag = "T";}
  	else if (flagF==0 && flagT==0 && flagO==1){ detectorFlag = "O";}
  	else if (flagF==1 && flagT==1 && flagO==0){ detectorFlag = "FT";}
  	else if (flagF==1 && flagT==0 && flagO==1){ detectorFlag = "FO";}
  	else if (flagF==0 && flagT==1 && flagO==1){ detectorFlag = "TO";}
  	else if (flagF==1 && flagT==1 && flagO==1){ detectorFlag = "FTO";}
  	else if (flagF==0 && flagT==0 && flagO==0){ detectorFlag = " ";}
*/
  	G4double initX ;
  	G4double initY ;
  	G4double initZ ;

  	G4double initMomentumX ;
  	G4double initMomentumY ;
  	G4double initMomentumZ ;


	// FIRST STEP OF TRACK, PRINT ENERGY DEPOSIT INFORMATION FOR EACH DETECTOR, THEN
	// SET ALL DEPOSIT TOTALS BACK TO ZERO FOR NEW TRACK ---------------------------------


 	// # of characters for widths of output
 	G4int j = 9; 

  	//if(trackID==1 && stepNumber==1)
  	if(parentID==0 && stepNumber==1)
  	{

		eventNumberCheck++ ;

		if(  (depositSum/keV >= mininumDeposit)   && eventNumberCheck != 0)
		//if(  (depositSum/keV >= mininumDeposit)   && eventID != 0)
		{
  			G4String line; 

			particle = aStep->GetTrack()->GetDefinition()->GetParticleName();  	

			ofstream outputHits(hitsFile, ios::app);
			outputHits << std::setw(j+3) << eventNumberCheck  //eventID //- 1
				<< std::setprecision(1) << std::fixed
				<< std::setw(j+2) << KE/keV 
				<< std::setw(j+2) << std::setprecision(2) << X
				<< std::setw(j) << Y
				<< std::setw(j) << Z	
				<< std::setw(j+4) << std::setprecision(3) << momentumX
				<< std::setw(j) << momentumY
				<< std::setw(j) << momentumZ
			  	<< std::setw(j+2)  << std::setprecision(1) 
			 	<< deposit_detector001/keV 				
			  	<< std::setw(j+2)  << deposit_detector002/keV 	
			  	<< std::setw(j+2)  << deposit_detector003/keV 
			  	<< std::setw(j+2)  << deposit_detector004/keV 
			  	<< std::setw(j+2)  << deposit_detector005/keV 
			  	<< std::setw(j+2)  << deposit_detector006/keV 
			  	<< std::setw(j+2)  << deposit_detector007/keV 
			  	<< std::setw(j+2)  << deposit_detector008/keV 				
			  /*	<< std::setw(j+2)  << std::setprecision(1) 
			  	<< deposit_IonAR1/keV 				// Ion AR1
			  	<< std::setw(j+2)  << deposit_IonAR2/keV 	// Ion AR2
				<< std::setw(j+2)  << deposit_IonT/keV 		// Ion T
				<< std::setw(j+2)  << deposit_ElectronAR1/keV 	// Electron AR1
				<< std::setw(j+2)  << deposit_ElectronAR2/keV 	// Electron AR2
				<< std::setw(j+2)  << deposit_ElectronT/keV  */	// Electron T
				<< std::setw(j+2)  << depositSum/keV
				<< G4endl;
		}

		initKE = aStep->GetTrack()->GetVertexKineticEnergy();
        	*KEpointer = initKE;

  		initX = aStep->GetTrack()->GetVertexPosition().x();
  		initY = aStep->GetTrack()->GetVertexPosition().y();
  		initZ = aStep->GetTrack()->GetVertexPosition().z();
		*Xpointer = initX;
		*Ypointer = initY;
		*Zpointer = initZ;

  		initMomentumX = aStep->GetTrack()->GetVertexMomentumDirection().x();
  		initMomentumY = aStep->GetTrack()->GetVertexMomentumDirection().y();
  		initMomentumZ = aStep->GetTrack()->GetVertexMomentumDirection().z();
		*momentumXpointer = initMomentumX;
		*momentumYpointer = initMomentumY;
		*momentumZpointer = initMomentumZ;

		*depositPointer = 0 ;

		*deposit_detector001_Pointer = 0;
		*deposit_detector002_Pointer = 0;
		*deposit_detector003_Pointer = 0;
		*deposit_detector004_Pointer = 0;
		*deposit_detector005_Pointer = 0;
		*deposit_detector006_Pointer = 0;
		*deposit_detector007_Pointer = 0;
		*deposit_detector008_Pointer = 0;
 
		/*
  		*deposit_IonAR1_Pointer = 0;
  		*deposit_IonAR2_Pointer = 0;
  		*deposit_IonT_Pointer = 0;
  		*deposit_ElectronAR1_Pointer = 0;
  		*deposit_ElectronAR2_Pointer = 0;
  		*deposit_ElectronT_Pointer = 0;
*/

/*
		*flagFpointer = 0;
		*flagTpointer = 0;
		*flagOpointer = 0 ;*/
  	}



	if (name == "detector001" || name == "detector002" || name == "detector003" || name == "detector004"   
			|| name == "detector005" || name == "detector006" || name == "detector007" || name == "detector008") 
	  /*	if (name == "detector001" || name == "detector002" ||name == "Ion T1" || name == "Ion T2"   
			|| name == "Electron AR1" || name == "Electron AR2" || name == "Electron T1" || name == "Electron T2") */
  	{
     		deposit = aStep->GetTotalEnergyDeposit();  // energy deposited in this step

     		particle = aStep->GetTrack()->GetDefinition()->GetParticleName();  // particle type
     		//stepEnergy = aStep->GetPreStepPoint()->GetKineticEnergy();  // kinetic energy at start of step (before deposit)

		if (deposit>0)
		{
			depositSum += deposit;	

			if (name == "detector001"){ deposit_detector001 +=deposit; }
			if (name == "detector002"){ deposit_detector002 +=deposit; }
			if (name == "detector003"){ deposit_detector003 +=deposit; }
			if (name == "detector004"){ deposit_detector004 +=deposit; }
			if (name == "detector005"){ deposit_detector005 +=deposit; }
			if (name == "detector006"){ deposit_detector006 +=deposit; }
			if (name == "detector007"){ deposit_detector007 +=deposit; }
			if (name == "detector008"){ deposit_detector008 +=deposit; }

			/*
			if (name == "detector002"){ Deposit_IonAR2 +=deposit; }
			if (name == "detector003"){ deposit_IonT +=deposit; }

			if (name == "detector004"){deposit_ElectronAR1 +=deposit;}
			if (name == "detector005"){deposit_ElectronAR2 +=deposit;}
			if (name == "detector006"){ deposit_ElectronT +=deposit;}
*/

  		}
	}


}
