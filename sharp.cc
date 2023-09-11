
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4VisExecutive.hh"
#include "globals.hh"

#include "PhysicsList.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"


#include <fstream>  
#include <stdlib.h>  
#include <iostream>  
#include <sstream>

#include "globalvar.h"

#include <time.h>

using namespace std ;


G4int k = 15 ;   //setting width (number of spaces) for headers of results file



int main()
{
  	G4long startTime = time(NULL) ;



	G4int bullets = atoi(events);
	G4int totalBullets = (G4int(360.0/azimuthal)*bullets) ;
	ostringstream bulletString;
	bulletString << totalBullets;

	G4int totalBullets2 = (G4int(360.0/azimuthal)*bullets);// + 1 ;
	ostringstream bulletString2;
	bulletString2 << totalBullets2;

        //G4cout  << "bullets:  "  << bullets << "   totalBullets2 :  " << totalBullets2 << "    bulletString2:  " << bulletString2.str() << G4endl ;


 	ofstream outputHits(hitsFile, ios::trunc);
	outputHits << "# " << std::setw(k) << " " <<  "  GENERAL DETAILS" << G4endl ;  /*
		<< "# " << std::setw(k) <<  bulletString.str()  << "  Particles shot per polar angle (events)" << G4endl
		<< "# " << std::setw(k) <<  beamRadius << "  Radius (mm) of particle source"  << G4endl
		<< "# " << std::setw(k) <<  angle << "  Polar angle (degrees)"  << G4endl
		<< "# " << std::setw(k) <<  particleType << "  Particle type"  << G4endl
		<< "# " << std::setw(k) <<  azimuthal << "  Azimuthal resolution (degrees)"  << G4endl ;

		outputHits << "# " << std::setw(k) <<  seed << "  Seed used for randomization of starting position"  << G4endl
		<< "# " << std::setw(k) <<  gunType << "  Type of particle source (distribution and target)"  << G4endl
		<< "# " << std::setw(k) << "13O" <<  "  Radius (mm) of source sphere (valid if particle source type is 7)"  << G4endl 
		<< "#   SIM_Energy_range = [1.0e" << energyMin << ",1.0e" << energyMax << "]       ; in keV"  << G4endl ;
		if (energyDistribution == "linear")
		{	
			outputHits << "#   SIM_Energy_log = 0                 ; Energy distribution, 0 => linear, 1 => logarithmic (base 10)"   << G4endl ;
		}
		if (energyDistribution == "log10")
		{	
			outputHits << "#   SIM_Energy_log = 1                 ; Energy distribution, 0 => linear, 1 => logarithmic (base 10)"   << G4endl ;
		}
		if (gunType == 7)
		{
			outputHits << "#   SIM_area = 130.^2 * 4 * !pi        ; mm^2     (spherical source)"   << G4endl ;
		}
		else if (gunType == 8)
		{
			outputHits << "#   SIM_area = 35.0 * 35.0             ; mm^2     (planar source)"   << G4endl ;
		}
		else
		{
			outputHits << "#   SIM_area = unspecified             ; "   << G4endl ;
		}

		if (particleType == "e-")
		{
			outputHits << "#   particle_type = -1"   << G4endl
				<< "#   particle_name = 'Electron'"   << G4endl ;
		}
		else if (particleType == "proton")
		{
			outputHits << "#   particle_type =  1"   << G4endl
				<< "#   particle_name = 'Proton'"   << G4endl ;
		}
		else if (particleType == "gamma")
		{
			outputHits << "#   particle_type =  0"   << G4endl
				<< "#   particle_name = 'Gamma'"   << G4endl ;
		}
		else if (particleType == "OxygenPlus")
		{
			outputHits << "#   particle_type =  2"   << G4endl
				<< "#   particle_name = 'O+, oxygen ion'"   << G4endl ;
		}


		if (gunType == 7)
		{
			outputHits << "#   desc = '4Pi'                         ; guntype = 7"   << G4endl ;
		}

		else
		{
			outputHits << "#   desc = unknown                        ; guntype != 7 or 8"   << G4endl ;
		}
*/

		outputHits << "#" << G4endl
		<< "#" << G4endl 
		<< "#              |                             INITIAL VALUES                        "
			<< "      |" << G4endl

		<< "#              |-------------------------------------------------------------------"
			<< "------|" << G4endl
		<< "#              |    KE   |        POSITION (mm)          |    UNIT DIRECTION VECTOR"
			<< "      |                ENERGY (keV) DEPOSITED IN DETECTORS" << G4endl
	
		<< "#              |---------|-------------------------------|-------------------------"
			<< "------|-------------------------------------------------------------------" << G4endl
	
		<< "#" << std::setw(9) << "Event" << std::setw(13) << "|  (keV)"
			<< std::setw(10) << "|   Pos_x"  << std::setw(9) << "Pos_y" << std::setw(9) << "Pos_z"  
			<< std::setw(14) << "|    Dir_x"  << std::setw(10) << "Dir_y" << std::setw(10) << "Dir_z"  
			<< std::setw(10) << "| Det 001" << std::setw(10) << " Det 002" << std::setw(10) << " Det 003" << std::setw(10) << " Det 004"
			<< std::setw(10) << "  Det 005" << std::setw(10) << " Det 006" << std::setw(10) << " Det 007" << std::setw(10) << " Det 008" 
			<< std::setw(10) << "Total" << G4endl 
		<< "#" << G4endl;
 



  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager;
  G4VisManager* visManager = new G4VisExecutive;
        

  // Set mandatory initialization and user action classes
  DetectorConstruction* detector = new DetectorConstruction;
  runManager->SetUserInitialization(detector);
  runManager->SetUserInitialization(new PhysicsList);
  runManager->SetUserAction(new PrimaryGeneratorAction);
  //RunAction* RunAction = new RunAction;
  runManager->SetUserAction(new RunAction);
  runManager->SetUserAction(new EventAction);
  runManager->SetUserAction(new SteppingAction);
      
  visManager->Initialize();

  // Open a UI session: will stay there until the user types "exit"
  G4UIsession* session = 0;

  if(visualization)	// RUN WITH VISUALIZATION
  {

#ifdef G4UI_USE_TCSH
    session = new G4UIterminal(new G4UItcsh);
#else
    session = new G4UIterminal();
#endif
    G4UImanager* UI = G4UImanager::GetUIpointer(); 


// create empty scene
    UI->ApplyCommand("/vis/scene/create");
    UI->ApplyCommand("/vis/scene/add/volume experimentalHall_phys");
    UI->ApplyCommand("/vis/sceneHandler/attach");
    UI->ApplyCommand("/vis/scene/add/trajectories smooth");  // this line makes particles show curved path in magnetic fields
    UI->ApplyCommand("/run/initialize");

//--------------------------------------------------------------------------------------------------------------
//
//   USE OGLI (BELOW) TO JUST LOOK AT DETECTOR, EASILY ROTATE OR PAN, ETC.., 
//	USE OGLIX TO ACTUALLY SEE PARTICLES INTERACT WITH DETECTOR AND USE COMMAND LINE
//
//--------------------------------------------------------------------------------------------------------------

// Create a scene handler for a specific graphics system
// LAPTOP
 //UI->ApplyCommand("/vis/open OGLIX 800x800");
// DESKTOP
  //UI->ApplyCommand("/vis/open OGLIX 1000x1000");
  //UI->ApplyCommand("/vis/open OGLI 1000x1000");
  G4String viewerCommandString = "/vis/open " + viewerString + " 1000x1000" ;
  UI->ApplyCommand(viewerCommandString);

// draw scene
   //UI->ApplyCommand("/vis/viewer/zoom 1.5");
   UI->ApplyCommand("/vis/viewer/flush");


// LAPTOP
//   UI->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 -1");

// DESKTOP
   //UI->ApplyCommand("/vis/viewer/set/viewpointVector -25 -50 100");
//   UI->ApplyCommand("/vis/viewer/set/viewpointVector 0 0 10");
   //UI->ApplyCommand("/vis/viewer/zoom 2.0");
   UI->ApplyCommand("/vis/drawVolume");

//   UI->ApplyCommand("/vis/viewer/set/style surface");
//   UI->ApplyCommand("/vis/viewer/set/style wireframe");

//  if you want to see trajectories and hits points
   UI->ApplyCommand("/vis/scene/add/trajectories smooth");
   UI->ApplyCommand("/vis/modeling/trajectories/create/drawByCharge");
   UI->ApplyCommand("/vis/modeling/trajectories/drawByCharge-0/default/setDrawStepPts true");
   UI->ApplyCommand("/vis/modeling/trajectories/drawByCharge-0/default/setStepPtsSize 0.2");

// (to refresh each event, uncomment next line)
   UI->ApplyCommand("/vis/scene/endOfEventAction accumulate 1000");

// hard coded position and direction for gun, ignored if primary generator simple not set to 6
 //  UI->ApplyCommand("/gun/position -236 -15    397 mm");
  // UI->ApplyCommand("/gun/direction  269.3  0 -384.8");
//   UI->ApplyCommand("/gun/position -22 58.4 100 mm  ");
//   UI->ApplyCommand("/gun/direction  0 0 -1");

// if you want make a run with particle
   UI->ApplyCommand("/tracking/verbose " + trackOutput);
    UI->ApplyCommand("/process/verbose 0");
    UI->ApplyCommand("/control/verbose 0");
    UI->ApplyCommand("/particle/process/verbose 0");

 //  UI->ApplyCommand("/run/beamOn " + bulletString.str());
  // UI->ApplyCommand("/vis/viewer/pan 0 0 mm");
   //UI->ApplyCommand("/vis/viewer/zoom 10");
   //UI->ApplyCommand("/vis/viewer/pan -37 -19 mm");

 //  UI->ApplyCommand("/vis/viewer/set/viewpointVector -25 -50 200");
 //  UI->ApplyCommand("/vis/viewer/set/viewpointVector -5 -6 15");
   UI->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
//   UI->ApplyCommand("/vis/viewer/set/viewpointVector 0 0 100");
   //UI->ApplyCommand("/vis/viewer/zoom 0.04");
   UI->ApplyCommand("/vis/viewer/pan 20 0 mm");
   //UI->ApplyCommand("/vis/viewer/zoom 0.2");
   UI->ApplyCommand("/vis/viewer/set/style surface");

    	if (particleType == "OxygenPlus")
    	{
		for (nLevel=0 ; nLevel<=(nLevelMax-1) ; nLevel++)
   		{
			UI->ApplyCommand("/gun/particle ion");
			UI->ApplyCommand("/gun/ion 8 16 1 0");
		   	UI->ApplyCommand("/run/beamOn " + bulletString2.str());
   		}
    	}


	else 
	{	
   		for (nLevel=0 ; nLevel<=(nLevelMax-1) ; nLevel++)
   		{
			UI->ApplyCommand("/gun/particle " + particleType);
   			UI->ApplyCommand("/run/beamOn " + bulletString2.str());
		}
   	}
//   UI->ApplyCommand("/vis/viewer/set/viewpointVector -1 0 0");
//   UI->ApplyCommand("/vis/viewer/pan 5 -15 mm");
//   UI->ApplyCommand("/vis/viewer/zoom 2");

   //UI->ApplyCommand("/vis/viewer/set/style wireframe");
   UI->ApplyCommand("/vis/viewer/set/viewpointVector 1 1000 1");
   UI->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
   UI->ApplyCommand("/vis/viewer/pan -0.02 0.01 ");
   UI->ApplyCommand("/vis/viewer/zoom 0.5"); 
   UI->ApplyCommand("/vis/viewer/set/viewpointVector 1 2 1");

    session->SessionStart();
    delete session;
  }



  else             //  NO VISUALIZATION
  { 

    G4UImanager* UI = G4UImanager::GetUIpointer(); 

    UI->ApplyCommand("/run/initialize");
    UI->ApplyCommand("/tracking/verbose " + trackOutput);
    UI->ApplyCommand("/process/verbose 0");
    UI->ApplyCommand("/control/verbose 0");
    UI->ApplyCommand("/particle/process/verbose 0");

    	if (particleType == "OxygenPlus")
    	{
		for (nLevel=0 ; nLevel<=(nLevelMax-1) ; nLevel++)
   		{
			UI->ApplyCommand("/gun/particle ion");
			UI->ApplyCommand("/gun/ion 8 16 1 0");
		   	UI->ApplyCommand("/run/beamOn " + bulletString2.str());
   		}
    	}


	else 
	{	
   		for (nLevel=0 ; nLevel<=(nLevelMax-1) ; nLevel++)
   		{
			UI->ApplyCommand("/gun/particle " + particleType);
   			UI->ApplyCommand("/run/beamOn " + bulletString2.str());
		}
   	}

  }




  //delete session;
  delete visManager;
  
  // Job termination
  delete runManager;
  //delete UI ;  // comment this line out if you want to enter commands at end of run ( session needs to be commented out? )

  G4cout << "Start time: " << startTime << G4endl ;
  G4long endTime = time(NULL) ;
  G4cout << "End time: " << endTime << G4endl ;
  G4long difference = endTime - startTime ;
  G4cout << "Time elapsed (seconds): " << difference << G4endl ;
  G4cout << "Time elapsed (minutes): " << fixed << setprecision(1) << (G4float)difference/60.0 << G4endl ;
  return 0;
}
