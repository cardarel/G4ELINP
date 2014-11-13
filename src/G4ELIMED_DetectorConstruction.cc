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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ELIMED_DetectorConstruction::G4ELIMED_DetectorConstruction():fWorldLogic(0){
    
    fMessenger = new G4ELIMED_DetectorConstructionMessenger(this);
    DefineMaterials();
    
    // World
    fWorldSize = G4ThreeVector(20000. * CLHEP::cm,20000. * CLHEP::cm,20000. * CLHEP::cm);
    
    // Beam pipe
    bBeamPipe = true;
    bConcrete = true;
    bRomanPot = true;
    bCollimatorSupport = true;
    bCollimator = true;
    bTransparentDetector = true;
    
    // Pb disks
    PbDisks = 0;
    ResetDetectorForSetup(0);

    // Collimator
    fCollimatorNumber = 12;   
    fCollimatorDistance = 0. * CLHEP::mm;
    fCollimatorAperture = 0.59 * CLHEP::mm;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

G4ELIMED_DetectorConstruction::~G4ELIMED_DetectorConstruction(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4ELIMED_DetectorConstruction::ResetDetectorForSetup(int line){

			/////////////////////LINE SELECTION ONLY FOR TEST!!
	
			 //line = 1; // 1 for HE / 0 for LE

			////////////////
	
    // Beam Pipe
    fBeamPipeA0Length = 982.5 * CLHEP::cm;
    if(line==1){
        fBeamPipeA0Length = 861. * CLHEP::cm;
    }
    fBeamPipeA0InnerRadius = 2. * CLHEP::cm;
    fBeamPipeA0OuterRadius = 2.16 * CLHEP::cm;
    
    fBeamPipeA2Length = 120. * CLHEP::cm;
    
    // Roman Pot
    fRomanPotWindowLength = 0.5 * CLHEP::cm;
    fRomanPotWindowInnerRadius = 2.16 * CLHEP::cm;
    fRomanPotWindowOuterRadius = 20.5 * CLHEP::cm;
    
    fRomanPotLength = 86. * CLHEP::cm;
    fRomanPotInnerRadius = 20. * CLHEP::cm;
    fRomanPotOuterRadius = 20.5 * CLHEP::cm;
    fRomanPotSupportAngle = G4ThreeVector(0.,0.,0.);
    
    // Concrete
    
 	if(line==1)
	{

	//High Energy line variables definition for walls

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
	//LOW Energy line variables definition for walls

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


	// SAME Concrete A1 shielding block  HE and LE lines
 	fConcreteA1Length = 100. * CLHEP::cm;
	fConcreteA1Width = 200. * CLHEP::cm;
	fConcreteA1Height = 200. * CLHEP::cm;
	fConcreteA1RadiusPipe = 2.16 * CLHEP::cm;
	fConcreteA1Distance = fRomanPotLength + fBeamPipeA0Length + 2*fRomanPotWindowLength + 120. * CLHEP::cm - fConcreteA1Length * 0.5;

    
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


    // Detector SCREEN
    fTransparentDetectorWidth = 554. * CLHEP::cm; //edit to fit the smaller LE room (278cm on the right)
    fTransparentDetectorHeight = 500.  * CLHEP::cm; //edit to fit the room height
    fTransparentDetectorLength = 1. * CLHEP::cm;
    
    fPbDiskLength = 5. * CLHEP::cm;
    fPbDiskOuterRadius = 30. * CLHEP::cm;
    
    fPbDiskA0Distance = fBeamPipeA0Length - fPbDiskLength * 0.5 - 110. * CLHEP::cm;
    fPbDiskA1Distance = fBeamPipeA0Length - fPbDiskLength * 0.5;
    
    
    //Detector RACKS
    fTransparentRackWidth = 60. * CLHEP::cm;
    fTransparentRackLength = 80. * CLHEP::cm;
    fTransparentRackHeight = 200. * CLHEP::cm;
   
      if(line==1)
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
   


    // Definition of stainless steel (not in NIST) for pipes
    G4Element* C = G4NistManager::Instance()->FindOrBuildElement("C");
    G4Element* Si = G4NistManager::Instance()->FindOrBuildElement("Si");
    G4Element* Cr = G4NistManager::Instance()->FindOrBuildElement("Cr");
    G4Element* Mn = G4NistManager::Instance()->FindOrBuildElement("Mn");
    G4Element* Ni = G4NistManager::Instance()->FindOrBuildElement("Ni");
    G4Element* Fe = G4NistManager::Instance()->FindOrBuildElement("Fe");


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
    
    fWorldMaterial = G4_AIR;
    //fBeamPipeMaterial = StainlessSteel; PAOLO EDIT pipe vacuum
    fBeamPipeMaterial = StainlessSteel;
    fConcreteMaterial = G4_Concrete;
    fCollimatorMaterial = G4_W;
    fCollimatorSupportMaterial = G4_Al;
    fPbDiskMaterial = G4_Pb;
    fBeamPipeVacuum = Vacuum;
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
        fBeamPipeVisAttribute->SetForceSolid(false);
        
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
        
        G4VPhysicalVolume* fBeamPipeA0InsidePhysical = new G4PVPlacement(0,
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
        
        
        G4VPhysicalVolume* fBeamPipeA2InsidePhysical = new G4PVPlacement(0,
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
                                                  fRomanPotOuterRadius,
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
        
        G4VPhysicalVolume* fRomanPotWindow0Physical;
        G4VPhysicalVolume* fRomanPotWindow1Physical;
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

        G4VPhysicalVolume* fRomanPotPhysical;
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
        
        G4SubtractionSolid* fConcreteA1Solid = new G4SubtractionSolid("ConcreteA1", fConcreteA1B0Solid, fConcreteA1B1Solid);
        
        
        fConcreteA1Logic = new G4LogicalVolume(fConcreteA1Solid,
                                               fConcreteMaterial,
                                               "ConcreteA1");
        
        fConcreteA1Logic->SetVisAttributes(fConcreteVisAttribute);
        
        G4ThreeVector fConcreteA1PositionVector = G4ThreeVector(0.,0.,fConcreteA1Distance);
        
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

        G4Box* fConcreteA2Solid = new G4Box("ConcreteA2",
                                              (fRoomWidth +fWallThickness + fWallThickness2) * 0.5,
                                              fWallHeigth * 0.5,
                                              fWallThickness * 0.5);


        
        fConcreteA2Logic = new G4LogicalVolume(fConcreteA2Solid,
                                               fConcreteMaterial,
                                               "ConcreteA2");
        
        fConcreteA2Logic->SetVisAttributes(fConcreteVisAttribute);
        
        G4ThreeVector fConcreteA2PositionVector = G4ThreeVector(fRoomShiftX -(fWallThickness2 - fWallThickness) * 0.5, //asimmetrical right wall thickness requires this additional shift
        														fRoomShiftY,
        														fConcreteA0Distance + fWallThickness * 0.5 + fRoomLength + fWallThickness * 0.5);
        
        fConcreteA2Physical = new G4PVPlacement(0,
                                                fConcreteA2PositionVector,
                                                fConcreteA2Logic,
                                                "fConcreteA2",
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
        
        
        
        
        G4SubtractionSolid* fCollimatorSupportA0Solid = new G4SubtractionSolid("CollimatorSupportA0", fCollimatorSupportA0B0Solid, fCollimatorSupportA0B1Solid,0,G4ThreeVector(0.,fCollimatorSupportA0B1Distance,0.));
        
        G4SubtractionSolid* fCollimatorSupportA1Solid = new G4SubtractionSolid("CollimatorSupportA1", fCollimatorSupportA0Solid, fCollimatorSupportA0B2Solid,0,G4ThreeVector(0.,fCollimatorSupportA0B1Distance,+(2.*fCollimatorSupportA1B0Length+fCollimatorLength)*0.5));
        
        G4SubtractionSolid* fCollimatorSupportSolid = new G4SubtractionSolid("CollimatorSupport", fCollimatorSupportA1Solid, fCollimatorSupportA0B2Solid,0,G4ThreeVector(0.,fCollimatorSupportA0B1Distance,-(2.*fCollimatorSupportA1B0Length+fCollimatorLength)*0.5));
        
        fCollimatorSupportLogic = new G4LogicalVolume(fCollimatorSupportSolid,
                                                      fCollimatorSupportMaterial,
                                                      "CollimatorSupport");
        
        fCollimatorSupportLogic->SetVisAttributes(fCollimatorSupportVisAttribute);
    }
    
    
    // Collimator
    if(bCollimator){
        G4VisAttributes* fCollimatorVisAttribute;
        fCollimatorVisAttribute = new G4VisAttributes(G4Colour(0., 0., 1.));
        fCollimatorVisAttribute->SetForceSolid(true);
        
        G4Box* fCollimatorSolid = new G4Box("Collimator",
                                            fCollimatorWidth * 0.5,
                                            fCollimatorHeight * 0.5,
                                            fCollimatorLength * 0.5);
        fCollimatorLogic = new G4LogicalVolume(fCollimatorSolid,
                                               fCollimatorMaterial,
                                               "Collimator");
        
        fCollimatorLogic->SetVisAttributes(fCollimatorVisAttribute);
    }
    
    
    G4VPhysicalVolume* fCollimatorSupportA0Physical;
    G4VPhysicalVolume* fCollimatorA0Physical;
    G4VPhysicalVolume* fCollimatorA1Physical;
    
    if(bCollimator || bCollimatorSupport){
        
        G4Box* fCollimatorEnvelopeSolid = new G4Box("CollimatorEnvelopeSolid",
                                                    fCollimatorSupportA0B0Width * 0.5,
                                                    fCollimatorSupportA0B0Height * 0.5,
                                                    (fCollimatorLength + fCollimatorSupportA1B0Length * 2.) * 0.5);
        fCollimatorEnvelopeLogic = new G4LogicalVolume(fCollimatorEnvelopeSolid,
                                                       fBeamPipeVacuum,
                                                       "CollimatorEnvelope");
        fCollimatorEnvelopeLogic->SetVisAttributes(G4VisAttributes::GetInvisible());
    }
    
    if(bCollimatorSupport){
        fCollimatorSupportA0Physical = new G4PVPlacement(0,
                                                         G4ThreeVector(0.,0.,0.),
                                                         fCollimatorSupportLogic,
                                                         "CollimatorSupport",
                                                         fCollimatorEnvelopeLogic,
                                                         false,
                                                         0);
    }
    if(bCollimator){
        G4double vRelativeAperture = (fCollimatorAperture+fCollimatorWidth)*0.5;
        
        G4ThreeVector fCollimatorA1PositionVector = G4ThreeVector(+vRelativeAperture,fCollimatorSupportA0B1Distance,0.);
        
        G4ThreeVector fCollimatorA0PositionVector = G4ThreeVector(-vRelativeAperture,fCollimatorSupportA0B1Distance,0.);
        
        fCollimatorA0Physical = new G4PVPlacement(0,
                                                  fCollimatorA0PositionVector,
                                                  fCollimatorLogic,
                                                  "CollimatorL",
                                                  fCollimatorEnvelopeLogic,
                                                  false,
                                                  0);
        
        fCollimatorA1Physical = new G4PVPlacement(0,
                                                  fCollimatorA1PositionVector,
                                                  fCollimatorLogic,
                                                  "CollimatorR",
                                                  fCollimatorEnvelopeLogic,
                                                  false,
                                                  1);
    }
    
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
        
        G4double vIndex = double(i1);
        
        if(fmod(fCollimatorNumber,2)==0.) {
            vIndex += 0.5;
        }
        
        vIndex -= int(fCollimatorNumber/2.);
        
        G4double vAngle = double(i1)/double(fCollimatorNumber);
                
        G4double vRelativeDistance = vIndex*(fCollimatorDistance+fCollimatorLength+fCollimatorSupportA1B0Length*2.);
        
        G4ThreeVector fCollimatorSupportA0PositionVector = G4ThreeVector(0.,0.,vRelativeDistance);
        
        G4RotationMatrix* fCollimatorRotationMatrix = new G4RotationMatrix(2.*M_PI*vAngle,0.,0.);

        if(bCollimator || bCollimatorSupport){
            fCollimatorEnvelopePhysical = new G4PVPlacement(fCollimatorRotationMatrix,
                                                            fCollimatorSupportA0PositionVector,
                                                            fCollimatorEnvelopeLogic,
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
    
    G4VPhysicalVolume* fRomanPotCollimatorEnvelopePhysical = new G4PVPlacement(fRomanPotCollimatorEnvelopeRotationMatrix,
                                                                               G4ThreeVector(0.,0.,0.),
                                                                               fRomanPotCollimatorEnvelopeLogic,
                                                                               "RomanPotCollimatorEnvelope",
                                                                               fRomanPotEnvelopeLogic,
                                                                               false,
                                                                               0);

    
    // Roman pot
    if(bRomanPot){
        
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
        G4VPhysicalVolume* fTransparentDetectorPhysical;

        fTransparentDetectorPositionVector = G4ThreeVector(0.,fRoomShiftY,fConcreteA0Distance - fWallThickness * 0.5 - fTransparentDetectorLength * 0.5);

        fTransparentDetectorPhysical = new G4PVPlacement(0,
                                                         fTransparentDetectorPositionVector,
                                                         fTransparentDetectorLogic,
                                                         "TransparentDetector",
                                                         fWorldLogic,
                                                         false,
                                                         0);
        
        fTransparentDetectorPositionVector = G4ThreeVector(0.,fRoomShiftY,fBeamPipeA0Length - fTransparentDetectorLength * 0.5);
        
        fTransparentDetectorPhysical = new G4PVPlacement(0,
                                                         fTransparentDetectorPositionVector,
                                                         fTransparentDetectorLogic,
                                                         "TransparentDetector",
                                                         fWorldLogic,
                                                         false,
                                                         1);

        fTransparentDetectorPositionVector = G4ThreeVector(0.,fRoomShiftY,fBeamPipeA0Length + (fRomanPotLength + 2.*fRomanPotWindowLength) + fTransparentDetectorLength * 0.5);

        fTransparentDetectorPhysical = new G4PVPlacement(0,
                                                         fTransparentDetectorPositionVector,
                                                         fTransparentDetectorLogic,
                                                         "TransparentDetector",
                                                         fWorldLogic,
                                                         false,
                                                         2);

        
        
        
        
        fTransparentDetectorBoxLogic = new G4LogicalVolume(fTransparentDetectorSolidBox,
                                                           fWorldMaterial,
                                                           "TransparentDetectorBox");
        
        G4ThreeVector fTransparentDetectorBoxPositionVector;
        G4VPhysicalVolume* fTransparentDetectorBoxPhysical;

        fTransparentDetectorBoxPositionVector = G4ThreeVector(0.,
        													fRoomShiftY,	
        													fBeamPipeA0Length + (fRomanPotLength + 2.*fRomanPotWindowLength) + fBeamPipeA2Length + fTransparentDetectorLength * 0.5);
        
        fTransparentDetectorBoxPhysical = new G4PVPlacement(0,
                                                            fTransparentDetectorBoxPositionVector,
                                                            fTransparentDetectorBoxLogic,
                                                            "TransparentDetectorBox",
                                                            fWorldLogic,
                                                            false,
                                                            1);

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
        
        G4ThreeVector fTransparentDetectorRack1PositionVector;
        G4ThreeVector fTransparentDetectorRack2PositionVector;
        
        G4VPhysicalVolume* fTransparentDetectorRack1Physical;
		G4VPhysicalVolume* fTransparentDetectorRack2Physical;
		
        fTransparentDetectorRack1PositionVector = G4ThreeVector(fRack1PositionX,fRack1PositionY,fRack1PositionZ);
		fTransparentDetectorRack2PositionVector = G4ThreeVector(fRack2PositionX,fRack2PositionY,fRack2PositionZ);
		
        fTransparentDetectorRack1Physical = new G4PVPlacement(0,
                                                         fTransparentDetectorRack1PositionVector,
                                                         fTransparentDetectorRack1Logic,
                                                         "TransparentDetectorRack1",
                                                         fWorldLogic,
                                                         false,
                                                         0);   
                     
       fTransparentDetectorRack2Physical = new G4PVPlacement(0,
                                                         fTransparentDetectorRack2PositionVector,
                                                         fTransparentDetectorRack2Logic,
                                                         "TransparentDetectorRack2",
                                                         fWorldLogic,
                                                         false,
                                                         0); 
    }

    // Pb disks
    G4VisAttributes* fPbDiskVisAttribute = new G4VisAttributes();
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
        
        fTransparentDetectorLogic->SetSensitiveDetector(vDetector);

        fTransparentDetectorBoxLogic->SetSensitiveDetector(vDetector);
       
        fTransparentDetectorRack1Logic->SetSensitiveDetector(vDetector);
        fTransparentDetectorRack2Logic->SetSensitiveDetector(vDetector);

        //fCollimatorLogic->SetSensitiveDetector(vDetector);
    }
#endif
    
    return fWorldPhysical;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef G4MULTITHREADED
void G4ELIMED_DetectorConstruction::ConstructSDandField(){
    if(bTransparentDetector){
        G4VSensitiveDetector* vDetector = new G4ELIMED_SensitiveDetector("/det");
        G4SDManager::GetSDMpointer()->AddNewDetector(vDetector);
        
        fTransparentDetectorLogic->SetSensitiveDetector(vDetector);
        
        fTransparentDetectorBoxLogic->SetSensitiveDetector(vDetector);
        
        fTransparentDetectorRack1Logic->SetSensitiveDetector(vDetector);
        fTransparentDetectorRack2Logic->SetSensitiveDetector(vDetector);

        //fCollimatorLogic->SetSensitiveDetector(vDetector);
    }
}
#else
void G4ELIMED_DetectorConstruction::ConstructSDandField(){
}
#endif
