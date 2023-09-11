

#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;

#include "G4VUserDetectorConstruction.hh"
//#include "G4GDMLParser.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    DetectorConstruction();
    ~DetectorConstruction();


  public:

    G4VPhysicalVolume* Construct();

  public:


  private:
    
    // LOGICAL VOLUMES----------------------------------------------------------------------------------------

    G4LogicalVolume* world_log;
    G4LogicalVolume* magnetic_field_layer_log;
    G4LogicalVolume* detector_log;
    G4LogicalVolume* scatterer_log;


    // PHYSICAL VOLUMES ------------------------------------------------------------------------------------------------

    G4VPhysicalVolume* world_phys;
    G4VPhysicalVolume* magnetic_field_layer_phys;
    G4VPhysicalVolume* detector_phys;
    G4VPhysicalVolume* scatterer_phys;


};

#endif

