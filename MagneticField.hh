

#ifndef MagneticField_H
#define MagneticField_H 1

#include "globals.hh"
#include "G4MagneticField.hh"

class magneticField : public G4MagneticField
{
  public:
    magneticField();
    ~magneticField();

    void GetFieldValue( const  double Point[3],
                               double *Bfield ) const;

  private:
    G4double By_center;
    G4double By_edge;
    G4double zmin;
    G4double zmax;
};

#endif

