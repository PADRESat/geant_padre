
#include "EventAction.hh"
#include "SteppingAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"


#include <fstream>  
#include <stdlib.h>  
#include <iostream>  

#include "globalvar.h"

using namespace std ;
 



EventAction::EventAction()
{}


 
EventAction::~EventAction()
{}



void EventAction::BeginOfEventAction(const G4Event* evt)
{

     	G4int event_id = evt->GetEventID();
	if(event_id%1000000 == 0) 	{ G4cout << G4endl << "EVENT # " << event_id << " START" << G4endl; }
  	//ofstream eventNumber (eventNumberFile, ios::trunc);

     	//G4int event_id = evt->GetEventID();
     	//eventNumber << event_id << G4endl ;

	//ofstream outputHits(hitsFile, ios::app);
	//outputHits << "Event # " << evt->GetEventID() << " start" << G4endl;
	//G4cout << G4endl << "EVENT # " << evt->GetEventID() << " START" << G4endl;

}
 
void EventAction::EndOfEventAction(const G4Event* evt)
{
	G4int event_id = evt->GetEventID();
	if(event_id%1000000 == 0) 	{ G4cout << G4endl << "EVENT # " << event_id << " END" << G4endl; }
	//ofstream outputHits(hitsFile, ios::app);
     	//G4int event_id = evt->GetEventID();
	//outputHits << "#   numberOfParticles = " <<  event_id << G4endl ;
}
