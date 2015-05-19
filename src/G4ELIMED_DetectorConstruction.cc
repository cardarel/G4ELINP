//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
//=================================================================================
// PAOLO CARDARELLI, amendements 02/09/2014:
//StainlessSteel material added for beampipe 
//edited fConcreteA1Distance, added: 2*fRomanPotWindowLength
//=================================================================================

//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4ELIMED_DetectorConstruction.hh"
#include "G4RunManager.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Cons.hh"
#include "G4UnionSolid.hh"
#include "G4AssemblyVolume.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4UniformMagField.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"

#include "G4ELIMED_SensitiveDetector.hh"
#include "G4ELIMED_SensitiveDetectorHit.hh"

#include "G4Polyhedra.hh"
#include "G4Trd.hh"
#include "G4SubtractionSolid.hh"

#include "G4MultiFunctionalDetector.hh"
#include "G4PSDoseDeposit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ELIMED_DetectorConstruction::G4ELIMED_DetectorConstruction():fWorldLogic(0){
    
    fMessenger = new G4ELIMED_DetectorConstructionMessenger(this);
    DefineMaterials();
    
    // World
    fWorldSize = G4ThreeVector(20000. * CLHEP::cm,20000. * CLHEP::cm,20000. * CLHEP::cm);
    
    // Beam pipe e Modules
    bBeamPipe = true;
    bConcrete = true;
    bRomanPot = true;
    bCollimatorSupport = true;
    bCollimator = true;
    bTransparentDetector = true;
    bModulesOn = true;
    
    // Pb disks
    PbDisks = 0;
	bLine=1;
	ResetDetectorForSetup(bLine);

    // Collimator
    fCollimatorNumber = 14;   
    fCollimatorDistance = 0. * CLHEP::mm;
    fCollimatorAperture = 0.59 * CLHEP::mm;

	bCollimatorRelativeRandomDisplacement = false;
	bCollimatorAngleManual = false;
	SetCollRandDisplMean(0. *  CLHEP::mm);
	SetCollRandDisplSigma(0.001 *  CLHEP::mm);

    fRomanPotSupportAngle = G4ThreeVector(0.,0.,0.);
    fRomanPotSupportPosition = G4ThreeVector(0.,0.,0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

G4ELIMED_DetectorConstruction::~G4ELIMED_DetectorConstruction(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4ELIMED_DetectorConstruction::ResetDetectorForSetup(int line){


	bLine=line;
	//Collimator center distance
	 fCollimatorCenterDistance = 1025.5 * CLHEP::cm;
    if(bLine==1){
        fCollimatorCenterDistance = 904. * CLHEP::cm;
			}
    // Roman Pot
    fRomanPotWindowLength = 2.5 * CLHEP::cm;
    fRomanPotWindowInnerRadius = 2.16 * CLHEP::cm;
    fRomanPotWindowOuterRadius = 10. * CLHEP::cm;
    
    fRomanPotLength = 47. * CLHEP::cm;
    fRomanPotInnerRadius = 8.1 * CLHEP::cm;
    fRomanPotOuterRadius = 8.35 * CLHEP::cm; 
          
    // Beam Pipe
    fBeamPipeA0Length = fCollimatorCenterDistance - 0.5 * fRomanPotLength - fRomanPotWindowLength;
    /*if(bLine==1){
        fBeamPipeA0Length = 861. * CLHEP::cm;
    }*/
    fBeamPipeA0InnerRadius = 2. * CLHEP::cm;
    fBeamPipeA0OuterRadius = 2.16 * CLHEP::cm;
    
    fBeamPipeA2Length = 1188.5 * CLHEP::cm - fCollimatorCenterDistance - 0.5 * fRomanPotLength - fRomanPotWindowLength;
    if(bLine==1){
        fBeamPipeA2Length = 1067 * CLHEP::cm - fCollimatorCenterDistance - 0.5 * fRomanPotLength - fRomanPotWindowLength;
			}
    
    // Concrete
    if(bLine==1)
	{
	// High Energy line variables definition for walls
	fRoomWidth = 1000. * CLHEP::cm;
	fRoomLength = 1239. * CLHEP::cm;
	fRoomHeigth = 500. * CLHEP::cm;

	fBeamHeigth = 150 * CLHEP::cm; //beamline heigth from floor
	fRoomShiftX = -177.5 * CLHEP::cm; // shift on x-axis of the room center with respect to beam direction axis
	fRoomShiftY = fRoomHeigth * 0.5 - fBeamHeigth; // shift on y-axis of the room center with respect to beam direction axis	

	fFloorThickness = 150. * CLHEP::cm;
	fTopThickness = 150. * CLHEP::cm; //ceiling thickness
	fWallThickness = 150. * CLHEP::cm;
	fWallThickness2 = 200. * CLHEP::cm; // only for HE line, left wall has different thickness
	fWallHeigth =  700.* CLHEP::cm; // height of side walls

	fConcreteA0RadiusPipe = 2.16 * CLHEP::cm;
	fConcreteA0Distance = 260. * CLHEP::cm + fWallThickness * 0.5;

	}
	else
 	{
	// Low Energy line variables definition for walls

	fRoomWidth = 850. * CLHEP::cm;
	fRoomLength = 3850. * CLHEP::cm;
	fRoomHeigth = 500. * CLHEP::cm;
	
	fBeamHeigth = 150 * CLHEP::cm; //beamline heigth from floor
	fRoomShiftX = 147. * CLHEP::cm; // shift on x-axis of the room center with respect to beam direction axis
	fRoomShiftY = fRoomHeigth * 0.5 - fBeamHeigth; // shift on y-axis of the room center with respect to beam direction axis

	fFloorThickness = 150. * CLHEP::cm;
	fTopThickness = 150. * CLHEP::cm; //ceiling thickness
	fWallThickness = 150. * CLHEP::cm;
	fWallThickness2 = 150. * CLHEP::cm; // only for HE line, left wall has different thickness
	fWallHeigth =  700.* CLHEP::cm; // height of side walls
	
	fConcreteA0RadiusPipe = 2.16 * CLHEP::cm;
	fConcreteA0Distance = 611. * CLHEP::cm + fWallThickness* 0.5;
	}

	//A1 shielding block concrete - Same for HE and LE lines
 	fConcreteA1Length = 100. * CLHEP::cm;
	fConcreteA1Width = 200. * CLHEP::cm;
	fConcreteA1Height = 250. * CLHEP::cm;
	fConcreteA1RadiusPipe = 2.16 * CLHEP::cm;
	fConcreteA1Distance = fBeamPipeA2Length + fRomanPotLength + fBeamPipeA0Length + 2*fRomanPotWindowLength - fConcreteA1Length * 0.5;
    
    // Collimator
    fCollimatorLength = 20. * CLHEP::mm;
    fCollimatorWidth = 30. * CLHEP::mm;
    fCollimatorHeight = 40. * CLHEP::mm;
    
    fCollimatorSupportA0B0Width = 90. * CLHEP::mm;
    fCollimatorSupportA0B0Height = 70. * CLHEP::mm;
    
    fCollimatorSupportA0B1Width = 80. * CLHEP::mm;
    fCollimatorSupportA0B1Distance = -5. * CLHEP::mm;
    
    fCollimatorSupportA1B0Length = 5. * CLHEP::mm;
    
    fCollimatorSupportA1B1Width = 60. * CLHEP::mm;

    // Girders, Pedestals and vacuum cahmbers
    fGirderHeight = 214. * CLHEP::mm;
    fGirderWidth = 124. * CLHEP::mm;
    fGirderThickness = 12. * CLHEP::mm;
    fGirderJointLength  = 246. * CLHEP::mm;
    
    fPedestalHeight  = 645. * CLHEP::mm;
    fPedestalM30Height  = 752. * CLHEP::mm; 
    fPedestalM31Height  = 922. * CLHEP::mm;        
    fPedestalWidth = 300. * CLHEP::mm;
    fPedestalLength = 300. * CLHEP::mm; 
    fPedestalThickness = 10. * CLHEP::mm;
    
    fGirderY = - 400. * CLHEP::mm - fGirderHeight * 0.5;
    fGirderM30Y = 962. * CLHEP::mm - fBeamHeigth;
    fGirderM31Y = 1132. * CLHEP::mm - fBeamHeigth;
    fPedestalY = - fBeamHeigth + fPedestalHeight * 0.5;
    fPedestalM30Y = - fBeamHeigth + fPedestalM30Height * 0.5;
    fPedestalM31Y = - fBeamHeigth + fPedestalM31Height * 0.5;
    fM27AGirderLength = 1900. * CLHEP::mm;
    fM30GirderLength = 3000.* CLHEP::mm;
    fM31GirderLength = 2244. * CLHEP::mm;
    
    fCSPECInnerRadius = 195. * CLHEP::mm;
    fCSPECOuterRadius = 200. * CLHEP::mm;
    fCSPECLength = 3000. * CLHEP::mm;
    fCSPECWindowLength = 20. * CLHEP::mm;
    
    if(bLine==1)
		{//H.E. line
		fThetaElectron = 0.12967 * CLHEP::rad;
		fThetaM34 = 0.12967 * CLHEP::rad + (3.14159 * CLHEP::rad * 0.5 - 0.12967 * CLHEP::rad) * 0.5;
		
		fM32GirderLength = 889. * CLHEP::mm * cos(fThetaElectron);
		fM33GirderLength = 2600. * CLHEP::mm;
		fM34GirderLength = 2350. * CLHEP::mm;
						
		fM27ADistance = fConcreteA0Distance + fWallThickness * 0.6 + fM27AGirderLength * 0.5;
		fM30Distance = fConcreteA1Distance + fConcreteA1Length * 0.5 + 164. * CLHEP::mm + fM30GirderLength * 0.5;
		fM31Distance = fConcreteA1Distance + fConcreteA1Length * 0.5 + 3311. * CLHEP::mm + fM31GirderLength * 0.5;
		fM32Distance = fConcreteA1Distance - fConcreteA1Length * 0.5 -  (156. * CLHEP::mm) * cos(fThetaElectron) - fM32GirderLength * 0.5;
		fM33Distance = fConcreteA1Distance + fConcreteA1Length * 0.5 + 294. * CLHEP::mm + fM33GirderLength * 0.5;
		fM34Distance = fConcreteA1Distance + fConcreteA1Length * 0.5 + 4383. * CLHEP::mm; 
		
		fM32X = 503.4 * CLHEP::mm; 
		fM33X = 908. * CLHEP::mm; 
		fM34X = 1765. * CLHEP::mm; 
		
		//M27A MAgnet
		fM27AMagnetWidth = 392.6 * CLHEP::mm;
		fM27AMagnetHeight = 196. * CLHEP::mm;
		fM27AMagnetLength = 683. * CLHEP::mm;
		fM27AMagnetPoleWidth = 114. * CLHEP::mm;
		fM27AMagnetPoleHeight = 53. * CLHEP::mm;
	
		fM27AMagnetCoilWidth = 264. * CLHEP::mm; //overall
		fM27AMagnetCoilHeight = 38.1 * CLHEP::mm;
		fM27AMagnetCoilThickness = 74.3 * CLHEP::mm; //single donut width
		fM27AMagnetCoilLength = fM27AMagnetLength + 2. * fM27AMagnetCoilThickness;
		
		//M34 Magnet
		fM34MagnetRadius = 1600 *CLHEP::mm;
		fM34MagnetInnerRadius = fM34MagnetRadius - 310 * CLHEP::mm;
        fM34MagnetOuterRadius = fM34MagnetRadius + 310 * CLHEP::mm;
        fM34MagnetHeight = 452 * CLHEP::mm;
        fM34MagnetThetaStart = -3.14159 * CLHEP::rad + fThetaElectron + (112./fM34MagnetRadius)*CLHEP::rad;
        fM34MagnetThetaEnd = 3.14159 * CLHEP::rad * 0.5 - fThetaElectron - (200./fM34MagnetRadius)*CLHEP::rad;
        
        fM34MagnetCoilHeight = 98 * CLHEP::mm;
		fM34MagnetCoilThickness = 106 * CLHEP::mm; //single donut width
		fM34MagnetCoilThetaStart = -3.14159 * CLHEP::rad + fThetaElectron;
        fM34MagnetCoilThetaEnd = 3.14159 * CLHEP::rad * 0.5 - fThetaElectron;
        fM34MagnetCoilHoleThetaStart = -3.14159 * CLHEP::rad + fThetaElectron + (110./fM34MagnetRadius)*CLHEP::rad;
        fM34MagnetCoilHoleThetaEnd = 3.14159 * CLHEP::rad * 0.5 - fThetaElectron - (195./fM34MagnetRadius)*CLHEP::rad;
		
	  // Detector SCREEN HE
   	   fTransparentDetectorWidth = 554. * CLHEP::cm; //edit to fit the smaller LE room (278cm on the right)
  	   fTransparentDetectorHeight = 500.  * CLHEP::cm; //edit to fit the room height
 	   fTransparentDetectorLength = 1. * CLHEP::cm;

		}
		else
		{ ///L.E. line TO BE DEFINED !!
		fM27ADistance = fConcreteA1Distance - fConcreteA1Length * 0.5 - 3683. * CLHEP::mm - fM27AGirderLength * 0.5;
		fM30Distance = fConcreteA1Distance + fConcreteA1Length * 0.5 + 164. * CLHEP::mm + fM30GirderLength * 0.5;
		fM31Distance = fConcreteA1Distance + fConcreteA1Length * 0.5 + 3311. * CLHEP::mm + fM31GirderLength * 0.5;
		
		// Detector SCREEN LE
   	  	fTransparentDetectorWidth = 554. * CLHEP::cm; //edit to fit the smaller LE room (278cm on the right)
  	  	fTransparentDetectorHeight = 500.  * CLHEP::cm; //edit to fit the room height
   	 	fTransparentDetectorLength = 1. * CLHEP::cm;
		}


    
    fPbDiskLength = 5. * CLHEP::cm;
    fPbDiskOuterRadius = 30. * CLHEP::cm;
    
    fPbDiskA0Distance = fBeamPipeA0Length - fPbDiskLength * 0.5 - 110. * CLHEP::cm;
    fPbDiskA1Distance = fBeamPipeA0Length - fPbDiskLength * 0.5;
    
    
    //Detector RACKS
    fTransparentRackWidth = 60. * CLHEP::cm;
    fTransparentRackLength = 80. * CLHEP::cm;
    fTransparentRackHeight = 200. * CLHEP::cm;
   
    if(bLine==1)
		{
		//HE line- definition of racks positions
		fRack1PositionX = 238.* CLHEP::cm + fTransparentRackLength * 0.5;
		fRack1PositionY = (fBeamHeigth - fTransparentRackHeight);
		fRack1PositionZ = fConcreteA0Distance + fWallThickness * 0.5 + 250. * CLHEP::cm + fTransparentRackWidth * 0.5; 

		fRack2PositionX = -315.* CLHEP::cm -fTransparentRackWidth * 0.5;
		fRack2PositionY = (fBeamHeigth - fTransparentRackHeight);
		fRack2PositionZ = fConcreteA0Distance + fWallThickness * 0.5 + 950. * CLHEP::cm + fTransparentRackLength * 0.5;
		}
		else	
		{
		//LE line-  definition of racks positions
		fRack1PositionX = -188.*CLHEP::cm - fTransparentRackLength * 0.5;
		fRack1PositionY = (fBeamHeigth - fTransparentRackHeight);
		fRack1PositionZ = fConcreteA0Distance + fWallThickness * 0.5 + 10. * CLHEP::cm + fTransparentRackWidth * 0.5; //10 cm from wall


		fRack2PositionX = -85.*CLHEP::cm -fTransparentRackWidth *0.5;
		fRack2PositionY = (fBeamHeigth - fTransparentRackHeight);
		fRack2PositionZ = 1518.5 * CLHEP::cm + fTransparentRackLength * 0.5;
		}
		
 	//Detector Hexapod
		
    fHexapodA1PositionX = 0. * CLHEP::cm;
    fHexapodA1PositionY = -fRomanPotWindowOuterRadius -50. * CLHEP::cm;   
    fHexapodA1PositionZ = fBeamPipeA0Length + (fRomanPotLength + 2.*fRomanPotWindowLength) * 0.5; 
       
    fHexapodA2PositionX = 0. * CLHEP::cm;
    fHexapodA2PositionY =-fRomanPotWindowOuterRadius -50. * CLHEP::cm -32.8 * CLHEP::cm;
    fHexapodA2PositionZ = fBeamPipeA0Length + (fRomanPotLength + 2.*fRomanPotWindowLength) * 0.5; 
    
    fHexapodB1PositionX = 0. * CLHEP::cm;
    fHexapodB1PositionY = -fRomanPotWindowOuterRadius -10. * CLHEP::cm;
    fHexapodB1PositionZ = fBeamPipeA0Length + fRomanPotLength + fRomanPotWindowLength; 
    
    fHexapodB2PositionX = 0. * CLHEP::cm;
    fHexapodB2PositionY = -fRomanPotWindowOuterRadius -10. * CLHEP::cm -32.8 * CLHEP::cm;
    fHexapodB2PositionZ = fBeamPipeA0Length + fRomanPotLength + fRomanPotWindowLength; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void G4ELIMED_DetectorConstruction::DefineMaterials(){
    G4double z = 7.;
    G4double a = 14.007*CLHEP::g/CLHEP::mole;
    G4double density = CLHEP::universe_mean_density;
    G4double pressure = 1.E-6 * 1.E-3 * CLHEP::bar;//10-6 millibar
    G4double temperature = 300.*CLHEP::kelvin;
    G4Material* Vacuum = new G4Material("Vacuum", z , a , density, kStateGas,temperature,pressure);
    
    G4Material* G4_Al = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");
    G4Material* G4_W = G4NistManager::Instance()->FindOrBuildMaterial("G4_W");
    G4Material* G4_Pb = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pb");
    G4Material* G4_Concrete = G4NistManager::Instance()->FindOrBuildMaterial("G4_CONCRETE");
    G4Material* G4_AIR = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
    G4Material* G4_Cu = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");


    // Definition of stainless steel (not in NIST) for pipes and sand for pedestals 
    G4Element* C  = G4NistManager::Instance()->FindOrBuildElement("C");
    G4Element* Si = G4NistManager::Instance()->FindOrBuildElement("Si");
    G4Element* Cr = G4NistManager::Instance()->FindOrBuildElement("Cr");
    G4Element* Mn = G4NistManager::Instance()->FindOrBuildElement("Mn");
    G4Element* Ni = G4NistManager::Instance()->FindOrBuildElement("Ni");
    G4Element* Fe = G4NistManager::Instance()->FindOrBuildElement("Fe");
    G4Element* H  = G4NistManager::Instance()->FindOrBuildElement("H");    
	G4Element* O  = G4NistManager::Instance()->FindOrBuildElement("O"); 
	G4Element* Na = G4NistManager::Instance()->FindOrBuildElement("Na"); 
	G4Element* K  = G4NistManager::Instance()->FindOrBuildElement("K"); 	
	G4Element* Ca = G4NistManager::Instance()->FindOrBuildElement("Ca"); 	
	G4Element* Al = G4NistManager::Instance()->FindOrBuildElement("Al"); 	
	
    G4double density_SS;
    G4int ncomponents_SS;
    G4double fractionmass;
    G4Material* StainlessSteel = new G4Material("StainlessSteel", density_SS= 8.06*CLHEP::g/CLHEP::cm3, ncomponents_SS=6);
    StainlessSteel->AddElement(C, fractionmass=0.001);
    StainlessSteel->AddElement(Si, fractionmass=0.007);
    StainlessSteel->AddElement(Cr, fractionmass=0.18);
    StainlessSteel->AddElement(Mn, fractionmass=0.01);
    StainlessSteel->AddElement(Fe, fractionmass=0.712);
    StainlessSteel->AddElement(Ni, fractionmass=0.09);
    
    
    // Sand composition and density fromCompendium of Material Composition Data for Radiation Transport Modeling, 
    // Homeland Security, Revision 1 -PIET-43741-TM-963 PNNL-15870 Rev. 1
    G4double density_Sand;
    G4int ncomponents_Sand;
    G4double fractionmass_Sand;
    G4Material* Sand = new G4Material("Sand", density_Sand= 1.700 * CLHEP::g/CLHEP::cm3, ncomponents_Sand = 9);
    Sand->AddElement(H, fractionmass_Sand=0.007833);
    Sand->AddElement(C, fractionmass_Sand=0.003360);
    Sand->AddElement(O, fractionmass_Sand=0.536153);
    Sand->AddElement(Al, fractionmass_Sand=0.034401);      
    Sand->AddElement(Na, fractionmass_Sand=0.01763);    
    Sand->AddElement(Si, fractionmass_Sand=0.365067); 
    Sand->AddElement(K, fractionmass_Sand=0.011622);
    Sand->AddElement(Ca, fractionmass_Sand=0.011212);
    Sand->AddElement(Fe, fractionmass_Sand=0.013289);
  
    
    fWorldMaterial = G4_AIR;
    
    //fBeamPipeMaterial = StainlessSteel; PAOLO EDIT pipe vacuum
    fBeamPipeMaterial = StainlessSteel;
    fConcreteMaterial = G4_Concrete;
    fCollimatorMaterial = G4_W;
    fCollimatorSupportMaterial = G4_Al;
    fPbDiskMaterial = G4_Pb;
    fBeamPipeVacuum = Vacuum;
       
    //Girders and Pedestals
    fGirderMaterial = G4_Al;
    fPedestalMaterial = StainlessSteel;
    fPedestalInsideMaterial = Sand;
    
    //Magnet
    fMagnetMaterial = StainlessSteel;
    fCoilMaterial = G4_Cu;
    
    }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* G4ELIMED_DetectorConstruction::Construct(){
    
    //World
    fWorldSolid = new G4Box("World",
                            fWorldSize.x()/2.,
                            fWorldSize.y()/2.,
                            fWorldSize.z()/2.);
    
    fWorldLogic = new G4LogicalVolume(fWorldSolid,
                                      fWorldMaterial,
                                      "World");
    fWorldLogic->SetVisAttributes(G4VisAttributes::Invisible);
    
    fWorldPhysical = new G4PVPlacement(0,
                                       G4ThreeVector(),
                                       fWorldLogic,
                                       "World",
                                       0,
                                       false,
                                       0);
    
    
    // Beam pipe
    if(bBeamPipe){
        G4VisAttributes* fBeamPipeVisAttribute = new G4VisAttributes();
        fBeamPipeVisAttribute->SetForceSolid(true);
        
        fBeamPipeA0Solid = new G4Tubs("BeamPipeA0",
                                              fBeamPipeA0InnerRadius,
                                              fBeamPipeA0OuterRadius,
                                              fBeamPipeA0Length * 0.5,
                                              0*CLHEP::deg,
                                              360*CLHEP::deg);
        
        fBeamPipeA0Logic = new G4LogicalVolume(fBeamPipeA0Solid,
                                               fBeamPipeMaterial,
                                               "BeamPipeA0");
        
        fBeamPipeA0Logic->SetVisAttributes(fBeamPipeVisAttribute);
        
        G4ThreeVector fBeamPipeA0PositionVector = G4ThreeVector(0.,0.,fBeamPipeA0Length * 0.5);
        
        fBeamPipeA0Physical = new G4PVPlacement(0,
                                                fBeamPipeA0PositionVector,
                                                fBeamPipeA0Logic,
                                                "BeamPipeA0",
                                                fWorldLogic,
                                                false,
                                                0);
        
        //inside pipe vac A0
         G4Tubs* fBeamPipeA0InsideSolid = new G4Tubs("BeamPipeA0Inside",
                                              0.,
                                              fBeamPipeA0InnerRadius,
                                              fBeamPipeA0Length * 0.5,
                                              0*CLHEP::deg,
                                              360*CLHEP::deg);
        
        G4LogicalVolume* fBeamPipeA0InsideLogic = new G4LogicalVolume(fBeamPipeA0InsideSolid,
                                               fBeamPipeVacuum,
                                               "BeamPipeA0Inside");
        
        fBeamPipeA0InsideLogic->SetVisAttributes(fBeamPipeVisAttribute);
        

		fBeamPipeA0InsidePhysical = new G4PVPlacement(0,
                                                	fBeamPipeA0PositionVector,
                                                	fBeamPipeA0InsideLogic,
                                               		"BeamPipeInsideA0",
                                                	fWorldLogic,
                                                	false,
                                               		0);
        
        fBeamPipeA2Solid = new G4Tubs("BeamPipeA2",
                                              fBeamPipeA0InnerRadius,
                                              fBeamPipeA0OuterRadius,
                                              fBeamPipeA2Length * 0.5,
                                              0*CLHEP::deg,
                                              360*CLHEP::deg);
        
        fBeamPipeA2Logic = new G4LogicalVolume(fBeamPipeA2Solid,
                                               fBeamPipeMaterial,
                                               "BeamPipeA2");
        
        fBeamPipeA2Logic->SetVisAttributes(fBeamPipeVisAttribute);
        
        G4ThreeVector fBeamPipeA2PositionVector = G4ThreeVector(0.,0.,fBeamPipeA0Length + (fRomanPotLength + 2.*fRomanPotWindowLength) + fBeamPipeA2Length * 0.5);
        
        fBeamPipeA2Physical = new G4PVPlacement(0,
                                                fBeamPipeA2PositionVector,
                                                fBeamPipeA2Logic,
                                                "BeamPipeA2",
                                                fWorldLogic,
                                                false,
                                                0);
       //inside vac A2 pipe
                                                
       G4Tubs* fBeamPipeA2InsideSolid = new G4Tubs("BeamPipeA2Inside",
                                              0.,
                                              fBeamPipeA0InnerRadius,
                                              fBeamPipeA2Length * 0.5,
                                              0*CLHEP::deg,
                                              360*CLHEP::deg);
        
        G4LogicalVolume* fBeamPipeA2InsideLogic = new G4LogicalVolume(fBeamPipeA2InsideSolid,
                                               fBeamPipeVacuum,
                                               "BeamPipeA2Inside");
        
        fBeamPipeA2InsideLogic->SetVisAttributes(fBeamPipeVisAttribute);
        
        
		
		fBeamPipeA2InsidePhysical = new G4PVPlacement(0,
                                                						fBeamPipeA2PositionVector,
                                               							 fBeamPipeA2InsideLogic,
                                                						"BeamPipeA2Inside",
                                               							 fWorldLogic,
                                               							 false,
                                               							 0);
        
    }
    
    
    // Roman pot
    if(bRomanPot){
        G4VisAttributes* fRomaPotVisAttribute = new G4VisAttributes();
        fRomaPotVisAttribute->SetForceSolid(false);
        
        G4Tubs* fRomanPotEnvelopeSolid = new G4Tubs("RomanPotEnvelope",
                                                  0.,
                                                  fRomanPotWindowOuterRadius,
                                                  (fRomanPotLength + 2.*fRomanPotWindowLength) * 0.5,
                                                  0*CLHEP::deg,
                                                  360*CLHEP::deg
                                                  );
        
        fRomanPotEnvelopeLogic = new G4LogicalVolume(fRomanPotEnvelopeSolid,
                                                     fBeamPipeVacuum,
                                                     "RomanPotEnvelope");
        
        fRomanPotEnvelopeLogic->SetVisAttributes(fRomaPotVisAttribute);

        G4Tubs* fRomanPotWindowSolid = new G4Tubs("RomanPotWindow",
                                                  fRomanPotWindowInnerRadius,
                                                  fRomanPotWindowOuterRadius,
                                                  fRomanPotWindowLength * 0.5,
                                                  0*CLHEP::deg,
                                                  360*CLHEP::deg);
        
        fRomanPotWindowLogic = new G4LogicalVolume(fRomanPotWindowSolid,
                                                   fBeamPipeMaterial,
                                                   "RomanPotWindow");
        
        fRomanPotWindowLogic->SetVisAttributes(fRomaPotVisAttribute);
        
        G4ThreeVector fRomanPotWindow0PositionVector = G4ThreeVector(0.,0.,-(fRomanPotLength + fRomanPotWindowLength) * 0.5);
        G4ThreeVector fRomanPotWindow1PositionVector = G4ThreeVector(0.,0.,+(fRomanPotLength + fRomanPotWindowLength) * 0.5);
        

        fRomanPotWindow0Physical = new G4PVPlacement(0,
                                                     fRomanPotWindow0PositionVector,
                                                     fRomanPotWindowLogic,
                                                     "RomanPotWindow0",
                                                     fRomanPotEnvelopeLogic,
                                                     false,
                                                     0);
        
        fRomanPotWindow1Physical = new G4PVPlacement(0,
                                                     fRomanPotWindow1PositionVector,
                                                     fRomanPotWindowLogic,
                                                     "RomanPotWindow1",
                                                     fRomanPotEnvelopeLogic,
                                                     false,
                                                     0);
        
        G4Tubs* fRomanPotSolid = new G4Tubs("RomanPot",
                                            fRomanPotInnerRadius,
                                            fRomanPotOuterRadius,
                                            fRomanPotLength * 0.5,
                                            0*CLHEP::deg,
                                            360*CLHEP::deg);
        
        fRomanPotLogic = new G4LogicalVolume(fRomanPotSolid,
                                             fBeamPipeMaterial,
                                             "RomanPot");
        
        fRomanPotLogic->SetVisAttributes(fRomaPotVisAttribute);
        
        
        G4ThreeVector fRomanPotPositionVector = G4ThreeVector(0.,0.,0.);


        fRomanPotPhysical = new G4PVPlacement(0,
                                              fRomanPotPositionVector,
                                              fRomanPotLogic,
                                              "RomanPot",
                                              fRomanPotEnvelopeLogic,
                                              false,
                                              0);
    }
    // Concrete
    
    if(bConcrete){
    
       G4VisAttributes* fConcreteVisAttribute;
        fConcreteVisAttribute = new G4VisAttributes(G4Colour(0.0,1.0,0.0));
        fConcreteVisAttribute->SetForceSolid(false);
    
        
	//-------------------------------------------A0 WALL with hole for pipe ---------------------------------------//

	//A0B0 first wall after IP no hole
        G4Box* fConcreteA0B0Solid = new G4Box("ConcreteA0B0",
                                              (fRoomWidth +fWallThickness + fWallThickness2) * 0.5,
                                              fWallHeigth * 0.5,
                                              fWallThickness * 0.5);
	//A0B0 first wall hole
        G4Tubs* fConcreteA0B1Solid = new G4Tubs("ConcreteA0B1",
                                                0.,
                                                fConcreteA0RadiusPipe,
                                                fWallThickness * 0.6,
                                                0*CLHEP::deg,
                                                360*CLHEP::deg);
	//A0Solid first wall with hole for pipe
        
        G4SubtractionSolid* fConcreteA0Solid = new G4SubtractionSolid("ConcreteA0", fConcreteA0B0Solid, fConcreteA0B1Solid,0,
        																G4ThreeVector(-(fRoomShiftX -(fWallThickness2 - fWallThickness) * 0.5 ),- fRoomShiftY,0.));
        
        
        fConcreteA0Logic = new G4LogicalVolume(fConcreteA0Solid,
                                               fConcreteMaterial,
                                               "ConcreteA0");
        
        fConcreteA0Logic->SetVisAttributes(fConcreteVisAttribute);
        
        G4ThreeVector fConcreteA0PositionVector = G4ThreeVector(fRoomShiftX -(fWallThickness2 - fWallThickness) * 0.5, //asimmetrical right wall thickness requires this additional shift
        														fRoomShiftY,
        														fConcreteA0Distance);
        
        fConcreteA0Physical = new G4PVPlacement(0,
                                                fConcreteA0PositionVector,
                                                fConcreteA0Logic,
                                                "fConcreteA0",
                                                fWorldLogic,
                                                false,
                                                0);


	//-------------------------------------------A1 Concrete SHIELDING BLOCK with hole for pipe ------------------------------------------------//


	//A1B0 concrete block for shield -no hole

        G4Box* fConcreteA1B0Solid = new G4Box("ConcreteA1B0",
                                              fConcreteA1Width * 0.5,
                                              fConcreteA1Height * 0.5,
                                              fConcreteA1Length * 0.5);

	//A1B1 tube for shield hole
        G4Tubs* fConcreteA1B1Solid = new G4Tubs("ConcreteA1B1",
                                                0.,
                                                fConcreteA1RadiusPipe,
                                                fConcreteA1Length * 0.6,
                                                0*CLHEP::deg,
                                                360*CLHEP::deg);
	
	//A1Solid concrete block for shield with hole
        G4SubtractionSolid* fConcreteA1Solid = new G4SubtractionSolid("ConcreteA1", fConcreteA1B0Solid, fConcreteA1B1Solid,0, G4ThreeVector(0.,25.*CLHEP::cm,0.));
        
        
        fConcreteA1Logic = new G4LogicalVolume(fConcreteA1Solid,
                                               fConcreteMaterial,
                                               "ConcreteA1");
        
        fConcreteA1Logic->SetVisAttributes(fConcreteVisAttribute);
        
        G4ThreeVector fConcreteA1PositionVector = G4ThreeVector(0.,-25.*CLHEP::cm,fConcreteA1Distance);
        
        fConcreteA1Physical = new G4PVPlacement(0,
                                                fConcreteA1PositionVector,
                                                fConcreteA1Logic,
                                                "fConcreteA1",
                                                fWorldLogic,
                                                false,
                                                0);
    

	//-------------------------------------------FLOOR  --------------------------------------------------//

        G4Box* fConcreteFloorSolid = new G4Box("ConcreteFloor",
                                              fRoomWidth* 0.5,
                                              fFloorThickness * 0.5,
                                              fRoomLength * 0.5);


        
        fConcreteFloorLogic = new G4LogicalVolume(fConcreteFloorSolid,
                                               fConcreteMaterial,
                                               "ConcreteFloor");
        
        fConcreteFloorLogic->SetVisAttributes(fConcreteVisAttribute);
        
        G4ThreeVector fConcreteFloorPositionVector = G4ThreeVector(fRoomShiftX,
        														   -(fBeamHeigth + fFloorThickness * 0.5), 
																   fConcreteA0Distance + fWallThickness* 0.5 +fRoomLength * 0.5);
        
        fConcreteFloorPhysical = new G4PVPlacement(0,
                                                fConcreteFloorPositionVector,
                                                fConcreteFloorLogic,
                                                "fConcreteFloor",
                                                fWorldLogic,
                                                false,
                                                0);
    
    
	//------------------------------------------- CEILING  -------------------------------------------//

        G4Box* fConcreteTopSolid = new G4Box("ConcreteTop",
                                              fRoomWidth* 0.5,
                                              fTopThickness * 0.5,
                                              fRoomLength * 0.5);


        
        fConcreteTopLogic = new G4LogicalVolume(fConcreteTopSolid,
                                               fConcreteMaterial,
                                               "ConcreteTop");
        
        fConcreteTopLogic->SetVisAttributes(fConcreteVisAttribute);
        
        G4ThreeVector fConcreteTopPositionVector = G4ThreeVector(fRoomShiftX,
        														 fRoomHeigth - fBeamHeigth + fTopThickness * 0.5, 
																 fConcreteA0Distance + fWallThickness* 0.5 +fRoomLength * 0.5);
        
        fConcreteTopPhysical = new G4PVPlacement(0,
                                                fConcreteTopPositionVector,
                                                fConcreteTopLogic,
                                                "fConcreteTop",
                                                fWorldLogic,
                                                false,
                                                0);
  
                                                
	//----------------------------------- RIGHT WALL (considering beam propagation direction (opposite to e- beam dumps) ---------------------------//

        G4Box* fConcreteRightWallSolid = new G4Box("ConcreteRightWall",
                                              fWallThickness2* 0.5,
                                              fWallHeigth * 0.5,
                                              fRoomLength * 0.5);


        
        fConcreteRightWallLogic = new G4LogicalVolume(fConcreteRightWallSolid,
                                               fConcreteMaterial,
                                               "ConcreteRightWall");
        
        fConcreteRightWallLogic->SetVisAttributes(fConcreteVisAttribute);
        
        G4ThreeVector fConcreteRightWallPositionVector = G4ThreeVector(fRoomShiftX - fRoomWidth * 0.5 -fWallThickness2 * 0.5,
        														 	   fRoomShiftY, 
																	   fConcreteA0Distance + fWallThickness* 0.5 +fRoomLength * 0.5);
        
        fConcreteRightWallPhysical = new G4PVPlacement(0,
                                                fConcreteRightWallPositionVector,
                                                fConcreteRightWallLogic,
                                                "fConcreteRightWall",
                                                fWorldLogic,
                                                false,
                                                0);
    
                                                
	//------------------------------ LEFT WALL (considering beam propagation direction (e- beam dumps side)) ----------------------------//

        G4Box* fConcreteLeftWallSolid = new G4Box("ConcreteLeftWall",
                                              fWallThickness * 0.5,
                                              fWallHeigth * 0.5,
                                              fRoomLength * 0.5);


        
        fConcreteLeftWallLogic = new G4LogicalVolume(fConcreteLeftWallSolid,
                                               fConcreteMaterial,
                                               "ConcreteLeftWall");
        
        fConcreteLeftWallLogic->SetVisAttributes(fConcreteVisAttribute);
        
        G4ThreeVector fConcreteLeftWallPositionVector = G4ThreeVector(fRoomWidth * 0.5 + fRoomShiftX + fWallThickness *0.5,
        														 	  fRoomShiftY, 
																	  fConcreteA0Distance + fWallThickness* 0.5 +fRoomLength * 0.5);
        
        fConcreteLeftWallPhysical = new G4PVPlacement(0,
                                                fConcreteLeftWallPositionVector,
                                                fConcreteLeftWallLogic,
                                                "fConcreteLeftWall",
                                                fWorldLogic,
                                                false,
                                                0);


	//------------------------------- A2 WALL (last wall considering z-axis beam propagation (to experimental rooms)) -----------------------------------------//

        /*G4Box* fConcreteA2Solid = new G4Box("ConcreteA2",
                                              (fRoomWidth +fWallThickness + fWallThickness2) * 0.5,
                                              fWallHeigth * 0.5,
                                              fWallThickness * 0.5);


        
        fConcreteA2Logic = new G4LogicalVolume(fConcreteA2Solid,
                                               fConcreteMaterial,
                                               "ConcreteA2");
        
	fConcreteA2Logic->SetVisAttributes(fConcreteVisAttribute);*/
        
        G4ThreeVector fConcreteA2PositionVector = G4ThreeVector(fRoomShiftX -(fWallThickness2 - fWallThickness) * 0.5, //asimmetrical right wall thickness requires this additional shift
        														fRoomShiftY,
        														fConcreteA0Distance + fWallThickness * 0.5 + fRoomLength + fWallThickness * 0.5);
        
        fConcreteA2Physical = new G4PVPlacement(0,
                                                fConcreteA2PositionVector,
                                                fConcreteA0Logic,//EDIT A2 replaced with A0to make hole in last wall
                                                "fConcreteA0",//EDIT A2 replaced with A0  to make hole inlast wall
                                                fWorldLogic,
                                                false,
                                                0);
    }
    
    
    // Collimator support
    if(bCollimatorSupport){
        G4VisAttributes* fCollimatorSupportVisAttribute;
        fCollimatorSupportVisAttribute = new G4VisAttributes();
        fCollimatorSupportVisAttribute->SetForceSolid(false);
        
        
        G4Box* fCollimatorSupportA0B0Solid = new G4Box("CollimatorSupportA0B0",
                                                       fCollimatorSupportA0B0Width * 0.5,
                                                       fCollimatorSupportA0B0Height * 0.5,
                                                       (fCollimatorLength + fCollimatorSupportA1B0Length * 2.) * 0.5);
        
        G4Box* fCollimatorSupportA0B1Solid = new G4Box("CollimatorSupportA0B1",
                                                       fCollimatorSupportA0B1Width * 0.5,
                                                       fCollimatorHeight * 0.5,
                                                       fCollimatorLength * 0.5);
        
        G4Box* fCollimatorSupportA0B2Solid = new G4Box("CollimatorSupportA0B2",
                                                       fCollimatorSupportA1B1Width * 0.5,
                                                       fCollimatorHeight * 0.5,
                                                       fCollimatorSupportA1B0Length * 1.);
        
        
        
        
        G4SubtractionSolid* fCollimatorSupportA0Solid = new G4SubtractionSolid("CollimatorSupportA0", 
        																		fCollimatorSupportA0B0Solid, 
        																		fCollimatorSupportA0B1Solid,
        																		0,
        																		G4ThreeVector(0.,fCollimatorSupportA0B1Distance,0.));
        
        G4SubtractionSolid* fCollimatorSupportA1Solid = new G4SubtractionSolid("CollimatorSupportA1", 
        																		fCollimatorSupportA0Solid,
        																		fCollimatorSupportA0B2Solid,
        																		0,
        																		G4ThreeVector(0.,
        																					  fCollimatorSupportA0B1Distance,
        																					  +(2.*fCollimatorSupportA1B0Length+fCollimatorLength)*0.5));
        
        G4SubtractionSolid* fCollimatorSupportSolid = new G4SubtractionSolid("CollimatorSupport", 
        																	  fCollimatorSupportA1Solid, 
        																	  fCollimatorSupportA0B2Solid,
        																	  0,
        																	  G4ThreeVector(0.,
        																	  				fCollimatorSupportA0B1Distance,
        																	  				-(2.*fCollimatorSupportA1B0Length+fCollimatorLength)*0.5));
        
        fCollimatorSupportLogic = new G4LogicalVolume(fCollimatorSupportSolid,
                                                      fCollimatorSupportMaterial,
                                                      "CollimatorSupport");
        
        fCollimatorSupportLogic->SetVisAttributes(fCollimatorSupportVisAttribute);
    }
    
    
    // Collimator

        G4VisAttributes* fCollimatorVisAttribute;
        fCollimatorVisAttribute = new G4VisAttributes(G4Colour(0., 0., 1.));
        fCollimatorVisAttribute->SetForceSolid(true);
        
        G4Box* fCollimatorSolid = new G4Box("Collimator",
                                            fCollimatorWidth * 0.5,
                                            fCollimatorHeight * 0.5,
                                            fCollimatorLength * 0.5);
        fCollimatorLogicL = new G4LogicalVolume(fCollimatorSolid,
                                               fCollimatorMaterial,
                                               "CollimatorL");
        
        fCollimatorLogicL->SetVisAttributes(fCollimatorVisAttribute);

        fCollimatorLogicR = new G4LogicalVolume(fCollimatorSolid,
                                               fCollimatorMaterial,
                                               "CollimatorR");
        
        fCollimatorLogicR->SetVisAttributes(fCollimatorVisAttribute);
        
        G4Box* fCollimatorEnvelopeSolid = new G4Box("CollimatorEnvelopeSolid",
                                                    fCollimatorSupportA0B0Width * 0.5,
                                                    fCollimatorSupportA0B0Height * 0.5,
                                                    (fCollimatorLength + fCollimatorSupportA1B0Length * 2.) * 0.5);

    
    G4double fRomanPotCollimatorEnvelopeWidth = 0.5 * sqrt(fCollimatorSupportA0B0Width * fCollimatorSupportA0B0Width + fCollimatorSupportA0B0Height * fCollimatorSupportA0B0Height);
    G4double fRomanPotCollimatorEnvelopeLength = (fCollimatorLength + fCollimatorSupportA1B0Length * 2.) * 0.5 * fCollimatorNumber;
    
    G4Box* fRomanPotCollimatorEnvelopeSolid = new G4Box("fRomanPotCollimatorEnvelopeSolid",
                                                        fRomanPotCollimatorEnvelopeWidth,
                                                        fRomanPotCollimatorEnvelopeWidth,
                                                        fRomanPotCollimatorEnvelopeLength);
    
    G4LogicalVolume* fRomanPotCollimatorEnvelopeLogic = new G4LogicalVolume(fRomanPotCollimatorEnvelopeSolid,
                                                                            fBeamPipeVacuum,
                                                                            "RomanPotCollimatorEnvelope");


    for(int i1=0.;i1<fCollimatorNumber;i1++){
        

// 2014/11/18 ebagli
    if(bCollimator || bCollimatorSupport){
        fCollimatorEnvelopeLogic[i1] = new G4LogicalVolume(fCollimatorEnvelopeSolid,
                                                       fBeamPipeVacuum,
                                                       "CollimatorEnvelope");
        fCollimatorEnvelopeLogic[i1]->SetVisAttributes(G4VisAttributes::GetInvisible());
    }
    
    if(bCollimatorSupport){
        fCollimatorSupportA0Physical = new G4PVPlacement(0,
                                                         G4ThreeVector(0.,0.,0.),
                                                         fCollimatorSupportLogic,
                                                         "CollimatorSupport",
                                                         fCollimatorEnvelopeLogic[i1],
                                                         false,
                                                         0);
    }
    if(bCollimator)
    	{
        G4double vRelativeAperture = (fCollimatorAperture+fCollimatorWidth)*0.5;
        
// 2014/11/18 ebagli - Added relative random misplacement of the collimators
			G4double vDisplacement1 = fCollDisplMean[i1];
			G4double vDisplacement2 = fCollDisplMean[i1];
			if(bCollimatorRelativeRandomDisplacement==1)
				{ // UNIFORM DISTRIBUTION
					vDisplacement1 = fCollDisplMean[i1] + 2.*(G4UniformRand()-0.5)*fCollDisplSigma[i1];
					vDisplacement2 = fCollDisplMean[i1] + 2.*(G4UniformRand()-0.5)*fCollDisplSigma[i1];
				}
		
			if(bCollimatorRelativeRandomDisplacement==2)
				{ // GAUSSIAN DISTRIBUTION
					vDisplacement1 = G4RandGauss::shoot(fCollDisplMean[i1], fCollDisplSigma[i1]);
					vDisplacement2 = G4RandGauss::shoot(fCollDisplMean[i1], fCollDisplSigma[i1]);
				}

            G4cout << "Collimator " << i1 << G4endl;
            G4cout << "Displacements [mm] = (L) " << vDisplacement1/CLHEP::mm << " (R) " << vDisplacement2/CLHEP::mm << G4endl;

        G4ThreeVector fCollimatorA1PositionVector = G4ThreeVector(+(vRelativeAperture+vDisplacement1),fCollimatorSupportA0B1Distance,0.);
        
        G4ThreeVector fCollimatorA0PositionVector = G4ThreeVector(-(vRelativeAperture+vDisplacement2),fCollimatorSupportA0B1Distance,0.);
        
            G4cout << "Center Positions [mm] = (L) " << fCollimatorA0PositionVector.x()/CLHEP::mm << " (R) " << fCollimatorA1PositionVector.x()/CLHEP::mm  << G4endl;


        fCollimatorA0Physical = new G4PVPlacement(0,
                                                  fCollimatorA0PositionVector,
                                                  fCollimatorLogicL,
                                                  "CollimatorL",
                                                  fCollimatorEnvelopeLogic[i1],
                                                  false,
                                                  0);
        
        fCollimatorA1Physical = new G4PVPlacement(0,
                                                  fCollimatorA1PositionVector,
                                                  fCollimatorLogicR,
                                                  "CollimatorR",
                                                  fCollimatorEnvelopeLogic[i1],
                                                  false,
                                                  0);
    	}
//


        G4double vIndex = double(i1);

        if(fmod(fCollimatorNumber,2)==0.) {
            vIndex += 0.5;
        }
        
        vIndex -= int(fCollimatorNumber/2.);
        
        G4double vAngle = double(i1)/double(fCollimatorNumber);

        if(bCollimatorAngleManual == true){
        	vAngle = fCollDisplAngle[i1];
        }
        else{
        	vAngle = double(i1)/double(fCollimatorNumber);
        }

        G4double vRelativeDistance = vIndex*(fCollimatorDistance+fCollimatorLength+fCollimatorSupportA1B0Length*2.);
        
        G4ThreeVector fCollimatorSupportA0PositionVector = G4ThreeVector(0.,0.,vRelativeDistance);
        
        G4RotationMatrix* fCollimatorRotationMatrix = new G4RotationMatrix(2.*M_PI*vAngle,0.,0.);

        if(bCollimator || bCollimatorSupport){
            fCollimatorEnvelopePhysical = new G4PVPlacement(fCollimatorRotationMatrix,
                                                            fCollimatorSupportA0PositionVector,
                                                            fCollimatorEnvelopeLogic[i1],
                                                            "CollimatorEnvelope",
                                                            fRomanPotCollimatorEnvelopeLogic,
                                                            false,
                                                            0);
        }
        
    }

    G4RotationMatrix* fRomanPotCollimatorEnvelopeRotationMatrix = new G4RotationMatrix(0.,0.,0.);

    fRomanPotCollimatorEnvelopeRotationMatrix->rotateX(fRomanPotSupportAngle.x());
    fRomanPotCollimatorEnvelopeRotationMatrix->rotateY(fRomanPotSupportAngle.y());
    fRomanPotCollimatorEnvelopeRotationMatrix->rotateZ(fRomanPotSupportAngle.z());
    

	fRomanPotCollimatorEnvelopePhysical = new G4PVPlacement(fRomanPotCollimatorEnvelopeRotationMatrix,
                                                                               fRomanPotSupportPosition,
                                                                               fRomanPotCollimatorEnvelopeLogic,
                                                                               "RomanPotCollimatorEnvelope",
                                                                               fRomanPotEnvelopeLogic,
                                                                               false,
                                                                               0);

    
    // Roman pot
    if(bRomanPot)
    	{        
        G4VisAttributes* fRomanPotEnvelopeVisAttribute = new G4VisAttributes();
        fRomanPotEnvelopeVisAttribute->SetForceSolid(false);
        
        G4ThreeVector fRomanPotEnvelopePositionVector = G4ThreeVector(0.,0.,fBeamPipeA0Length + (fRomanPotLength + 2.*fRomanPotWindowLength) * 0.5);

        fRomanPotEnvelopePhysical = new G4PVPlacement(0,
                                                      fRomanPotEnvelopePositionVector,
                                                      fRomanPotEnvelopeLogic,
                                                      "RomanPotEnvelope",
                                                      fWorldLogic,
                                                      false,
                                                      0);
        
        fRomanPotEnvelopeLogic->SetVisAttributes(fRomanPotEnvelopeVisAttribute);
  	    }
    
     
    // Girders and Pedestals
    G4VisAttributes* fGirderAttribute; 
    fGirderAttribute = new G4VisAttributes(G4Colour(0.0,1.0,1.0));
    fGirderAttribute->SetForceSolid(true);
    
    //Magnet
    G4VisAttributes* fMagnetAttribute; 
    fMagnetAttribute = new G4VisAttributes(G4Colour(0.15,0.1,0.78));
    fMagnetAttribute->SetForceSolid(true);

    G4VisAttributes* fMagnetCoilAttribute; 
    fMagnetCoilAttribute = new G4VisAttributes(G4Colour(0.78,0.1,0.03));
    fMagnetCoilAttribute->SetForceSolid(true);   
    
    
    // Girders joint Logic Definition    
    G4Box* fGirderJointA0Solid = new G4Box("GirderJointA0",
                                              fGirderJointLength * 0.5,
                                              fGirderHeight * 0.5,
                                              fGirderWidth * 0.5);
    
    G4Box* fGirderJointA1Solid = new G4Box("GirderJointA1",
                                              fGirderJointLength * 0.6,
                                              fGirderHeight * 0.5 - fGirderThickness,
                                              fGirderWidth * 0.5 - fGirderThickness);
    
    G4SubtractionSolid* fGirderJointSolid = new G4SubtractionSolid("GirderJoint", fGirderJointA0Solid, fGirderJointA1Solid);
    
    fGirderJointLogic = new G4LogicalVolume(fGirderJointSolid,
                                               fGirderMaterial,
                                               "GirderJoint");
        
    fGirderJointLogic->SetVisAttributes(fGirderAttribute);
        
    G4ThreeVector fGirderJointPositionVector = G4ThreeVector(0.,0.,fConcreteA1Distance);
    
    // Pedestals Logic Definition 
    G4Box* fPedestalA0Solid = new G4Box("PedestalA0",
                                              fPedestalWidth * 0.5,
                                              fPedestalHeight * 0.5,
                                              fPedestalLength * 0.5);
    
    G4Box* fPedestalA1Solid = new G4Box("PedestalA1",
                                               fPedestalWidth * 0.5 - fPedestalThickness,
                                               fPedestalHeight * 0.6,
                                               fPedestalLength * 0.5 - fPedestalThickness);
    
    G4SubtractionSolid* fPedestalSolid = new G4SubtractionSolid("Pedestal", fPedestalA0Solid, fPedestalA1Solid);
    
    fPedestalLogic = new G4LogicalVolume(fPedestalSolid,
                                               fPedestalMaterial,
                                               "Pedestal");
        
    fPedestalLogic->SetVisAttributes(fGirderAttribute);
      
    G4Box* fPedestalInsideSolid = new G4Box("PedestalInside",
                                               fPedestalWidth * 0.5 - fPedestalThickness,
                                               fPedestalHeight * 0.5,
                                               fPedestalLength * 0.5 - fPedestalThickness);
    
    fPedestalInsideLogic = new G4LogicalVolume(fPedestalInsideSolid,
                                               fPedestalInsideMaterial,
                                               "PedestalInside");
        
    fPedestalInsideLogic->SetVisAttributes(fGirderAttribute); 
     
    G4Box* fPedestalM30A0Solid = new G4Box("PedestalM30A0",
                                              fPedestalWidth * 0.5,
                                              fPedestalM30Height * 0.5,
                                              fPedestalLength * 0.5);
    
    G4Box* fPedestalM30A1Solid = new G4Box("PedestalM30A1",
                                               fPedestalWidth * 0.5 - fPedestalThickness,
                                               fPedestalM30Height * 0.6,
                                               fPedestalLength * 0.5 - fPedestalThickness);
    
    G4SubtractionSolid* fPedestalM30Solid = new G4SubtractionSolid("PedestalM30", fPedestalM30A0Solid, fPedestalM30A1Solid);
    
    fPedestalM30Logic = new G4LogicalVolume(fPedestalM30Solid,
                                               fPedestalMaterial,
                                               "PedestalM30");
        
    fPedestalM30Logic->SetVisAttributes(fGirderAttribute);
      
    G4Box* fPedestalM30InsideSolid = new G4Box("PedestalM30Inside",
                                               fPedestalWidth * 0.5 - fPedestalThickness,
                                               fPedestalM30Height * 0.5,
                                               fPedestalLength * 0.5 - fPedestalThickness);
    
    fPedestalM30InsideLogic = new G4LogicalVolume(fPedestalM30InsideSolid,
                                               fPedestalInsideMaterial,
                                               "PedestalM30Inside");
        
    fPedestalM30InsideLogic->SetVisAttributes(fGirderAttribute);  
    
    G4Box* fPedestalM31A0Solid = new G4Box("PedestalM31A0",
                                              fPedestalWidth * 0.5,
                                              fPedestalM31Height * 0.5,
                                              fPedestalLength * 0.5);
    
    G4Box* fPedestalM31A1Solid = new G4Box("PedestalM31A1",
                                               fPedestalWidth * 0.5 - fPedestalThickness,
                                               fPedestalM31Height * 0.6,
                                               fPedestalLength * 0.5 - fPedestalThickness);
    
    G4SubtractionSolid* fPedestalM31Solid = new G4SubtractionSolid("PedestalM31", fPedestalM31A0Solid, fPedestalM31A1Solid);
    
    fPedestalM31Logic = new G4LogicalVolume(fPedestalM31Solid,
                                               fPedestalMaterial,
                                               "PedestalM31");
        
    fPedestalM31Logic->SetVisAttributes(fGirderAttribute);
      
    G4Box* fPedestalM31InsideSolid = new G4Box("PedestalM31Inside",
                                               fPedestalWidth * 0.5 - fPedestalThickness,
                                               fPedestalM31Height * 0.5,
                                               fPedestalLength * 0.5 - fPedestalThickness);
    
    fPedestalM31InsideLogic = new G4LogicalVolume(fPedestalM31InsideSolid,
                                               fPedestalInsideMaterial,
                                               "PedestalM31Inside");
        
    fPedestalM31InsideLogic->SetVisAttributes(fGirderAttribute);  
    
        
   	
	//M30
	G4Box* fM30GirderA0Solid = new G4Box("M30GirderA0",
                                              fGirderWidth * 0.5,
                                              fGirderHeight * 0.5,
                                              fM30GirderLength * 0.5);
    
    G4Box* fM30GirderA1Solid = new G4Box("M30GirderA1",
                                              fGirderWidth * 0.5 - fGirderThickness,
                                              fGirderHeight * 0.5 - fGirderThickness,
                                              fM30GirderLength * 0.6);
    
    G4SubtractionSolid* fM30GirderSolid = new G4SubtractionSolid("M30Girder", fM30GirderA0Solid, fM30GirderA1Solid);
    
    fM30GirderLogic = new G4LogicalVolume(fM30GirderSolid,
                                               fGirderMaterial,
                                               "M30Girder");
        
    fM30GirderLogic->SetVisAttributes(fGirderAttribute);
    
    		 
    G4ThreeVector fM30LGirderPositionVector = G4ThreeVector(-fGirderJointLength * 0.5 - fGirderWidth * 0.5, fGirderM30Y,fM30Distance); //support are made of 2 parallel identical girders, this is Left
    G4ThreeVector fM30RGirderPositionVector = G4ThreeVector(+fGirderJointLength * 0.5 + fGirderWidth * 0.5, fGirderM30Y,fM30Distance); // this is right
    
    if (bModulesOn==true)
    {
    fM30LGirderPhysical = new G4PVPlacement(0,
                                            fM30LGirderPositionVector,
                                            fM30GirderLogic,
                                            "M30LGirder",
                                            fWorldLogic,
                                            false,
                                            0);    
    
    
    fM30RGirderPhysical = new G4PVPlacement(0,
                                            fM30RGirderPositionVector,
                                            fM30GirderLogic,
                                            "M30RGirder",
                                            fWorldLogic,
                                            false,
                                            0);
    
    G4ThreeVector fM30Joint1PositionVector = G4ThreeVector(0., fGirderM30Y,fM30Distance - fM30GirderLength * 0.5 + fGirderWidth * 0.5); 
    G4ThreeVector fM30Joint2PositionVector = G4ThreeVector(0., fGirderM30Y,fM30Distance + fM30GirderLength * 0.5 - fGirderWidth * 0.5);
    
    fM30Joint1Physical = new G4PVPlacement(0,
                                            fM30Joint1PositionVector,
                                            fGirderJointLogic,
                                            "M30Joint1",
                                            fWorldLogic,
                                            false,
                                            0);  
     
     fM30Joint2Physical = new G4PVPlacement(0,
                                            fM30Joint2PositionVector,
                                            fGirderJointLogic,
                                            "M30Joint2",
                                            fWorldLogic,
                                            false,
                                            0);
    //M30 Pedestals
    G4ThreeVector fM30Pedestal1PositionVector = G4ThreeVector(0., fPedestalM30Y,fM30Distance - fM30GirderLength * 0.5 + fPedestalLength * 0.5); 
    G4ThreeVector fM30Pedestal2PositionVector = G4ThreeVector(0., fPedestalM30Y,fM30Distance + fM30GirderLength * 0.5 - fPedestalLength * 0.5);
    
    fM30Pedestal1Physical = new G4PVPlacement(0,
                                            fM30Pedestal1PositionVector,
                                            fPedestalM30Logic,
                                            "M30Pedestal1",
                                            fWorldLogic,
                                            false,
                                            0);  
    
    fM30Pedestal1InsidePhysical = new G4PVPlacement(0,
                                            fM30Pedestal1PositionVector,
                                            fPedestalM30InsideLogic,
                                            "M30Pedestal1Inside",
                                            fWorldLogic,
                                            false,
                                            0);                                             
                                            
     
     fM30Pedestal2Physical = new G4PVPlacement(0,
                                            fM30Pedestal2PositionVector,
                                            fPedestalM30Logic,
                                            "M30Pedestal2",
                                            fWorldLogic,
                                            false,
                                            0); 
                                            
    fM30Pedestal2InsidePhysical = new G4PVPlacement(0,
                                            fM30Pedestal2PositionVector,
                                            fPedestalM30InsideLogic,
                                            "M30Pedestal2Inside",
                                            fWorldLogic,
                                            false,
                                            0);    
     }                                                                                   
     //M30 CPSEC chamber - Compton Spectrometer vacuum chamber
      
        G4Tubs* fCSPECSolid = new G4Tubs("CSPEC",
                                            fCSPECInnerRadius,
                                            fCSPECOuterRadius,
                                            fCSPECLength * 0.5,
                                            0*CLHEP::deg,
                                            360*CLHEP::deg);
        
        fCSPECLogic = new G4LogicalVolume(fCSPECSolid,
                                             fBeamPipeMaterial,
                                             "CSPEC");
       
        G4Box* fTransparentCSPECSolid = new G4Box("TransparentCSPEC",  //for CSPEC scoring ONLY!
                                              43.*CLHEP::cm,
                                              fCSPECOuterRadius + 10*CLHEP::cm,
                                              (fM31Distance - 0.5 * fM31GirderLength - (fConcreteA1Distance + 0.5 *fConcreteA1Length)) * 0.5 );   
        
        fTransparentCSPECLogic = new G4LogicalVolume(fTransparentCSPECSolid,
                                             fBeamPipeVacuum,
                                             "TransparentCSPEC");
                                                                                              
        fCSPECLogic->SetVisAttributes(fGirderAttribute);
        
        
        G4ThreeVector fCSPECPositionVector = G4ThreeVector(0.,0.,fM30Distance);
        G4ThreeVector fTransparentCSPECPositionVector = G4ThreeVector(0.,0.,
        											(fM31Distance -0.5 * fM31GirderLength - (fConcreteA1Distance + 0.5 *fConcreteA1Length)) * 0.5 +fConcreteA1Distance + 0.5 *fConcreteA1Length);
    
    if (bModulesOn==true)
	{
        fCSPECPhysical = new G4PVPlacement(0,
                                              fCSPECPositionVector,
                                              fCSPECLogic,
                                              "CSPEC",
                                              fWorldLogic,
                                              false,
                                              0);
         /*                                   													//for CSPEC scoting only!!
         fTransparentCSPECPhysical = new G4PVPlacement(0,
                                              fTransparentCSPECPositionVector,
                                              fTransparentCSPECLogic,
                                              "TransparentCSPEC",
                                              fWorldLogic,
                                              false,
                                              0);
         */
                                              
     }    
        G4Tubs* fCSPECtWindowSolid = new G4Tubs("fCSPECWindow",
                                                  fBeamPipeA0OuterRadius,
                                                  fCSPECOuterRadius,
                                                  fCSPECWindowLength* 0.5,
                                                  0*CLHEP::deg,
                                                  360*CLHEP::deg);
        
        fCSPECWindowLogic = new G4LogicalVolume(fCSPECtWindowSolid,
                                                   fBeamPipeMaterial,
                                                   "fCSPECWindow");
        
        fCSPECWindowLogic->SetVisAttributes(fGirderAttribute);
        
        G4ThreeVector fCSPECWindow0PositionVector = G4ThreeVector(0.,0.,fM30Distance - fCSPECLength * 0.5 - fCSPECWindowLength * 0.5);
        G4ThreeVector fCSPECWindow1PositionVector = G4ThreeVector(0.,0.,fM30Distance + fCSPECLength * 0.5 + fCSPECWindowLength * 0.5);
        
    if (bModulesOn==true)
    {
        fCSPECWindow0Physical = new G4PVPlacement(0,
                                                     fCSPECWindow0PositionVector,
                                                     fCSPECWindowLogic,
                                                     "fCSPECWindow0",
                                                     fWorldLogic,
                                                     false,
                                                     0);
        
        fCSPECWindow1Physical = new G4PVPlacement(0,
                                                     fCSPECWindow1PositionVector,
                                                     fCSPECWindowLogic,
                                                     "fCSPECWindow1",
                                                     fWorldLogic,
                                                     false,
                                                     0);
     
     }
     //M31
	G4Box* fM31GirderA0Solid = new G4Box("M31GirderA0",
                                              fGirderWidth * 0.5,
                                              fGirderHeight * 0.5,
                                              fM31GirderLength * 0.5);
    
    G4Box* fM31GirderA1Solid = new G4Box("M31GirderA1",
                                              fGirderWidth * 0.5 - fGirderThickness,
                                              fGirderHeight * 0.5 - fGirderThickness,
                                              fM31GirderLength * 0.6);
    
    G4SubtractionSolid* fM31GirderSolid = new G4SubtractionSolid("M31Girder", fM31GirderA0Solid, fM31GirderA1Solid);
    
    fM31GirderLogic = new G4LogicalVolume(fM31GirderSolid,
                                               fGirderMaterial,
                                               "M31Girder");
        
    fM31GirderLogic->SetVisAttributes(fGirderAttribute);
    
    		 
    G4ThreeVector fM31LGirderPositionVector = G4ThreeVector(-fGirderJointLength * 0.5 - fGirderWidth * 0.5, fGirderM31Y,fM31Distance); //support are made of 2 parallel identical girders, this is Left
    G4ThreeVector fM31RGirderPositionVector = G4ThreeVector(+fGirderJointLength * 0.5 + fGirderWidth * 0.5, fGirderM31Y,fM31Distance); // this is right
    
    if (bModulesOn==true)
    {
    fM31LGirderPhysical = new G4PVPlacement(0,
                                            fM31LGirderPositionVector,
                                            fM31GirderLogic,
                                            "M31LGirder",
                                            fWorldLogic,
                                            false,
                                            0);    
    
    
    fM31RGirderPhysical = new G4PVPlacement(0,
                                            fM31RGirderPositionVector,
                                            fM31GirderLogic,
                                            "M31RGirder",
                                            fWorldLogic,
                                            false,
                                            0);
    }
    G4ThreeVector fM31Joint1PositionVector = G4ThreeVector(0., fGirderM31Y,fM31Distance - fM31GirderLength * 0.5 + fGirderWidth * 0.5); 
    G4ThreeVector fM31Joint2PositionVector = G4ThreeVector(0., fGirderM31Y,fM31Distance + fM31GirderLength * 0.5 - fGirderWidth * 0.5);
    
    if (bModulesOn==true)
    {
    fM31Joint1Physical = new G4PVPlacement(0,
                                            fM31Joint1PositionVector,
                                            fGirderJointLogic,
                                            "M31Joint1",
                                            fWorldLogic,
                                            false,
                                            0);  
     
     fM31Joint2Physical = new G4PVPlacement(0,
                                            fM31Joint2PositionVector,
                                            fGirderJointLogic,
                                            "M31Joint2",
                                            fWorldLogic,
                                            false,
                                            0);
    }
    //M31 Pedestals
    G4ThreeVector fM31Pedestal1PositionVector = G4ThreeVector(0., fPedestalM31Y,fM31Distance - fM31GirderLength * 0.5 + fPedestalLength * 0.5); 
    G4ThreeVector fM31Pedestal2PositionVector = G4ThreeVector(0., fPedestalM31Y,fM31Distance + fM31GirderLength * 0.5 - fPedestalLength * 0.5);
    
    if (bModulesOn==true)
    {
    fM31Pedestal1Physical = new G4PVPlacement(0,
                                            fM31Pedestal1PositionVector,
                                            fPedestalM31Logic,
                                            "M31Pedestal1",
                                            fWorldLogic,
                                            false,
                                            0);  
                                            
    fM31Pedestal1InsidePhysical = new G4PVPlacement(0,
                                            fM31Pedestal1PositionVector,
                                            fPedestalM31InsideLogic,
                                            "M31PedestalInside1",
                                            fWorldLogic,
                                            false,
                                            0);                                            
     
     fM31Pedestal2Physical = new G4PVPlacement(0,
                                            fM31Pedestal2PositionVector,
                                            fPedestalM31Logic,
                                            "M31Pedestal2",
                                            fWorldLogic,
                                            false,
                                            0);
                                            
     fM31Pedestal2InsidePhysical = new G4PVPlacement(0,
                                            fM31Pedestal2PositionVector,
                                            fPedestalM31InsideLogic,
                                            "M31PedestalInside2",
                                            fWorldLogic,
                                            false,
                                            0);   
    }                                              
	if(bLine==1)
	{
     //M27A
	G4Box* fM27AGirderA0Solid = new G4Box("M27AGirderA0",
                                              fGirderWidth * 0.5,
                                              fGirderHeight * 0.5,
                                              fM27AGirderLength * 0.5);
    
    G4Box* fM27AGirderA1Solid = new G4Box("M27AGirderA1",
                                              fGirderWidth * 0.5 - fGirderThickness,
                                              fGirderHeight * 0.5 - fGirderThickness,
                                              fM27AGirderLength * 0.6);
    
    G4SubtractionSolid* fM27AGirderSolid = new G4SubtractionSolid("M27AGirder", fM27AGirderA0Solid, fM27AGirderA1Solid);
    
    fM27AGirderLogic = new G4LogicalVolume(fM27AGirderSolid,
                                               fGirderMaterial,
                                               "M27AGirder");
        
    fM27AGirderLogic->SetVisAttributes(fGirderAttribute);
    
    		 
    G4ThreeVector fM27ALGirderPositionVector = G4ThreeVector(-fGirderJointLength * 0.5 - fGirderWidth * 0.5, fGirderY,fM27ADistance); //support are made of 2 parallel identical girders, this is Left
    G4ThreeVector fM27ARGirderPositionVector = G4ThreeVector(+fGirderJointLength * 0.5 + fGirderWidth * 0.5, fGirderY,fM27ADistance); // this is right
    
    if (bModulesOn==true)
    {
    fM27ALGirderPhysical = new G4PVPlacement(0,
                                            fM27ALGirderPositionVector,
                                            fM27AGirderLogic,
                                            "M27ALGirder",
                                            fWorldLogic,
                                            false,
                                            0);    
    
    
    fM27ARGirderPhysical = new G4PVPlacement(0,
                                            fM27ARGirderPositionVector,
                                            fM27AGirderLogic,
                                            "M27ARGirder",
                                            fWorldLogic,
                                            false,
                                            0);
    }
    
    G4ThreeVector fM27AJoint1PositionVector = G4ThreeVector(0., fGirderY,fM27ADistance - fM27AGirderLength * 0.5 + fGirderWidth * 0.5); 
    G4ThreeVector fM27AJoint2PositionVector = G4ThreeVector(0., fGirderY,fM27ADistance + fM27AGirderLength * 0.5 - fGirderWidth * 0.5);
    
    if (bModulesOn==true)
    {
    fM27AJoint1Physical = new G4PVPlacement(0,
                                            fM27AJoint1PositionVector,
                                            fGirderJointLogic,
                                            "M27AJoint1",
                                            fWorldLogic,
                                            false,
                                            0);  
     
     fM27AJoint2Physical = new G4PVPlacement(0,
                                            fM27AJoint2PositionVector,
                                            fGirderJointLogic,
                                            "M27AJoint2",
                                            fWorldLogic,
                                            false,
                                            0);
     }
    //M27A Pedestals
    G4ThreeVector fM27APedestal1PositionVector = G4ThreeVector(0., fPedestalY,fM27ADistance - fM27AGirderLength * 0.5 + fPedestalLength * 0.5); 
    G4ThreeVector fM27APedestal2PositionVector = G4ThreeVector(0., fPedestalY,fM27ADistance + fM27AGirderLength * 0.5 - fPedestalLength * 0.5);
    
    if (bModulesOn==true)
    {
    fM27APedestal1Physical = new G4PVPlacement(0,
                                            fM27APedestal1PositionVector,
                                            fPedestalLogic,
                                            "M27APedestal1",
                                            fWorldLogic,
                                            false,
                                            0); 
     
     fM27APedestal1InsidePhysical = new G4PVPlacement(0,
                                            fM27APedestal1PositionVector,
                                            fPedestalInsideLogic,
                                            "M27APedestal1Inside",
                                            fWorldLogic,
                                            false,
                                            0);                                       
                                                  
     fM27APedestal2Physical = new G4PVPlacement(0,
                                            fM27APedestal2PositionVector,
                                            fPedestalLogic,
                                            "M27APedestal2",
                                            fWorldLogic,
                                            false,
                                            0);
                                            
     fM27APedestal2InsidePhysical = new G4PVPlacement(0,
                                            fM27APedestal2PositionVector,
                                            fPedestalInsideLogic,
                                            "M27APedestal2Inside",
                                            fWorldLogic,
                                            false,
                                            0); 
     }
                                            
    //M27 Magnet    
    G4Box* fM27AMagnetA0Solid = new G4Box("M27AMagnetA0",				//external box
                                  		 fM27AMagnetWidth * 0.5,
                                    	 fM27AMagnetHeight * 0.5,
                                		 fM27AMagnetLength * 0.5);
      
    G4Box* fM27AMagnetA1Solid = new G4Box("M27AMagnetA1",				//hole for pipe between poles 
                                  		 fM27AMagnetPoleWidth * 0.6,
                                    	 fBeamPipeA0OuterRadius,  //check when fixed the final value!
                                		 fM27AMagnetLength * 0.6);
                                		 
    G4Box* fM27AMagnetA2Solid = new G4Box("M27AMagnetA2",				//holes for Cu coils 
                                  		 (110. * CLHEP::mm) * 0.5,
                                    	 (136. * CLHEP::mm) * 0.5,
                                		 fM27AMagnetLength * 0.6);
    
    G4Box* fM27AMagnetBaseSolid = new G4Box("M27AMagnetBase",				//Base
                                  		 (532.6 * CLHEP::mm) * 0.5,
                                    	 (30. * CLHEP::mm) * 0.5,
                                		 fM27AMagnetLength * 0.5);
    
    G4SubtractionSolid* fM27AMagnetA0A1Solid = new G4SubtractionSolid("M27AMagnetA0A1", 
        																	  fM27AMagnetA0Solid, 
        																	  fM27AMagnetA1Solid,
        																	  0,
        																	  G4ThreeVector(0.,0.,0.));
   
    G4SubtractionSolid* fM27AMagnetA0A1A2Solid = new G4SubtractionSolid("M27AMagnetA0A1A2", 
        																	  fM27AMagnetA0A1Solid, 
        																	  fM27AMagnetA2Solid,
        																	  0,
        																	  G4ThreeVector(fM27AMagnetPoleWidth * 0.5 + (110. * CLHEP::mm) *0.5 ,0.,0.));
        																	     						
    
    G4SubtractionSolid* fM27AMagnetSolid = new G4SubtractionSolid("M27AMagnetSolid", 
        																	  fM27AMagnetA0A1A2Solid, 
        																	  fM27AMagnetA2Solid,
        																	  0,
        																	  G4ThreeVector(-fM27AMagnetPoleWidth * 0.5 - (110. * CLHEP::mm) * 0.5,0.,0.));
    
    fM27AMagnetLogic = new G4LogicalVolume(fM27AMagnetSolid,
                                               fMagnetMaterial,
                                               "M27AMagnet");
                                               
    fM27AMagnetBaseLogic = new G4LogicalVolume(fM27AMagnetBaseSolid,
                                               fMagnetMaterial,
                                               "M27AMagnetBase");
        
    fM27AMagnetLogic->SetVisAttributes(fMagnetAttribute);
    fM27AMagnetBaseLogic->SetVisAttributes(fMagnetAttribute);
    
    G4ThreeVector fM27AMagnetPositionVector = G4ThreeVector(0., 0.,fM27ADistance);
    G4ThreeVector fM27AMagnetBasePositionVector = G4ThreeVector(0., - fM27AMagnetHeight * 0.5 -(30. * CLHEP::mm) * 0.5,fM27ADistance);
    
    if (bModulesOn==true)
    {
    fM27AMagnetPhysical = new G4PVPlacement(0,
                                            fM27AMagnetPositionVector,
                                            fM27AMagnetLogic,
                                            "M27AMagnet",
                                            fWorldLogic,
                                            false,
                                            0);  
    
    fM27AMagnetBasePhysical = new G4PVPlacement(0,
                                            fM27AMagnetBasePositionVector,
                                            fM27AMagnetBaseLogic,
                                            "M27AMagnetBase",
                                            fWorldLogic,
                                            false,
                                            0);  
	}
   
   //M27A Magnet Coils
   G4Box* fM27AMagnetCoilA0Solid = new G4Box("M27AMagnetCoilA0",		//external box
                                  		 fM27AMagnetCoilWidth * 0.5,
                                    	 fM27AMagnetCoilHeight * 0.5,
                                		 fM27AMagnetCoilLength * 0.5);
      
    G4Box* fM27AMagnetCoilA1Solid = new G4Box("M27AMagnetCoilA1",				//Internal hole
                                  		 fM27AMagnetCoilWidth * 0.5 - fM27AMagnetCoilThickness,
                                    	 fM27AMagnetCoilHeight * 0.5,  //check when fixed the final value!
                                		 fM27AMagnetCoilLength * 0.5 - fM27AMagnetCoilThickness);
    
    G4SubtractionSolid* fM27AMagnetCoilSolid = new G4SubtractionSolid("M27AMagnetCoilSolid", 
        															  fM27AMagnetCoilA0Solid, 
        															  fM27AMagnetCoilA1Solid,
        															  0,
        															  G4ThreeVector(0.,0.,0.));    
    
    fM27AMagnetCoilLogic = new G4LogicalVolume(fM27AMagnetCoilSolid,
                                               fCoilMaterial,
                                               "M27AMagnetCoil");
        
    fM27AMagnetCoilLogic->SetVisAttributes(fMagnetCoilAttribute);
    
    G4ThreeVector fM27AMagnetCoilTopPositionVector = G4ThreeVector(0.,fBeamPipeA0OuterRadius + (fM27AMagnetHeight * 0.5 -fBeamPipeA0OuterRadius - 30. * CLHEP::mm)*0.5,fM27ADistance);
    G4ThreeVector fM27AMagnetCoilBottomPositionVector = G4ThreeVector(0.,-fBeamPipeA0OuterRadius - (fM27AMagnetHeight * 0.5 -fBeamPipeA0OuterRadius - 30. * CLHEP::mm)*0.5,fM27ADistance);
    
    if (bModulesOn==true)
    {    
    fM27AMagnetCoilTopPhysical = new G4PVPlacement(0,
                                            fM27AMagnetCoilTopPositionVector,
                                            fM27AMagnetCoilLogic,
                                            "M27AMagnetCoilTop",
                                            fWorldLogic,
                                            false,
                                            0);  
    fM27AMagnetCoilBottomPhysical = new G4PVPlacement(0,
                                            fM27AMagnetCoilBottomPositionVector,
                                            fM27AMagnetCoilLogic,
                                            "M27AMagnetCoilBottom",
                                            fWorldLogic,
                                            false,
                                            0);      
    }
    
    //M34
     	
    G4Box* fM34Solid = new G4Box("M34",
                                  fGirderWidth * 0.5 +fGirderJointLength,
                                  60. * CLHEP::cm,
                                  fM34GirderLength * 0.5);
    
    fM34Logic = new G4LogicalVolume(fM34Solid,				//M34Logic envelope for the rotation of the whole module (girder+joints+pedestals)
                                    fWorldMaterial,
                                    "M34");
    
	
	G4Box* fM34GirderA0Solid = new G4Box("M34GirderA0",
                                              fGirderWidth * 0.5,
                                              fGirderHeight * 0.5,
                                              fM34GirderLength * 0.5);
    
    G4Box* fM34GirderA1Solid = new G4Box("M34GirderA1",
                                              fGirderWidth * 0.5 - fGirderThickness,
                                              fGirderHeight * 0.5 - fGirderThickness,
                                              fM34GirderLength * 0.6);
    
    G4SubtractionSolid* fM34GirderSolid = new G4SubtractionSolid("M34Girder", fM34GirderA0Solid, fM34GirderA1Solid);
    
    fM34GirderLogic = new G4LogicalVolume(fM34GirderSolid,
                                               fGirderMaterial,
                                               "M34Girder");
        
    fM34GirderLogic->SetVisAttributes(fGirderAttribute);
    
    		 
    G4ThreeVector fM34LGirderPositionVector = G4ThreeVector(-fGirderJointLength * 0.5 - fGirderWidth * 0.5, fGirderY + 900. *CLHEP::mm,0.); //support are made of 2 parallel identical girders, this is Left
    G4ThreeVector fM34RGirderPositionVector = G4ThreeVector(+fGirderJointLength * 0.5 + fGirderWidth * 0.5, fGirderY + 900. *CLHEP::mm,0.); // this is right
    
    if (bModulesOn==true)
    {
    fM34LGirderPhysical = new G4PVPlacement(0,
                                            fM34LGirderPositionVector,
                                            fM34GirderLogic,
                                            "M34LGirder",
                                            fM34Logic,
                                            false,
                                            0);    
    
    
    fM34RGirderPhysical = new G4PVPlacement(0,
                                            fM34RGirderPositionVector,
                                            fM34GirderLogic,
                                            "M34RGirder",
                                            fM34Logic,
                                            false,
                                            0);
    }
    
    G4ThreeVector fM34Joint1PositionVector = G4ThreeVector(0., fGirderY + 900. *CLHEP::mm, - fM34GirderLength * 0.5 + fGirderWidth * 0.5); 
    G4ThreeVector fM34Joint2PositionVector = G4ThreeVector(0., fGirderY + 900. *CLHEP::mm, + fM34GirderLength * 0.5 - fGirderWidth * 0.5);
    
    if (bModulesOn==true)
    {
    fM34Joint1Physical = new G4PVPlacement(0,
                                           fM34Joint1PositionVector,
                                           fGirderJointLogic,
                                           "M34Joint1",
                                           fM34Logic,
                                           false,
                                           0);  
     
     fM34Joint2Physical = new G4PVPlacement(0,
                                            fM34Joint2PositionVector,
                                            fGirderJointLogic,
                                            "M34Joint2",
                                            fM34Logic,
                                            false,
                                            0);
  
    }
   
    //M34 Pedestals
    G4ThreeVector fM34Pedestal1PositionVector = G4ThreeVector(0., fPedestalY + 900. *CLHEP::mm,- fM34GirderLength * 0.5 + fPedestalLength * 0.5); 
    G4ThreeVector fM34Pedestal2PositionVector = G4ThreeVector(0., fPedestalY + 900. *CLHEP::mm,+ fM34GirderLength * 0.5 - fPedestalLength * 0.5);
    
    if (bModulesOn==true)
    {
    fM34Pedestal1Physical = new G4PVPlacement(0,
                                            fM34Pedestal1PositionVector,
                                            fPedestalLogic,
                                            "M34Pedestal1",
                                            fM34Logic,
                                            false,
                                            0);  
    
    fM34Pedestal1InsidePhysical = new G4PVPlacement(0,
                                            fM34Pedestal1PositionVector,
                                            fPedestalInsideLogic,
                                            "M34Pedestal1Inside",
                                            fM34Logic,
                                            false,
                                            0);                                            
     
     fM34Pedestal2Physical = new G4PVPlacement(0,
                                            fM34Pedestal2PositionVector,
                                            fPedestalLogic,
                                            "M34Pedestal2",
                                            fM34Logic,
                                            false,
                                            0); 
                                            
    fM34Pedestal2InsidePhysical = new G4PVPlacement(0,
                                            fM34Pedestal2PositionVector,
                                            fPedestalInsideLogic,
                                            "M34Pedestal2Inside",
                                            fM34Logic,
                                            false,
                                            0);  
     }
     
     //M34 Complete (girder+joints+pedestals)
     G4ThreeVector fM34PositionVector = G4ThreeVector(fM34X,- 900. *CLHEP::mm,fM34Distance); 
     
     G4RotationMatrix *fM34RotationMatrix = new G4RotationMatrix(0.,0.,0.);
     
    
     fM34RotationMatrix->rotateY(-fThetaM34);

     if (bModulesOn==true)
     {
     fM34Physical = new G4PVPlacement(fM34RotationMatrix,
                                      fM34PositionVector,
                                      fM34Logic,
                                      "M34",
                                      fWorldLogic,
                                      false,
                                      0); 
     }
     
    //M34 Dump Magnet 
    
    G4Tubs* fM34MagnetA0Solid = new G4Tubs("M34MagnetA0",		//external box
                                  		 fM34MagnetInnerRadius,
                                    	 fM34MagnetOuterRadius,
                                		 fM34MagnetHeight * 0.5,
                                		 fM34MagnetThetaStart,
                                		 fM34MagnetThetaEnd);

	G4Tubs* fM34MagnetA1Solid = new G4Tubs("M34MagnetA1",		//poles hole
                                  		 fM34MagnetInnerRadius + 80. * CLHEP::mm,
                                    	 fM34MagnetOuterRadius - 80. * CLHEP::mm,
                                		 25. * CLHEP::mm,
                                		 fM34MagnetThetaStart*1.02,
                                		 fM34MagnetThetaEnd*1.05);
                                		 
	G4Tubs* fM34MagnetA2Solid = new G4Tubs("M34MagnetA2",		//coils hole
                                  		 fM34MagnetRadius - 240. * CLHEP::mm,
                                    	 fM34MagnetRadius - 60. * CLHEP::mm,
                                		 (254. * 0.5) * CLHEP::mm,
                                		 fM34MagnetThetaStart*1.02,
                                		 fM34MagnetThetaEnd*1.05);                          		 
    
    G4Tubs* fM34MagnetA3Solid = new G4Tubs("M34MagnetA2",		//coils hole
                                  		 fM34MagnetRadius + 60. * CLHEP::mm,
                                    	 fM34MagnetRadius + 240. * CLHEP::mm,
                                		 (254. * 0.5) * CLHEP::mm,
                                		 fM34MagnetThetaStart*1.02,
                                		 fM34MagnetThetaEnd*1.05);       
        
    G4SubtractionSolid* fM34MagnetA0A1Solid = new G4SubtractionSolid("M34MagnetA0A1Solid", 
        															  fM34MagnetA0Solid, 
        															  fM34MagnetA1Solid,
        															  0,
        															  G4ThreeVector(0.,0.,0.));
                          		 
    G4SubtractionSolid* fM34MagnetA0A1A2Solid = new G4SubtractionSolid("M34MagnetA0A1A2Solid", 
   		   															  fM34MagnetA0A1Solid, 
        															  fM34MagnetA2Solid,
        															  0,
        															  G4ThreeVector(0.,0.,0.));    
    
    G4SubtractionSolid* fM34MagnetA0A1A2A3Solid = new G4SubtractionSolid("M34MagnetA0A1Solid", 
        															  fM34MagnetA0A1A2Solid, 
        															  fM34MagnetA3Solid,
        															  0,
        															  G4ThreeVector(0.,0.,0.));  
    fM34MagnetLogic = new G4LogicalVolume(fM34MagnetA0A1A2A3Solid,
                                               fMagnetMaterial,
                                               "M34AMagnet");
                                               
        
    fM34MagnetLogic->SetVisAttributes(fMagnetAttribute);
    
        G4ThreeVector fM34MagnetPositionVector = G4ThreeVector(fM33X+fM34MagnetRadius*cos(fThetaElectron)+(fM33GirderLength*0.5 + 500*CLHEP::mm)*sin(fThetaElectron),0.,fM33Distance+(fM33GirderLength*0.5 + 500 *CLHEP::mm)*cos(fThetaElectron) - fM34MagnetRadius * sin(fThetaElectron)); 
         
     
     G4RotationMatrix *fM34MagnetRotationMatrix = new G4RotationMatrix(0.,0.,0.);
         
     fM34MagnetRotationMatrix->rotateX(1.57079);
     
     if (bModulesOn==true)
     {
     fM34MagnetPhysical = new G4PVPlacement(fM34MagnetRotationMatrix,
                                      fM34MagnetPositionVector,
                                      fM34MagnetLogic,
                                      "M34Magnet",
                                      fWorldLogic,
                                      false,
                                      0); 
    }
    
    //M34 Dump Magnet Coils
    G4Tubs* fM34MagnetCoilA0Solid = new G4Tubs("M34MagnetCoilA0",		//external box
                                  		 fM34MagnetRadius - 190. * CLHEP::mm,
                                    	 fM34MagnetRadius + 190. * CLHEP::mm,
                                		 fM34MagnetCoilHeight * 0.5,
                                		 fM34MagnetCoilThetaStart,
                                		 fM34MagnetCoilThetaEnd);

	G4Tubs* fM34MagnetCoilA1Solid = new G4Tubs("M34MagnetCoilA1",		//hole
                                  		 fM34MagnetRadius - 88. * CLHEP::mm,
                                    	 fM34MagnetRadius + 88. * CLHEP::mm,
                                		 fM34MagnetCoilHeight * 0.6,
                                		 fM34MagnetCoilHoleThetaStart,
                                		 fM34MagnetCoilHoleThetaEnd);   
                                		 
    G4SubtractionSolid* fM34MagnetCoilSolid = new G4SubtractionSolid("M34MagnetACoilSolid", 
        															  fM34MagnetCoilA0Solid, 
        															  fM34MagnetCoilA1Solid,
        															  0,
        															  G4ThreeVector(0.,0.,0.));   
    
    fM34MagnetCoilLogic = new G4LogicalVolume(fM34MagnetCoilSolid,
                                               fCoilMaterial,
                                               "M34AMagnetCoil");
                                               
        
    fM34MagnetCoilLogic->SetVisAttributes(fMagnetCoilAttribute);     
     
                                                    
     G4ThreeVector fM34MagnetCoilTopPositionVector = G4ThreeVector(
     													fM33X+fM34MagnetRadius*cos(fThetaElectron) + (fM33GirderLength * 0.5 + 500*CLHEP::mm) * sin(fThetaElectron),
     													126.5 * CLHEP::mm - fM34MagnetCoilHeight * 0.5,
     													fM33Distance+ (fM33GirderLength*0.5 + 500 *CLHEP::mm) * cos(fThetaElectron) - fM34MagnetRadius * sin(fThetaElectron)); 

     G4ThreeVector fM34MagnetCoilBottomPositionVector = G4ThreeVector(
    													 fM33X + fM34MagnetRadius*cos(fThetaElectron) + (fM33GirderLength *0.5 + 500 *CLHEP::mm) * sin(fThetaElectron),
     													-126.5 * CLHEP::mm + fM34MagnetCoilHeight * 0.5,
     													fM33Distance + (fM33GirderLength *0.5 + 500 *CLHEP::mm) * cos(fThetaElectron) - fM34MagnetRadius * sin(fThetaElectron)
     													); 
         
     //G4RotationMatrix *fM34MagnetRotationMatrix = new G4RotationMatrix(0.,0.,0.);
         
     //fM34MagnetRotationMatrix->rotateX(1.57079);
    
     if (bModulesOn==true)
     {
     fM34MagnetCoilTopPhysical = new G4PVPlacement(fM34MagnetRotationMatrix,
                                      fM34MagnetCoilTopPositionVector,
                                      fM34MagnetCoilLogic,
                                      "M34MagnetCoilTop",
                                      fWorldLogic,
                                      false,
                                      0); 
     
     fM34MagnetCoilBottomPhysical = new G4PVPlacement(fM34MagnetRotationMatrix,
                                      fM34MagnetCoilBottomPositionVector,
                                      fM34MagnetCoilLogic,
                                      "M34MagnetCoilBottom",
                                      fWorldLogic,
                                      false,
                                      0); 
     }
      
    //M32
    G4Box* fM32Solid = new G4Box("M32",
                                  fGirderWidth * 0.5 +fGirderJointLength,
                                  60. * CLHEP::cm,
                                  fM32GirderLength * 0.5);
    
    fM32Logic = new G4LogicalVolume(fM32Solid,				//M32Logic envelope for the rotation of the whole module (girder+joints+pedestals)
                                    fWorldMaterial,
                                    "M32");
    
	
	G4Box* fM32GirderA0Solid = new G4Box("M32GirderA0",
                                              fGirderWidth * 0.5,
                                              fGirderHeight * 0.5,
                                              fM32GirderLength * 0.5);
    
    G4Box* fM32GirderA1Solid = new G4Box("M32GirderA1",
                                              fGirderWidth * 0.5 - fGirderThickness,
                                              fGirderHeight * 0.5 - fGirderThickness,
                                              fM32GirderLength * 0.6);
    
    G4SubtractionSolid* fM32GirderSolid = new G4SubtractionSolid("M32Girder", fM32GirderA0Solid, fM32GirderA1Solid);
    
    fM32GirderLogic = new G4LogicalVolume(fM32GirderSolid,
                                               fGirderMaterial,
                                               "M32Girder");
        
    fM32GirderLogic->SetVisAttributes(fGirderAttribute);
    
    		 
    G4ThreeVector fM32LGirderPositionVector = G4ThreeVector(-fGirderJointLength * 0.5 - fGirderWidth * 0.5, fGirderY + 900. *CLHEP::mm,0.); //support are made of 2 parallel identical girders, this is Left
    G4ThreeVector fM32RGirderPositionVector = G4ThreeVector(+fGirderJointLength * 0.5 + fGirderWidth * 0.5, fGirderY + 900. *CLHEP::mm,0.); // this is right
    
    if (bModulesOn==true)
    {
    fM32LGirderPhysical = new G4PVPlacement(0,
                                            fM32LGirderPositionVector,
                                            fM32GirderLogic,
                                            "M32LGirder",
                                            fM32Logic,
                                            false,
                                            0);    
    
    
    fM32RGirderPhysical = new G4PVPlacement(0,
                                            fM32RGirderPositionVector,
                                            fM32GirderLogic,
                                            "M32RGirder",
                                            fM32Logic,
                                            false,
                                            0);
    }
    G4ThreeVector fM32Joint1PositionVector = G4ThreeVector(0., fGirderY + 900. *CLHEP::mm,- fM32GirderLength * 0.5 + fGirderWidth * 0.5); 
    G4ThreeVector fM32Joint2PositionVector = G4ThreeVector(0., fGirderY + 900. *CLHEP::mm, + fM32GirderLength * 0.5 - fGirderWidth * 0.5);
    
    if (bModulesOn==true)
    {
    fM32Joint1Physical = new G4PVPlacement(0,
                                           fM32Joint1PositionVector,
                                           fGirderJointLogic,
                                           "M32Joint1",
                                           fM32Logic,
                                           false,
                                           0);  
     
     fM32Joint2Physical = new G4PVPlacement(0,
                                            fM32Joint2PositionVector,
                                            fGirderJointLogic,
                                            "M32Joint2",
                                            fM32Logic,
                                            false,
                                            0);
  
     }  
   
   
    //M32 Pedestals
    G4ThreeVector fM32Pedestal1PositionVector = G4ThreeVector(0., fPedestalY+ 900. *CLHEP::mm,- fM32GirderLength * 0.5 + fPedestalLength * 0.5); 
    G4ThreeVector fM32Pedestal2PositionVector = G4ThreeVector(0., fPedestalY+ 900. *CLHEP::mm,+ fM32GirderLength * 0.5 - fPedestalLength * 0.5);
    
    if (bModulesOn==true)
    {
    fM32Pedestal1Physical = new G4PVPlacement(0,
                                            fM32Pedestal1PositionVector,
                                            fPedestalLogic,
                                            "M32Pedestal1",
                                            fM32Logic,
                                            false,
                                            0);  
    
    fM32Pedestal1InsidePhysical = new G4PVPlacement(0,
                                            fM32Pedestal1PositionVector,
                                            fPedestalInsideLogic,
                                            "M32Pedestal1Inside",
                                            fM32Logic,
                                            false,
                                            0);                                            
     
     fM32Pedestal2Physical = new G4PVPlacement(0,
                                            fM32Pedestal2PositionVector,
                                            fPedestalLogic,
                                            "M32Pedestal2",
                                            fM32Logic,
                                            false,
                                            0); 
                                            
    fM32Pedestal2InsidePhysical = new G4PVPlacement(0,
                                            fM32Pedestal2PositionVector,
                                            fPedestalInsideLogic,
                                            "M32Pedestal2Inside",
                                            fM32Logic,
                                            false,
                                            0);  
     }
     
     //M32 Complete (girders+joints+pedestals)                                      
     G4ThreeVector fM32PositionVector = G4ThreeVector(fM32X,- 900. *CLHEP::mm,fM32Distance); 
     
     G4RotationMatrix *fElectronRotationMatrix = new G4RotationMatrix(0.,0.,0.);
     
    
     fElectronRotationMatrix->rotateY(-fThetaElectron);

	if (bModulesOn==true)
	{     
     fM32Physical = new G4PVPlacement(fElectronRotationMatrix,
                                      fM32PositionVector,
                                      fM32Logic,
                                      "M32",
                                      fWorldLogic,
                                      false,
                                      0);        
     }
     
    //M33
    G4Box* fM33Solid = new G4Box("M33",
                                  fGirderWidth * 0.5 +fGirderJointLength,
                                  150 * CLHEP::cm,
                                  fM33GirderLength * 0.5);
    
    fM33Logic = new G4LogicalVolume(fM33Solid,				//M33Logic envelope for the rotation of the whole module (girder+joints+pedestals)
                                    fWorldMaterial,
                                    "M33");
    
	
	G4Box* fM33GirderA0Solid = new G4Box("M33GirderA0",
                                              fGirderWidth * 0.5,
                                              fGirderHeight * 0.5,
                                              fM33GirderLength * 0.5);
    
    G4Box* fM33GirderA1Solid = new G4Box("M33GirderA1",
                                              fGirderWidth * 0.5 - fGirderThickness,
                                              fGirderHeight * 0.5 - fGirderThickness,
                                              fM33GirderLength * 0.6);
    
    G4SubtractionSolid* fM33GirderSolid = new G4SubtractionSolid("M33Girder", fM33GirderA0Solid, fM33GirderA1Solid);
    
    fM33GirderLogic = new G4LogicalVolume(fM33GirderSolid,
                                               fGirderMaterial,
                                               "M33Girder");
        
    fM33GirderLogic->SetVisAttributes(fGirderAttribute);
    
    		 
    G4ThreeVector fM33LGirderPositionVector = G4ThreeVector(-fGirderJointLength * 0.5 - fGirderWidth * 0.5, fGirderY,0.); //support are made of 2 parallel identical girders, this is Left
    G4ThreeVector fM33RGirderPositionVector = G4ThreeVector(+fGirderJointLength * 0.5 + fGirderWidth * 0.5, fGirderY,0.); // this is right
    
    if (bModulesOn==true)
    {
    fM33LGirderPhysical = new G4PVPlacement(0,
                                            fM33LGirderPositionVector,
                                            fM33GirderLogic,
                                            "M33LGirder",
                                            fM33Logic,
                                            false,
                                            0);    
    
    
    fM33RGirderPhysical = new G4PVPlacement(0,
                                            fM33RGirderPositionVector,
                                            fM33GirderLogic,
                                            "M33RGirder",
                                            fM33Logic,
                                            false,
                                            0);
    }
    G4ThreeVector fM33Joint1PositionVector = G4ThreeVector(0., fGirderY,- fM33GirderLength * 0.5 + fGirderWidth * 0.5); 
    G4ThreeVector fM33Joint2PositionVector = G4ThreeVector(0., fGirderY, + fM33GirderLength * 0.5 - fGirderWidth * 0.5);
    
    if (bModulesOn==true)
    {
    fM33Joint1Physical = new G4PVPlacement(0,
                                           fM33Joint1PositionVector,
                                           fGirderJointLogic,
                                           "M33Joint1",
                                           fM33Logic,
                                           false,
                                           0);  
     
     fM33Joint2Physical = new G4PVPlacement(0,
                                            fM33Joint2PositionVector,
                                            fGirderJointLogic,
                                            "M33Joint2",
                                            fM33Logic,
                                            false,
                                            0);
	}
   
    //M33 Pedestals
    G4ThreeVector fM33Pedestal1PositionVector = G4ThreeVector(0., fPedestalY,- fM33GirderLength * 0.5 + fPedestalLength * 0.5); 
    G4ThreeVector fM33Pedestal2PositionVector = G4ThreeVector(0., fPedestalY,+ fM33GirderLength * 0.5 - fPedestalLength * 0.5);
    
    if (bModulesOn==true)
    {
    fM33Pedestal1Physical = new G4PVPlacement(0,
                                            fM33Pedestal1PositionVector,
                                            fPedestalLogic,
                                            "M33Pedestal1",
                                            fM33Logic,
                                            false,
                                            0);  
    
    fM33Pedestal1InsidePhysical = new G4PVPlacement(0,
                                            fM33Pedestal1PositionVector,
                                            fPedestalInsideLogic,
                                            "M33Pedestal1Inside",
                                            fM33Logic,
                                            false,
                                            0);                                            
     
     fM33Pedestal2Physical = new G4PVPlacement(0,
                                            fM33Pedestal2PositionVector,
                                            fPedestalLogic,
                                            "M33Pedestal2",
                                            fM33Logic,
                                            false,
                                            0); 
                                            
    fM33Pedestal2InsidePhysical = new G4PVPlacement(0,
                                            fM33Pedestal2PositionVector,
                                            fPedestalInsideLogic,
                                            "M33Pedestal2Inside",
                                            fM33Logic,
                                            false,
                                            0);  
     }
     
     //M33 Complete (girders+joints+pedestals)                                      
     G4ThreeVector fM33PositionVector = G4ThreeVector(fM33X,0.,fM33Distance); 
     
     //G4RotationMatrix *fElectronRotationMatrix = new G4RotationMatrix(0.,0.,0.);
     
    
     //fElectronRotationMatrix->rotateY(-fThetaElectron);

     if (bModulesOn==true)
     {
     fM33Physical = new G4PVPlacement(fElectronRotationMatrix,
                                      fM33PositionVector,
                                      fM33Logic,
                                      "M33",
                                      fWorldLogic,
                                      false,
                                      0); 
     }
     
     }
    
    // Transparent detector
    if(bTransparentDetector){

		G4VisAttributes* fDetectorVisAttribute; 							// set detector vis attribute
        fDetectorVisAttribute = new G4VisAttributes(G4Colour(1.0,0.0,1.0));
        fDetectorVisAttribute->SetForceSolid(false);
        
        // Tube for hole subtraction in screen
        G4Tubs* fBeamPipeHoleSolid = new G4Tubs("BeamPipeHoleSolid",
                                              0.,
                                              fBeamPipeA0OuterRadius,
                                              fBeamPipeA0Length * 0.5,
                                              0*CLHEP::deg,
                                              360*CLHEP::deg);
        
        // Screen 
        G4Box* fTransparentDetectorSolidBox = new G4Box("TransparentDetector",
                                                     fTransparentDetectorWidth * 0.5,
                                                     fTransparentDetectorHeight * 0.5,
                                                     fTransparentDetectorLength * 0.5);
        
        G4SubtractionSolid* fTransparentDetectorSolid = new G4SubtractionSolid("TransparentDetector", fTransparentDetectorSolidBox, fBeamPipeHoleSolid,
        																		0,
        																		G4ThreeVector(0.,-fRoomShiftY,0.));// screen not centered on beam axys, floor-ceiling asimmetry

        
        fTransparentDetectorLogic = new G4LogicalVolume(fTransparentDetectorSolid,
                                                        fWorldMaterial,
                                                        "TransparentDetector");
       
        fTransparentDetectorLogic->SetVisAttributes(fDetectorVisAttribute);

        
        G4ThreeVector fTransparentDetectorPositionVector;


        fTransparentDetectorPositionVector = G4ThreeVector(0.,fRoomShiftY,fConcreteA0Distance - fWallThickness * 0.5 - fTransparentDetectorLength * 0.5);

        fTransparentDetectorPhysical = new G4PVPlacement(0,
                                                         fTransparentDetectorPositionVector,
                                                         fTransparentDetectorLogic,
                                                         "TransparentDetector",
                                                         fWorldLogic,
                                                         false,
                                                         0);
        
        fTransparentDetectorPositionVector = G4ThreeVector(0.,fRoomShiftY,fBeamPipeA0Length - fTransparentDetectorLength * 0.5 - 100.0 * CLHEP::cm); //100 cm shift on z-axis to avoid overlap with M32
        
        fTransparentDetectorPhysical = new G4PVPlacement(0,
                                                         fTransparentDetectorPositionVector,
                                                         fTransparentDetectorLogic,
                                                         "TransparentDetector",
                                                         fWorldLogic,
                                                         false,
                                                         1);

        fTransparentDetectorPositionVector = G4ThreeVector(0.,fRoomShiftY,fConcreteA1Distance - fConcreteA1Length * 0.5 - fTransparentDetectorLength * 0.5);

        fTransparentDetectorPhysical = new G4PVPlacement(0,
                                                         fTransparentDetectorPositionVector,
                                                         fTransparentDetectorLogic,
                                                         "TransparentDetector",
                                                         fWorldLogic,
                                                         false,
                                                         2);

        
        
        
        G4Box* fTransparentDetectorSolidBox1 = new G4Box("TransparentDetectorBox",
                                                     fRoomWidth * 0.5,
                                                     fTransparentDetectorHeight * 0.5,
                                                     fTransparentDetectorLength * 0.5);
        
        fTransparentDetectorBoxLogic = new G4LogicalVolume(fTransparentDetectorSolidBox1,
                                                           fWorldMaterial,
                                                           "TransparentDetectorBox");
        
        G4ThreeVector fTransparentDetectorBoxPositionVector;


        fTransparentDetectorBoxPositionVector = G4ThreeVector(fRoomShiftX,
        													fRoomShiftY,	
        													fBeamPipeA0Length + (fRomanPotLength + 2.*fRomanPotWindowLength) + fBeamPipeA2Length + fTransparentDetectorLength * 0.5);
        

        fTransparentDetectorBoxPhysical = new G4PVPlacement(0,
                                                            fTransparentDetectorBoxPositionVector,
                                                            fTransparentDetectorBoxLogic,
                                                            "TransparentDetectorBox",
                                                            fWorldLogic,
                                                            false,
                                                            1);

        //G4ThreeVector fTransparentDetectorBoxPositionVector;


        fTransparentDetectorBoxPositionVector = G4ThreeVector(fRoomShiftX,
        													fRoomShiftY,	
        													fConcreteA0Distance + fWallThickness * 0.5 + fRoomLength + fWallThickness + fTransparentDetectorLength * 0.5);
        
        
        fTransparentDetectorBoxPhysical = new G4PVPlacement(0,
                                                            fTransparentDetectorBoxPositionVector,
                                                            fTransparentDetectorBoxLogic,
                                                            "TransparentDetectorBox",
                                                            fWorldLogic,
                                                            false,
                                                            2);

        //fTransparentDetectorLogic->SetVisAttributes(G4VisAttributes::GetInvisible()); // EDIT PAOLO detector set visible
        //fTransparentDetectorBoxLogic->SetVisAttributes(G4VisAttributes::GetInvisible());
    
    
    	//Transparent Detector RACKS 
         G4Box* fTransparentDetectorRack1Solid = new G4Box("TransparentDetectorRack1Solid",
                                                     fTransparentRackLength * 0.5,
                                                     fTransparentRackHeight * 0.5,
                                                     fTransparentRackWidth * 0.5);
         G4Box* fTransparentDetectorRack2Solid = new G4Box("TransparentDetectorRack2Solid",
                                                     fTransparentRackWidth* 0.5,
                                                     fTransparentRackHeight * 0.5,
                                                     fTransparentRackLength * 0.5);
        
  
        
        fTransparentDetectorRack1Logic = new G4LogicalVolume(fTransparentDetectorRack1Solid,
                                                        fBeamPipeVacuum,
                                                        "TransparentDetectorRack1");
        fTransparentDetectorRack2Logic = new G4LogicalVolume(fTransparentDetectorRack2Solid,
                                                        fBeamPipeVacuum,
                                                        "TransparentDetectorRack2");
       
        fTransparentDetectorRack1Logic->SetVisAttributes(fDetectorVisAttribute);
		fTransparentDetectorRack2Logic->SetVisAttributes(fDetectorVisAttribute);
        
        //G4ThreeVector fTransparentDetectorRack1PositionVector;
        G4ThreeVector fTransparentDetectorRack2PositionVector;
        
		
        //fTransparentDetectorRack1PositionVector = G4ThreeVector(fRack1PositionX,fRack1PositionY,fRack1PositionZ);
		fTransparentDetectorRack2PositionVector = G4ThreeVector(fRack2PositionX,fRack2PositionY,fRack2PositionZ);
		/*
        //fTransparentDetectorRack1Physical = 
         new G4PVPlacement(0,
                                                         fTransparentDetectorRack1PositionVector,
                                                         fTransparentDetectorRack1Logic,
                                                         "TransparentDetectorRack1",
                                                         fWorldLogic,
                                                         false,
                                                         0);   
                     
       //fTransparentDetectorRack2Physical =
         new G4PVPlacement(0,
                                                         fTransparentDetectorRack2PositionVector,
                                                         fTransparentDetectorRack2Logic,
                                                         "TransparentDetectorRack2",
                                                         fWorldLogic,
                                                         false,
                                                         0); 
    	*/
    	//Transparent Detector for Hexapod dose evaluation 
       G4Box* fTransparentDetectorHexapodSolid = new G4Box("TransparentDetectorHexapodSolid",
                                                     5 * CLHEP::cm,
                                                     5 * CLHEP::cm,
                                                     5 * CLHEP::cm);
       
        fTransparentDetectorHexapodLogic = new G4LogicalVolume(fTransparentDetectorHexapodSolid,
                                                        fWorldMaterial,
                                                        "TransparentDetectorHexapod");
       
        fTransparentDetectorRack1Logic->SetVisAttributes(fDetectorVisAttribute);

        G4ThreeVector fTransparentDetectorHexapodPositionVector;
        
        //fTransparentDetectorHexapodPositionVector = G4ThreeVector(fHexapodA1PositionX,fHexapodA1PositionY,fHexapodA1PositionZ);
		
        fTransparentDetectorHexapodPhysical = new G4PVPlacement(0,
                                                         fTransparentDetectorRack2PositionVector, //fTransparentDetectorHexapodPositionVector, //to evalaute dose in rack!
                                                         fTransparentDetectorHexapodLogic,
                                                         "TransparentDetectorHexapodA1",
                                                         fWorldLogic,
                                                         false,
                                                         0);   
/*
        fTransparentDetectorHexapodPositionVector = G4ThreeVector(fHexapodA2PositionX,fHexapodA2PositionY,fHexapodA2PositionZ);
		
        fTransparentDetectorHexapodPhysical = new G4PVPlacement(0,
                                                         fTransparentDetectorHexapodPositionVector,
                                                         fTransparentDetectorHexapodLogic,
                                                         "TransparentDetectorHexapodA2",
                                                         fWorldLogic,
                                                         false,
                                                         1); 
       
        fTransparentDetectorHexapodPositionVector = G4ThreeVector(fHexapodB1PositionX,fHexapodB1PositionY,fHexapodB1PositionZ);
		
        fTransparentDetectorHexapodPhysical = new G4PVPlacement(0,
                                                         fTransparentDetectorHexapodPositionVector,
                                                         fTransparentDetectorHexapodLogic,
                                                         "TransparentDetectorHexapodAB1",
                                                         fWorldLogic,
                                                         false,
                                                         2);    
                                                         
        fTransparentDetectorHexapodPositionVector = G4ThreeVector(fHexapodB2PositionX,fHexapodB2PositionY,fHexapodB2PositionZ);
		
        fTransparentDetectorHexapodPhysical = new G4PVPlacement(0,
                                                         fTransparentDetectorHexapodPositionVector,
                                                         fTransparentDetectorHexapodLogic,
                                                         "TransparentDetectorHexapodB2",
                                                         fWorldLogic,
                                                         false,
                                                         3);   
*/                                                                      
    }

    // Pb disks
    G4VisAttributes* fPbDiskVisAttribute = new G4VisAttributes(G4Colour(0.2,0.2,0.2));
      fPbDiskVisAttribute->SetForceSolid(true);
    
    G4Tubs* fPbDiskSolid = new G4Tubs("PbDisk",
                                      fBeamPipeA0OuterRadius,
                                      fPbDiskOuterRadius,
                                      fPbDiskLength * 0.5,
                                      0*CLHEP::deg,
                                      360*CLHEP::deg);
    
    G4LogicalVolume* fPbDiskLogic = new G4LogicalVolume(fPbDiskSolid,
                                                        fPbDiskMaterial,
                                                        "PbDisk");
    
    fPbDiskLogic->SetVisAttributes(fPbDiskVisAttribute);
    
      G4Tubs* fPbDiskM30Solid = new G4Tubs("PbDiskM30",
                                      fBeamPipeA0OuterRadius,
                                      fCSPECOuterRadius,
                                      fPbDiskLength * 0.5,
                                      0*CLHEP::deg,
                                      360*CLHEP::deg);
    
    G4LogicalVolume* fPbDiskM30Logic = new G4LogicalVolume(fPbDiskM30Solid,
                                                        fPbDiskMaterial,
                                                        "PbDiskM30");
    
    fPbDiskM30Logic->SetVisAttributes(fPbDiskVisAttribute);
      
    G4ThreeVector fPbDiskM30PositionVector = G4ThreeVector(0.,0.,fM30Distance + fCSPECLength * 0.5 + fCSPECWindowLength + fPbDiskLength);
      
        if (bModulesOn==true)
        {
        /*
        fPbDiskM30Physical = new G4PVPlacement(0,
                                        fPbDiskM30PositionVector,
                                        fPbDiskM30Logic,
                                        "PbDiskM30",
                                        fWorldLogic,
                                        false,
                                        0);
         */
        }
    
    
    if(PbDisks == 1 || PbDisks == 3){
    G4ThreeVector fPbDiskA0PositionVector = G4ThreeVector(0.,0.,fPbDiskA0Distance);
    fPbDiskPhysical = new G4PVPlacement(0,
                                        fPbDiskA0PositionVector,
                                        fPbDiskLogic,
                                        "PbDisk",
                                        fWorldLogic,
                                        false,
                                        0);
    }

    if(PbDisks == 2 || PbDisks == 3){
        G4ThreeVector fPbDiskA1PositionVector = G4ThreeVector(0.,0.,fPbDiskA1Distance);
        fPbDiskPhysical = new G4PVPlacement(0,
                                            fPbDiskA1PositionVector,
                                            fPbDiskLogic,
                                            "PbDisk",
                                            fWorldLogic,
                                            false,
                                            0);
    }

    
    
#ifndef G4MULTITHREADED
       if(bTransparentDetector){
        G4VSensitiveDetector* vDetector = new G4ELIMED_SensitiveDetector("/det");
        G4SDManager::GetSDMpointer()->AddNewDetector(vDetector);
        
        //fTransparentDetectorLogic->SetSensitiveDetector(vDetector);

        fTransparentDetectorBoxLogic->SetSensitiveDetector(vDetector);
        //fTransparentCSPECLogic->SetSensitiveDetector(vDetector); //CSPEC scoring only!!
       
        //fTransparentDetectorRack1Logic->SetSensitiveDetector(vDetector);
        //fTransparentDetectorRack2Logic->SetSensitiveDetector(vDetector);
		
	//fTransparentDetectorHexapodLogic->SetSensitiveDetector(vDetector);
        //fCollimatorLogic->SetSensitiveDetector(vDetector);
    }
    
       G4MultiFunctionalDetector* multisd = new G4MultiFunctionalDetector("/multisd");
   G4VPrimitiveScorer* dosedet = new G4PSDoseDeposit("dose");
   multisd->RegisterPrimitive(dosedet);
   SetSensitiveDetector("TransparentDetectorHexapod",multisd);
   

#endif
    
    return fWorldPhysical;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef G4MULTITHREADED
void G4ELIMED_DetectorConstruction::ConstructSDandField(){
    
    if(bTransparentDetector){
        G4VSensitiveDetector* vDetector = new G4ELIMED_SensitiveDetector("/det");
        G4SDManager::GetSDMpointer()->AddNewDetector(vDetector);
        
        //fTransparentDetectorLogic->SetSensitiveDetector(vDetector);
        
        fTransparentDetectorBoxLogic->SetSensitiveDetector(vDetector);
        //fTransparentCSPECLogic->SetSensitiveDetector(vDetector); //CSPEC scoring only!!
                
       // fTransparentDetectorRack1Logic->SetSensitiveDetector(vDetector);
        //fTransparentDetectorRack2Logic->SetSensitiveDetector(vDetector);

	//fTransparentDetectorHexapodLogic->SetSensitiveDetector(vDetector);
        //fCollimatorLogic->SetSensitiveDetector(vDetector);
    }
    
       G4MultiFunctionalDetector* multisd = new G4MultiFunctionalDetector("/multisd");
   G4VPrimitiveScorer* dosedet = new G4PSDoseDeposit("dose");
   multisd->RegisterPrimitive(dosedet);
   SetSensitiveDetector("TransparentDetectorHexapod",multisd);

}
#else
void G4ELIMED_DetectorConstruction::ConstructSDandField(){
}
#endif
