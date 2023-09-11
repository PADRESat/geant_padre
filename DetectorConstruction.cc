#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4Trap.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include <fstream>  
#include <stdlib.h>  
#include <iostream>  

//#include "G4UniformMagField.hh"
#include "MagneticField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"


#include "globalvar.h"

#include "G4UIcommand.hh"


DetectorConstruction::DetectorConstruction()
 :  	
	// --------------LOGICAL VOLUME INITIALIZATION---------------------------------------------

	world_log(0), 
	magnetic_field_layer_log(0), 
	detector_log(0),
    	scatterer_log(0),




	// ---------------PHYSICAL VOLUME INITIALIZATION-------------------------------------------------

 	world_phys(0),	
	magnetic_field_layer_phys(0),
	detector_phys(0),
    	scatterer_phys(0)
  

{;}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{




   //------------------------------------------------------ MAGNETIC FIELD 

  static G4bool fieldIsInitialized = false;
  if(!fieldIsInitialized)
  {
    magneticField* myField = new magneticField;
    G4FieldManager* fieldMgr
      = G4TransportationManager::GetTransportationManager()
        ->GetFieldManager();
    fieldMgr->SetDetectorField(myField);
    fieldMgr->CreateChordFinder(myField);
    fieldIsInitialized = true;
  }



   //------------------------------------------------------ ELEMENTS 

  G4double a;  // atomic mass 
  G4double amu;  // atomic number

 // G4Element* elH = new G4Element("Hydrogen", "H", 	amu= 1., a = 1.01*g/mole);
  G4Element* elBe = new G4Element("Beryllium", "Be", 	amu= 4., a = 9.0122*g/mole);
  /*G4Element* elC = new G4Element("Carbon", "C", 	amu= 6., a = 12.01*g/mole);
  G4Element* elN = new G4Element("Nitrogen", "N", 	amu= 7., a = 14.01*g/mole);
  G4Element* elO = new G4Element("Oxygen", "O", 	amu= 8., a = 16.00*g/mole);
  G4Element* elF = new G4Element("Fluorine", "F", 	amu= 9., a = 18.9984*g/mole);
  G4Element* elAl = new G4Element("aluminum", "Al", 	amu=13., a = 26.9815*g/mole);

  G4Element* elSi = new G4Element("silicon", "Si", 	amu=14., a = 28.0855*g/mole);
  G4Element* elAr = new G4Element("Argon", "Ar", 	amu=18., a = 39.95*g/mole);
  G4Element* elCr = new G4Element("Chromium", "Cr", 	amu=24., a = 51.9961*g/mole);
  G4Element* elFe = new G4Element("Iron", "Fe", 	amu=26., a = 55.8450*g/mole);
  G4Element* elCo = new G4Element("Cobalt", "Co", 	amu=27., a = 58.9332*g/mole);
  G4Element* elNi = new G4Element("Nickel", "Ni", 	amu=28., a = 58.6934*g/mole);

  G4Element* elCu = new G4Element("Copper", "Cu", 	amu=29., a = 63.5460*g/mole);
  G4Element* elZi = new G4Element("Zinc", "Zn", 	amu=30., a = 65.3900*g/mole);*/
  G4Element* elCd  = new G4Element("Cadmium","Cd", 	amu=48., a = 112.411*g/mole);/*
  G4Element* elSn = new G4Element("Tin", "Sn", 		amu=50., a = 118.7100*g/mole);*/
  G4Element* elTe  = new G4Element("Tellurium","Te", 	amu=52., a = 127.6*g/mole);/*
  G4Element* elSm = new G4Element("Samarium", "Sm", 	amu=62., a = 150.36*g/mole);
  G4Element* elPt = new G4Element("Platinum", "Pt", 	amu=78., a = 195.078*g/mole);
  G4Element* elPb = new G4Element("Lead", "Pb", 	amu=82., a = 207.1900*g/mole);
*/



  //------------------------------------------------------ MATERIALS


  G4double density;  // material density
  G4int nElem;  // number of elements
  G4int nAtoms; // number of atoms
  G4double fraction;  // in terms of mass

  G4Material* vacuum = 
  new G4Material("vacuum", amu= 1., a= 1.0*g/mole, density = 1.E-25*g/cm3);
/*
  G4Material* air = 
  new G4Material("air", density = 1.225e-3*g/cm3, nElem=3);
  air->AddElement(elN, fraction=0.78);
  air->AddElement(elO, fraction=0.21);
  air->AddElement(elAr, fraction=0.01);
*/
  G4Material* beryllium = 
  new G4Material("beryllium", density = 1.85*g/cm3, nElem=1);
  beryllium->AddElement(elBe, fraction=1.00);

 G4Material* CdTe = 
  new G4Material("CdTe", density= 5.85*g/cm3, nElem=2);
     CdTe->AddElement(elCd , nAtoms=1);
     CdTe->AddElement(elTe, nAtoms= 1);
/*
  G4Material* silicon = 
  new G4Material("silicon", density = 2.33*g/cm3, nElem=1);
  silicon->AddElement(elSi, fraction=1.00);

  G4Material* aluminum = 
  new G4Material("aluminum", density = 2.7*g/cm3, nElem=1);
  aluminum->AddElement(elAl, fraction=1.00);


  G4Material* kapton = 
  new G4Material("Kapton", density = 1.417*g/cm3, nElem=4);
  kapton->AddElement(elC, nAtoms=22);
  kapton->AddElement(elH, nAtoms=10);
  kapton->AddElement(elN, nAtoms=2);
  kapton->AddElement(elO, nAtoms=5);

  G4Material* BeCuAlloy = 
  new G4Material("BeCuAlloy", density = 8.90*g/cm3, nElem=2);
  BeCuAlloy->AddElement(elCu, fraction=0.97);
  BeCuAlloy->AddElement(elBe, fraction=0.03);


  G4Material* copper = 
  new G4Material("copper", density = 8.96*g/cm3, nElem=1);
  copper->AddElement(elCu, fraction=1.00);

  G4Material* kaptonFilm = 
  new G4Material("KaptonFilm", density = 1.42*g/cm3, nElem=4);
  kaptonFilm->AddElement(elC, fraction=0.6911);
  kaptonFilm->AddElement(elO, fraction=0.2092);
  kaptonFilm->AddElement(elN, fraction=0.0733);
  kaptonFilm->AddElement(elH, fraction=0.0264);



  G4Material* SmCoAlloy = 
  new G4Material("SmCoAlloy", density = 8.64*g/cm3, nElem=2);
  SmCoAlloy->AddElement(elCo, fraction=0.80);
  SmCoAlloy->AddElement(elSm, fraction=0.20);

  G4Material* vacoflux = 
  new G4Material("vacoflux", density = 8.12*g/cm3, nElem=2);
  vacoflux->AddElement(elCo, fraction=0.50);
  vacoflux->AddElement(elFe, fraction=0.50);

  G4Material* kovar = 
  new G4Material("kovar", density = 8.36*g/cm3, nElem=3);
  kovar->AddElement(elFe, fraction=0.525);
  kovar->AddElement(elNi, fraction=0.301);
  kovar->AddElement(elCo, fraction=0.174);

  G4Material* brass = 
  new G4Material("brass", density = 8.489*g/cm3, nElem=3);
  brass->AddElement(elCu, fraction=0.6150);
  brass->AddElement(elZi, fraction=0.3525);
  brass->AddElement(elPb, fraction=0.0325);

  G4Material* teflon = 
  new G4Material("teflon", density = 2.20*g/cm3, nElem=2);
  teflon->AddElement(elF, fraction=0.7598);
  teflon->AddElement(elC, fraction=0.2402);

  G4Material* peek = 
  new G4Material("peek", density = 1.3*g/cm3, nElem=3);
  peek->AddElement(elC, fraction=0.7915);
  peek->AddElement(elO, fraction=0.1665);
  peek->AddElement(elH, fraction=0.0420);

  G4Material* FR4 = 
  new G4Material("FR4_polyphenylene_ether", density = 1.1*g/cm3, nElem=3);
  FR4->AddElement(elC, fraction=0.7740);
  FR4->AddElement(elO, fraction=0.1718);
  FR4->AddElement(elH, fraction=0.0542);

  G4Material* diallyl = 
  new G4Material("diallyl phthalate", density = 1.8*g/cm3, nElem=3);
  diallyl->AddElement(elC, fraction=0.6828);
  diallyl->AddElement(elO, fraction=0.2599);
  diallyl->AddElement(elH, fraction=0.0573);

  G4Material* germanSilver = 
  new G4Material("German silver", density = 8.9*g/cm3, nElem=3);
  germanSilver->AddElement(elCu, fraction=0.6);
  germanSilver->AddElement(elNi, fraction=0.2);
  germanSilver->AddElement(elZi, fraction=0.2);

  G4Material* polyethermide = 
  new G4Material("polyethermide", density = 1.27*g/cm3, nElem=4);
  polyethermide->AddElement(elC, fraction=0.7499);
  polyethermide->AddElement(elO, fraction=0.1620);
  polyethermide->AddElement(elN, fraction=0.0473);
  polyethermide->AddElement(elH, fraction=0.0408);

  G4Material* bronze = 
  new G4Material("bronze_544", density = 8.89*g/cm3, nElem=4);
  bronze->AddElement(elCu, fraction=0.88);
  bronze->AddElement(elZi, fraction=0.04);
  bronze->AddElement(elPb, fraction=0.04);
  bronze->AddElement(elSn, fraction=0.04);

  G4Material* steel = 
  new G4Material("stainless_steel", density = 7.93*g/cm3, nElem=4);
  steel->AddElement(elFe, fraction=0.7299);
  steel->AddElement(elCr, fraction=0.18);
  steel->AddElement(elNi, fraction=0.09);
  steel->AddElement(elC, fraction=0.0001);

  G4Material* platinum = 
  new G4Material("platinum", density = 21.45*g/cm3, nElem=1);
  platinum->AddElement(elPt, fraction=1.00);

 */




  //--------- ROTATIONS AND TRANSLATIONS (TO BE USED IN VOLUME PLACEMENTS)
/*

  G4RotationMatrix* xRot90 = new G4RotationMatrix ;
  xRot90->rotateX((pi/2.0)*rad) ;

  G4RotationMatrix* xRot180 = new G4RotationMatrix ;
  xRot180->rotateX(pi*rad) ;

  G4RotationMatrix* xRot270 = new G4RotationMatrix ;
  xRot270->rotateX((3.0*pi/2.0)*rad) ;

  G4RotationMatrix* yRot45 = new G4RotationMatrix ;
  yRot45->rotateY((pi/4.0)*rad) ;

  G4RotationMatrix* yRot90 = new G4RotationMatrix ;
  yRot90->rotateY((pi/2.0)*rad) ;

  G4RotationMatrix* yRot180 = new G4RotationMatrix ;
  yRot180->rotateY(pi*rad) ;

  G4RotationMatrix* yRot270 = new G4RotationMatrix ;
  yRot270->rotateY((3.0*pi/2.0)*rad) ;


  G4RotationMatrix* zRot90 = new G4RotationMatrix ;
  zRot90->rotateZ((pi/2.0)*rad) ;

  G4RotationMatrix* zRot180 = new G4RotationMatrix ;
  zRot180->rotateZ(pi*rad) ;

  G4RotationMatrix* zRot270 = new G4RotationMatrix ;
  zRot270->rotateZ((3.0*pi/2.0)*rad) ;


  G4RotationMatrix* xyRot180 = new G4RotationMatrix ;
  xyRot180->rotateX(pi*rad) ;
  xyRot180->rotateY(pi*rad) ;


  G4RotationMatrix* xzRot180 = new G4RotationMatrix ;
  xzRot180->rotateX(pi*rad) ;
  xzRot180->rotateZ(pi*rad) ;

  G4RotationMatrix* yzRot180 = new G4RotationMatrix ;
  yzRot180->rotateY(pi*rad) ;
  yzRot180->rotateZ(pi*rad) ;

  G4RotationMatrix* z90y180Rot = new G4RotationMatrix ;
  z90y180Rot->rotateZ((pi/2.0)*rad) ;
  z90y180Rot->rotateY(pi*rad) ;

  G4RotationMatrix* z270x180Rot = new G4RotationMatrix ;
  z270x180Rot->rotateZ((3.0*pi/2.0)*rad) ;
  z270x180Rot->rotateX(pi*rad) ;

*/




  G4double dx, dy, dz ;
  G4double x, y, z ;


  // WHETHER TO CHECK IF VOLUMES OVERLAP
  G4bool checkOverlap = true ;




  //  WORLD
  dx = 40*cm;
  dy = 40*cm;
  dz = 40*cm;

  G4Box* box_world = new G4Box("world_box", dx, dy, dz);
  world_log = new G4LogicalVolume(box_world, vacuum,"world_log",0,0,0);
  world_phys = new G4PVPlacement(0,G4ThreeVector(), world_log,"world",0,false,0);
  

  //  SCATTERER
  G4float radius_inner = 0.0*cm ;
  G4float radius_outer = 5.5*cm ;
  G4float half_length = (6.2/2.0)*cm ;
  G4float phi_start = 0*pi ;    // in radians
  G4float phi_total = 2*pi ;   // in radians
 
  G4Tubs* tube_scatterer = new G4Tubs("tube_scatterer",radius_inner, radius_outer, half_length, phi_start, phi_total); 
  scatterer_log = new G4LogicalVolume(tube_scatterer, beryllium,"scatterer_log",0,0,0); 
  scatterer_phys = new G4PVPlacement(0,G4ThreeVector(0, 0, 2*half_length), scatterer_log,"scatterer",world_log,false,0, checkOverlap);

 //  DETECTORS
 G4int  Distance  =  2*6.6*cm;
 
 G4int NDetectors = 8;
 G4int Angle = ( 360 / NDetectors );
 G4float zPosition =  10.0*cm;
  G4double pi = 3.14159;
  G4int j=0;
  G4int i = 0;


  for (j=0;j< 360; j+=45)
    {  
	i = i+1;
      G4String idxStr;
      if (i < 10)
        idxStr = "00" + G4UIcommand::ConvertToString(G4int(i));
      else if (i < 100)
        idxStr = "0" + G4UIcommand::ConvertToString(G4int(i));
      else
        idxStr = G4UIcommand::ConvertToString(G4int(i));


	
  G4RotationMatrix* myRotation = new G4RotationMatrix();
  if ( i % 2 == 0){

   myRotation->rotateX(-90.*deg),
   myRotation->rotateY(1.*j*deg),
   myRotation->rotateZ(90.*deg);

}

 else if ( i== 3 || i ==7){

   myRotation->rotateX(-90.*deg),
   myRotation->rotateY(90.*j*deg),
   myRotation->rotateZ(90.*deg);

}
else {

   myRotation->rotateX(1.*j*deg),
   myRotation->rotateY(-90*deg),
   myRotation->rotateZ(0.);

}
/*	physiSingleDetector = new G4PVPlacement(myRotation,
		G4ThreeVector(0.5*Distance*cos(j*pi/180.),0.5*Distance*sin(j*pi/180.),BeHeight+xyWafer-1.0*cm),
		"SingleDetector",
		logicSingleDetector,
		fPhysiWorld,
		false,
		i);
*/


  dx = 2.82*cm;
  dy = 2.82*cm;
  dz = 1.0*mm;



  G4Box* box_detector = new G4Box("detector_box", dx/2., dy/2., dz/2.);
  detector_log = new G4LogicalVolume(box_detector, CdTe,"detector_log",0,0,0);
//  detector_phys = new G4PVPlacement(0,G4ThreeVector(0,0, (7.0+2.82-1.0)*cm), detector_log,"detector", world_log,false,0, checkOverlap);
  detector_phys = new G4PVPlacement(myRotation,G4ThreeVector( 0.5*Distance*cos(j*pi/180.),0.5*Distance*sin(j*pi/180.), (7.0+2.82-1.0)*cm), 
		detector_log,"detector"+idxStr, world_log,false,i, checkOverlap);

}





  //------------------------------ MAGNETIC FIELD LAYERS (just for visualization purposes) ----------------------
/*
  G4double field_x = 25.0*mm;
  G4double field_y = 12.0*mm;
  G4double field_z = 1.0*mm;
  G4Box* fieldLayer_box = new G4Box("fieldLayer_box", field_x/2.0,field_y/2.0,field_z/2.0);
  magnetic_field_layer_log = new G4LogicalVolume(fieldLayer_box, vacuum,"fieldLayer_log",0,0,0);
  //magnetic_field_layer_log = new G4LogicalVolume(fieldLayer_box, air,"fieldLayer_log",0,0,0);

  for(G4int i=0;i<8;i++) // loop for 8 layers
  {
    G4double fieldPos_x = 31.35*mm;
    G4double fieldPos_y = 0.0*mm;
    G4double fieldPos_z = 0.5*mm + (i-4)*1.0*mm;
    magnetic_field_layer_phys = new G4PVPlacement(0,
               G4ThreeVector(fieldPos_x,fieldPos_y,fieldPos_z*cm),
               magnetic_field_layer_log,"fieldLayer",world_log,false,i, checkOverlap);
  }

  for(G4int i=9;i<17;i++) // loop for 8 layers
  {
    G4double fieldPos_x =  -44.051*mm;
    G4double fieldPos_y = 0.0*mm;
    G4double fieldPos_z = 0.5*mm + (i-4-9)*1.0*mm;
    magnetic_field_layer_phys = new G4PVPlacement(0,
               G4ThreeVector(fieldPos_x,fieldPos_y,fieldPos_z*cm),
               magnetic_field_layer_log,"fieldLayer",world_log,false,i,checkOverlap);
  }
*/


  //-----------------------------------DETECTOR STACKS---------------





/*
CODE LIKE THIS (for copy and paste, only alter dimensions,translations,centers):
dx1 = ?? ;
dy1 = ?? ;
dz1 = ?? ;

dx2 = ?? ;
dy2 = ?? ;
dz2 = ?? ;

transX = ?? ;
transY = ?? ;
transZ = ?? ;

centerX = 
centerY
centerZ

step01 = new G4Box(...dx1*mm,dy1*mm,dz1*mm);
step02 = new G4Box(...dx2*mm,dy2*mm,dz2*mm);
step03 = new G4SubtractionSolid("step03",step01, step02,0,G4ThreeVector(transZ*mm,transY*mm,transZ*mm)

part_log = new G4LogicalVolume()
part_phys = new G4PVPlacement(...G4ThreeVector(centerX*mm,...))

*/




  //------------- VISUALIZATION----------------------------------- 

  G4bool visible = 1;  //visible

  G4VisAttributes* invisible = new G4VisAttributes(0, G4Colour(0.0,1.0,0.0)); 
  //G4VisAttributes* green = new G4VisAttributes(1, G4Colour(0.0,1.0,0.0));  
  G4VisAttributes* red = new G4VisAttributes(visible,G4Colour(1.0,0.0,0.0)); 
  G4VisAttributes* yellow = new G4VisAttributes (visible, G4Colour(1.0, 1.0, 0.0)); 
  G4VisAttributes* white = new G4VisAttributes (visible, G4Colour(1.0, 1.0, 1.0)); 
/*
  G4VisAttributes* gray = new G4VisAttributes (visible, G4Colour(0.7, 0.7, 0.7)); 
  G4VisAttributes* cyan = new G4VisAttributes(visible,G4Colour(0.0,1.0,1.0));  
  G4VisAttributes* magenta = new G4VisAttributes(visible,G4Colour(1.0,0.0,1.0));  
  G4VisAttributes* blue = new G4VisAttributes(visible,G4Colour(0.0,0.0,1.0));  
  G4VisAttributes* grayDark = new G4VisAttributes (visible, G4Colour(0.5, 0.5, 0.5)); 
  G4VisAttributes* brown = new G4VisAttributes (visible, G4Colour(0.45, 0.25, 0.0)); 
  G4VisAttributes* orange = new G4VisAttributes (visible, G4Colour(1.0, 0.5, 0.0)); 


*/
 

 

  world_log		->SetVisAttributes(invisible);
  detector_log		 ->SetVisAttributes(white);  // white

  scatterer_log		 ->SetVisAttributes(red);  // white

  //magnetic_field_layer_log	->SetVisAttributes(yellow);  // yellow 






  return world_phys;

  

}


