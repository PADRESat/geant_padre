

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4ParticleTable.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"


#include "G4VUserPrimaryGeneratorAction.hh"

class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction();

    void GeneratePrimaries(G4Event* anEvent);

  private:
    G4ParticleGun* particleGun;
    G4ParticleTable * particleTable;
};

#endif


