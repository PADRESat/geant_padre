


#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"

#include "Randomize.hh"

#include <math.h>


#include <fstream>  
#include <stdlib.h>  
#include <iostream>  

#include "globalvar.h"


#include "G4GeneralParticleSource.hh"



using namespace std ;






PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  G4int n_particle = 1; 
  particleGun = new G4ParticleGun(n_particle);

  

  particleTable = G4ParticleTable::GetParticleTable();

  // Default particle
  //
  //particleGun->SetParticleDefinition(particleTable->FindParticle(particleType));
  //particleGun->SetParticleEnergy(12*keV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}



void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{


 if (gunType==9){


   

 
  
   G4float energy_min = 20.0 ;
   G4float energy_max = 500.0 ;
  
   G4int   n_bins = 100 ;
   G4float bin_width = (energy_max - energy_min)/n_bins ;
   G4float bin_edges_lower [n_bins] ; 
   G4float bin_midpoints  [n_bins] ; 
   G4float bin_edges_upper  [n_bins] ;
    
   for (G4int i=0 ; i<n_bins ; i++)
	{	
	    bin_edges_lower[i] = energy_min + (i*bin_width) ;
	    bin_midpoints[i]   = energy_min + ( ((2*i)+1)/2.0 ) * bin_width ;
	    bin_edges_upper[i] = energy_min + ((i+1)*bin_width) ;	
	}

   G4float alpha = -3.0 ;
   G4float fluxes_lower[n_bins];
   G4float fluxes_mid[n_bins];
   G4float fluxes_upper[n_bins];

  for (G4int i=0 ; i<n_bins ; i++)
	{	
	  fluxes_lower [i] = pow(bin_edges_lower[i],alpha);
	  fluxes_mid [i]   = pow(bin_midpoints[i],alpha);
	  fluxes_upper [i] = pow(bin_edges_upper[i],alpha);
	}
     

  G4float flux_total ; 
  G4float integrated_flux ; 

   for (G4int i=0 ; i<n_bins ; i++)
	{	
          if (i == 0) 
	    {
	      flux_total = 0;
	      integrated_flux =0;
	    }
	  flux_total += fluxes_mid[i];
	  integrated_flux += fluxes_mid[i] * bin_width;
	}






  G4float sum ;
  G4float weights[n_bins] ;
  G4float weights_cumulative[n_bins] ;

   for (G4int i=0 ; i<n_bins ; i++)
	{
	  if (i == 0) sum = 0;
	  weights[i] = fluxes_mid[i]/flux_total ;
	  sum += weights[i] ;
	  weights_cumulative[i] =sum ;
	}  




   G4cout << "ENERGIES: lower  mid  upper    FLUXES: lower  mid  upper   WEIGHTS: bin   cumulative" << G4endl ;
   for (G4int i=0 ; i<n_bins  ; i++)
     {
        G4cout << std::setprecision(1) << std::fixed 
	       << std::setw(10) << bin_edges_lower[i] 
	       << std::setw(10) << bin_midpoints[i] 
	       << std::setw(10) << bin_edges_upper[i] 
	       
	       << std::setprecision(1) << std::scientific 
	       << std::setw(10) << fluxes_lower[i] 
	       << std::setw(10) << fluxes_mid[i] 
	       << std::setw(10) << fluxes_upper[i] 

	       << std::setprecision(3) << std::fixed 
	       << std::setw(10) << weights[i] 
	       << std::setw(10) << weights_cumulative[i] 

	       << G4endl ;      
      }  

   G4cout  << "FLUX TOTAL, INTEGRATED FLUX"
	   << std::setprecision(3) << std::scientific 
	   << std::setw(10) << flux_total
	   << std::setw(10) << integrated_flux 
	   << G4endl ;




   G4float flux_lower_cumulative [n_bins] ;
   G4float flux_mid_cumulative [n_bins] ;
   G4float flux_upper_cumulative [n_bins] ;
  



   G4float random_value = G4UniformRand(); 
   G4float random_flux_cumulative = random_value*integrated_flux ;
   G4float discrepancy [n_bins] ;
   G4long index [2] ;

   G4cout << "RANDOM VALUE: " << std::setprecision(4) << std::fixed << random_value  << G4endl ; 

   for (G4int i=0 ; i<n_bins ; i++)
     {
       G4float difference = random_flux_cumulative-flux_mid_cumulative[i]   ;
       G4cout  <<  random_flux_cumulative << "  " << flux_mid_cumulative[i] << "  difference: " << difference << G4endl ;
       if (difference > 0)
	  {
	    index[0]=i ;
	  }  
       else 
	  {
	    index[1]=i;
	    break ;
	  }  
      }  

   G4cout << "    INDICES: " << index[0] << "  " << index[1] << G4endl ; 

   
  /*
 
  
  n_particles = 1000000
  seed=1
  random_values = randomu(seed, n_particles)  
    random_energies = fltarr(n_particles)
  
  
  for i=0, n_particles-1 do begin
    random_value = random_values[i]
    random_flux_cumulative = random_value*integrated_flux
    discrepancy = ABS(random_flux_cumulative[0]-flux_mid_cumulative)
    index = where(discrepancy EQ MIN(discrepancy))
    random_energies[i] = bin_midpoints[index] 
    ;random_values[i] = random_value
  endfor

*/


 	const G4double PI = 4.0*atan(1.0); 
    	G4double beamRadius = 15;
 	G4double x,y,z;

  	G4int bullets = atoi(events);

	// getting random initial position
	for (G4int i=0; i<=atoi(seed); i++){ G4UniformRand(); }
	G4double randTheta = ( G4UniformRand()) * (2*PI);
	G4double randRadialLength = beamRadius*sqrt(G4UniformRand());
        x = randRadialLength*cos(randTheta);
	y = randRadialLength*sin(randTheta);        
        z = 15.0;
  	G4ThreeVector initialPosition(x*cm, y*cm, z*cm);  
  	particleGun->SetParticlePosition(initialPosition);

	particleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, -1)) ;
	particleGun->SetParticlePolarization(G4ThreeVector(1,0,0));

	G4double minEnergy = 20*keV ;
	G4double maxEnergy = 500*keV ;
	G4double randomEnergy = (maxEnergy-minEnergy)*G4UniformRand() + minEnergy ;
	particleGun->SetParticleEnergy(randomEnergy) ;
	
	particleGun->GeneratePrimaryVertex(anEvent);




	}




        else if (gunType==1){
	particleGun->SetParticlePosition(G4ThreeVector(63.1*mm, -12.5*mm, -100*mm));  // targets +z side FOIL
  	particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
  	particleGun->GeneratePrimaryVertex(anEvent);  
	}

	else if (gunType==2){
  	particleGun->SetParticlePosition(G4ThreeVector(-25.001*mm, -12.501*mm, -100*mm));   // targets +z side OPEN
  	particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
  	particleGun->GeneratePrimaryVertex(anEvent);
	particleGun->SetParticleEnergy(200*keV);
	}

	else if (gunType==3){
  	particleGun->SetParticlePosition(G4ThreeVector(25.000*mm, -12.500*mm, 100*mm));  // targets -z side OPEN
  	particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,-1));
  	particleGun->GeneratePrimaryVertex(anEvent);
	}

	else if (gunType==4){
  	particleGun->SetParticlePosition(G4ThreeVector(25.000*mm, -12.500*mm, -100*mm));  // targets -z side FOIL
  	particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
  	particleGun->GeneratePrimaryVertex(anEvent); 
	} 

	else if (gunType==5){
		G4double x,y,z;

		//z = 100;

		// ION DETECTOR, dead layer at z=-13.281 mm
		for(z=10; z<=10; z=z+1.0)
		{
			for(x = -5.0; x<=5.0; x=x+1.0)
			{
				for(y = -2.0; y<=2.0; y=y+1.0)	
				{
					particleGun->SetParticlePosition(G4ThreeVector(x*mm, y*mm, z*cm));  
  					particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,-1));
					particleGun->SetParticleEnergy(1.0*MeV);
  					//particleGun->SetParticleDefinition(particleTable->FindParticle("proton"));
  					particleGun->GeneratePrimaryVertex(anEvent); 
				}
			}
		}


	} 

	// to enable hard coded position, momentum
        else if (gunType==6){		
  	particleGun->GeneratePrimaryVertex(anEvent);  
	}


        else if (gunType==7){		
  	
	//G4float radius_source_sphere = 100*mm;  
  	G4float radius_source_sphere = 150*mm;  //if we want to put the particles on a sphere surrounding the instrument
  	const G4double PI = 4.0*atan(1.0);

	// getting random initial position of particle
  	G4float theta_position = acos( (G4UniformRand()-0.5)*2);
  	G4float phi_position = 2*PI*G4UniformRand();
  	G4float xpos = radius_source_sphere*sin (theta_position)*cos (phi_position);
  	G4float ypos = radius_source_sphere*sin (theta_position)*sin (phi_position);
  	G4float zpos = radius_source_sphere*cos (theta_position);

	G4float center_of_detectors_X = ( (-12.3+63.1)/2 )*mm;
	G4float center_of_detectors_Y = -12.5*mm;
	G4float center_of_detectors_Z = ( (13.948-17.935)/2 )*mm;

	// translating sphere to center on center of 6 detectors
	xpos += center_of_detectors_X ; 
	ypos += center_of_detectors_Y ;
	zpos += center_of_detectors_Z ;

//	G4cout << "Center of source: " << xpos << ", " << ypos << ", " << zpos ;
  	
	particleGun->SetParticlePosition(G4ThreeVector(xpos, ypos, zpos));



	// getting random initial direction of particle, hemisphere
  	//G4float theta_momentum = G4UniformRand()*PI/2.0;
  	G4float theta_momentum = acos(sqrt(G4UniformRand()));  // theta ranges from 0 to PI/2
  	G4float phi_momentum = 2*PI*G4UniformRand();
 
        G4double direction [4]; 
  	direction [1] = sin (theta_momentum)*cos (phi_momentum);
  	direction [2]  = sin (theta_momentum)*sin (phi_momentum);
  	direction [3]  = cos (theta_momentum);

	//rotation matrix, to frame in which + z-axis of new coordinate system
	//         extends from particle's initial position to origin of detector coordinate system

        // 1st rotation of points, about x-axis, CW from perspective of x-axis aimed at viewer
        G4double rot1[4][4];
        rot1[1][1] = 1, 	rot1[1][2] = 0,           	  	rot1[1][3] = 0;
        rot1[2][1] = 0, 	rot1[2][2] = cos(-theta_position), 	rot1[2][3] = -sin(-theta_position);
        rot1[3][1] = 0, 	rot1[3][2] = sin(-theta_position), 	rot1[3][3] = cos(-theta_position);
            

        // 2nd rotation of points, about z-axis, CW from perspective of z-axis aimed at viewer
        G4double rot2[4][4]; 
        rot2[1][1] = cos(phi_position - PI/2.0), 	rot2[1][2] = -sin(phi_position - PI/2.0), 	rot2[1][3] = 0;
        rot2[2][1] = sin(phi_position - PI/2.0), 	rot2[2][2] = cos(phi_position - PI/2.0),  	rot2[2][3] = 0;
        rot2[3][1] = 0,         			rot2[3][2] = 0,          			rot2[3][3] = 1;    
            
	// full rotation matrix
        G4double rotation[4][4]; 
	for (G4int i=1 ; i<=3 ; i++)
	{	
		for (G4int k=1;  k<=3; k++)
		{
			rotation[i][k] = rot2[i][1]*rot1[1][k] + rot2[i][2]*rot1[2][k] + rot2[i][3]*rot1[3][k] ;
		}
	}

	// now rotating initial direction to new coordinate system as defined by rotation matrix above, and then reflecting (minus signs)
        G4double directionRot [4]; 
	for (G4int i=1 ; i<=3; i++)
	{	
		directionRot [i] = -rotation[i][1]*direction[1] - rotation[i][2]*direction[2] - rotation[i][3]*direction[3];

	}
	//G4cout << "Initial Direction  :  (" << direction[1] << ", " << direction[2] << ", " << direction[3] << ")" << G4endl ;
  	//G4cout << G4endl << "MomentumParticleGun:  (" << fixed << setprecision(7) << directionRot[1] << ", " << directionRot[2] << ", " << directionRot[3] << ")" << G4endl ;
  	particleGun->SetParticleMomentumDirection(G4ThreeVector(directionRot[1], directionRot[2], directionRot[3]));




	// generating random energy
	// getting random initial position
	for (G4int i=0; i<=atoi(seed); i++){ G4UniformRand(); }
	G4double randExponent = ( atof(energyMax) - atof(energyMin) )*G4UniformRand() + atof(energyMin) ;

//	G4double randExponent = 7.0*G4UniformRand() ;
	G4double randEnergy = pow(10.0, randExponent ) ;
	particleGun->SetParticleEnergy(randEnergy*keV);

  	particleGun->GeneratePrimaryVertex(anEvent);

	}

 





        else if (gunType==8){	


		G4double x,y,z; //postions
		G4double px,py,pz; //momenta


  		const G4double PI = 4.0*atan(1.0);
  		G4float theta_momentum = acos ( sqrt ( ( G4UniformRand() ) ) )/1.0;
  		G4float phi_momentum= 2*PI*G4UniformRand();
  		px = sin (theta_momentum)*cos (phi_momentum);
  		py = sin (theta_momentum)*sin (phi_momentum);
		pz =   -cos (theta_momentum);

		// ION DETECTOR, dead layer at z=-13.281 mm
		for(z=-13.27; z<=36.73; z=z+10.0)
		{
			x = 31.350 ;
			y = 0.0	;
			particleGun->SetParticlePosition(G4ThreeVector(x*mm, y*mm, z*mm));  
  			particleGun->SetParticleMomentumDirection(G4ThreeVector(px, py, pz));
			particleGun->SetParticleEnergy(5.5*MeV);
  			//particleGun->SetParticleDefinition(particleTable->FindParticle("proton"));
  			particleGun->GeneratePrimaryVertex(anEvent); 

		}

		//  ELECTRON DETECTOR, foil at z=19.97 mm
		for(z=19.98; z<=69.98; z=z+10.0)
		{
			x = -46.051;
			y =  0.0	;
			particleGun->SetParticlePosition(G4ThreeVector(x*mm, y*mm, z*mm));  
			particleGun->SetParticleMomentumDirection(G4ThreeVector(px, py, pz));
			particleGun->SetParticleEnergy(5.5*MeV);
  			//particleGun->SetParticleDefinition(particleTable->FindParticle("proton"));
  			particleGun->GeneratePrimaryVertex(anEvent); 
		}


	}



}




