
#ifndef RunAction_h
#define RunAction_h 1

#include <iostream>

#include "globals.hh"
#include "G4UserRunAction.hh"

class G4Run;

// ----------------------------------------------------------------------------

class RunAction : public G4UserRunAction
{
  public:

    RunAction();
   ~RunAction();

    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);


      
};

// ----------------------------------------------------------------------------

#endif
