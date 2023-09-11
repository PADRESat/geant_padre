
#include "G4ios.hh"
#include <iomanip>

#include "globals.hh"
#include "Randomize.hh"
#include "RunAction.hh"

#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"

#include <fstream>  
#include <stdlib.h>  
#include <iostream>  
#include <sstream>

#include "globalvar.h"

using namespace std ;

// ----------------------------------------------------------------------------

RunAction::RunAction()
{ 
}

// ----------------------------------------------------------------------------

RunAction::~RunAction()
{
}

// ----------------------------------------------------------------------------

void RunAction::BeginOfRunAction(const G4Run* aRun)
{  
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl ;
}

// ----------------------------------------------------------------------------

void RunAction::EndOfRunAction(const G4Run*)
{


}
