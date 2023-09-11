

#include "MagneticField.hh"
//#include "G4FieldManager.hh"
//#include "G4TransportationManager.hh"


magneticField::magneticField()
{
    By_center = 2240*gauss;
    By_edge   = 4000*gauss;
}

magneticField::~magneticField()
{;}

void magneticField::GetFieldValue(const double Point[3],double *Bfield) const
{


  Bfield[0] = 0 ;
  Bfield[2] = 0;

  if( (std::abs(Point[0]-(31.299*mm)) < 13.5*mm )
	&& std::abs(Point[1]-(0.0*mm)) < 5.0*mm 
	&& std::abs(Point[2]-( 0*mm)) < 4.0*mm )
  { Bfield[1] =  By_center; }

  else if( ( std::abs(Point[0]-(-44.05*mm)) < 13.5*mm )
	&& std::abs(Point[1]-(0.0*mm)) < 5.0*mm 
	&& std::abs(Point[2]-( 0*mm)) < 4.0*mm )
  { Bfield[1] = By_center; }

  else if( ( std::abs(Point[0]-(31.299*mm)) < 13.0*mm )
	&& std::abs(Point[1]-(6.0*mm)) < 1.0*mm 
	&& std::abs(Point[2]-( 0*mm)) < 4.0*mm )
  { Bfield[1] = By_edge; }

  else if( ( std::abs(Point[0]-(31.299*mm)) < 13.0*mm )
	&& std::abs(Point[1]-(-6.0*mm)) < 1.0*mm 
	&& std::abs(Point[2]-( 0*mm)) < 4.0*mm )
  { Bfield[1] = By_edge; }

  else if( ( std::abs(Point[0]-(-44.05*mm)) < 13.0*mm )
	&& std::abs(Point[1]-(6.0*mm)) < 1.0*mm 
	&& std::abs(Point[2]-( 0*mm)) < 4.0*mm )
  { Bfield[1] = By_edge; }

  else if( ( std::abs(Point[0]-(-44.05*mm)) < 13.0*mm )
	&& std::abs(Point[1]-(-6.0*mm)) < 1.0*mm 
	&& std::abs(Point[2]-( 0*mm)) < 4.0*mm )
  { Bfield[1] = By_edge; }


  else
  { Bfield[1] = 0.; }

 


}

