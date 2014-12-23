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
// $Id: G4ELIMED_DetectorConstruction.hh,v 1.1 2010-10-18 15:56:17 maire Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef G4ELIMED_DetectorConstruction_h
#define G4ELIMED_DetectorConstruction_h 1
#endif

#include "G4VUserDetectorConstruction.hh"
#include "G4ELIMED_DetectorConstructionMessenger.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4RunManager.hh"

#include "globals.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4ELIMED_DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    
    G4ELIMED_DetectorConstruction();
    ~G4ELIMED_DetectorConstruction();
    
    void DefineMaterials();
    G4VPhysicalVolume* Construct();

    void ResetDetectorForSetup(int = 0);

private:
    G4ELIMED_DetectorConstructionMessenger* fMessenger;
    void ConstructSDandField();
    
    // World
private:
    G4ThreeVector fWorldSize;
    G4Box* fWorldSolid;
    G4LogicalVolume* fWorldLogic;
    G4VPhysicalVolume* fWorldPhysical;
    G4Material* fWorldMaterial;
    G4Material* fBeamPipeVacuum;   
    
    G4int bLine; 
    // Beam pipe
private:
    G4bool bBeamPipe;
    G4Material *fBeamPipeMaterial;
    
    G4VSolid* fBeamPipeA0Solid;
    G4LogicalVolume* fBeamPipeA0Logic;
    G4VPhysicalVolume* fBeamPipeA0Physical;
        G4VPhysicalVolume* fBeamPipeA0InsidePhysical;

    G4double fBeamPipeA0Length;
    G4double fBeamPipeA0InnerRadius;
    G4double fBeamPipeA0OuterRadius;
    
    G4VSolid* fBeamPipeA2Solid;
    G4LogicalVolume* fBeamPipeA2Logic;
    G4VPhysicalVolume* fBeamPipeA2Physical;
        G4VPhysicalVolume* fBeamPipeA2InsidePhysical ;

    G4double fBeamPipeA2Length;

    // Roman pot
public:
    void SetRomanPotSupportAngle(G4ThreeVector vAngle) {fRomanPotSupportAngle=vAngle;};
    G4ThreeVector GetRomanPotSupportAngle() {return fRomanPotSupportAngle;};
    void SetRomanPotSupportPosition(G4ThreeVector vPosition) {fRomanPotSupportPosition=vPosition;};
    G4ThreeVector GetRomanPotSupportPosition() {return fRomanPotSupportPosition;};
    
private:
    G4ThreeVector fRomanPotSupportAngle;
    G4ThreeVector fRomanPotSupportPosition;

    G4bool bRomanPot;
    G4LogicalVolume* fRomanPotWindowLogic;
    G4double fRomanPotWindowLength;
    G4double fRomanPotWindowInnerRadius;
    G4double fRomanPotWindowOuterRadius;
    
    G4LogicalVolume* fRomanPotLogic;
        G4VPhysicalVolume* fRomanPotPhysical;
    G4double fRomanPotLength;
    G4double fRomanPotInnerRadius;
    G4double fRomanPotOuterRadius;

            G4VPhysicalVolume* fRomanPotWindow0Physical;
        G4VPhysicalVolume* fRomanPotWindow1Physical;

    G4LogicalVolume* fRomanPotEnvelopeLogic;
    G4VPhysicalVolume* fRomanPotEnvelopePhysical;
    G4VPhysicalVolume* fRomanPotCollimatorEnvelopePhysical;

    // Concrete // variables added
private:
    G4bool bConcrete;
    G4Material *fConcreteMaterial;
    
    G4LogicalVolume* fConcreteA0Logic;
    G4LogicalVolume* fConcreteFloorLogic; 
    G4LogicalVolume* fConcreteTopLogic;
    G4LogicalVolume* fConcreteRightWallLogic;
    G4LogicalVolume* fConcreteLeftWallLogic;
    G4LogicalVolume* fConcreteA2Logic;
       
    G4VPhysicalVolume* fConcreteA0Physical;
    G4VPhysicalVolume* fConcreteFloorPhysical;
    G4VPhysicalVolume* fConcreteTopPhysical;
    G4VPhysicalVolume* fConcreteRightWallPhysical;
    G4VPhysicalVolume* fConcreteLeftWallPhysical;
    G4VPhysicalVolume* fConcreteA2Physical;

    //G4double fConcreteA0Length; PAOLO
    //G4double fConcreteA0Width;
    //G4double fConcreteA0Height;
    G4double fConcreteA0RadiusPipe;
    G4double fConcreteA0Distance;

    G4LogicalVolume* fConcreteA1Logic;
    G4VPhysicalVolume* fConcreteA1Physical;

    G4double fConcreteA1Length;
    G4double fConcreteA1Width;
    G4double fConcreteA1Height;
    G4double fConcreteA1RadiusPipe;
    G4double fConcreteA1Distance;
    
    //Walls 
   	G4double fRoomWidth; 
	G4double fRoomLength;
	G4double fRoomHeigth;

	G4double fBeamHeigth; //beamline heigth from floor
	G4double fRoomShiftX; // shift on x-axis of the room center with respect to beam direction axis
 	G4double fRoomShiftY; // shift on y-axis of the room center with respect to beam direction axis

	G4double fFloorThickness;
	G4double fTopThickness; //ceiling thickness
	G4double fWallThickness;
	G4double fWallThickness2; // only for HE line, left wall has different thickness
	G4double fWallHeigth; // height of side walls
	
	
	
    
    // Collimator
private:
    G4int fCollimatorNumber;
    G4double fCollimatorDistance;
    G4double fCollimatorAperture;

	G4int bCollimatorRelativeRandomDisplacement;
	G4double fCollDisplMean;
	G4double fCollDisplSigma;

public:
    void SetCollimatorNumber(G4int vNumber) {fCollimatorNumber=vNumber;};
    G4int GetCollimatorNumber() {return fCollimatorNumber;};

    void SetCollimatorDistance(G4double vDistance) {fCollimatorDistance=vDistance;};
    G4double GetCollimatorDistance() {return fCollimatorDistance;};

    void SetCollimatorAperture(G4double vAperture) {fCollimatorAperture=vAperture;};
    G4double GetCollimatorAperture() {return fCollimatorAperture;};

    void SetCollRandDispl(G4int vNumber) {bCollimatorRelativeRandomDisplacement=vNumber;};
    G4int GetCollRandDispl() {return bCollimatorRelativeRandomDisplacement;};

    void SetCollRandDisplMean(G4double vDistance) {fCollDisplMean=vDistance;};
    G4double GetCollRandDisplMean() {return fCollDisplMean;};

    void SetCollRandDisplSigma(G4double vAperture) {fCollDisplSigma=vAperture;};
    G4double GetCollRandDisplSigma() {return fCollDisplSigma;};

private:
    G4bool bCollimator;
    G4Material *fCollimatorMaterial;

    G4double fCollimatorLength;
    G4double fCollimatorWidth;
    G4double fCollimatorHeight;
    
    G4LogicalVolume* fCollimatorLogicL;
    G4LogicalVolume* fCollimatorLogicR;
    G4LogicalVolume* fCollimatorEnvelopeLogic[64];
    G4VPhysicalVolume* fCollimatorEnvelopePhysical;

    // Collimator support
private:
    G4bool bCollimatorSupport;
    G4Material *fCollimatorSupportMaterial;

    G4double fCollimatorSupportA0B0Width;
    G4double fCollimatorSupportA0B0Height;

    G4double fCollimatorSupportA0B1Width;
    G4double fCollimatorSupportA0B1Distance;

    G4double fCollimatorSupportA1B0Length;

    G4double fCollimatorSupportA1B1Width;

    G4LogicalVolume* fCollimatorSupportLogic;

    G4VPhysicalVolume* fCollimatorSupportA0Physical;
    G4VPhysicalVolume* fCollimatorA0Physical;
    G4VPhysicalVolume* fCollimatorA1Physical;
    
    //Girders and Pedestals
private:
    G4double fGirderHeight;
    G4double fGirderWidth;
    G4double fGirderThickness;
    G4double fGirderJointLength;
    G4double fPedestalHeight;
    G4double fPedestalWidth;
    G4double fPedestalLength;
    G4double fPedestalThickness;
    G4double fGirderY;
    G4double fPedestalY;
    G4double fM27AGirderLength;
    G4double fM30GirderLength;
    G4double fM31GirderLength;
    G4double fM27ADistance;
    G4double fM30Distance;  
    G4double fM31Distance;
    G4double fM32Distance;
    G4double fM33Distance;
    G4double fM34Distance;
    
    G4double fM27AMagnetWidth;
    G4double fM27AMagnetHeight;
    G4double fM27AMagnetLength;
    G4double fM27AMagnetPoleWidth;
    G4double fM27AMagnetPoleHeight;
    G4double fM27AMagnetCoilWidth;
    G4double fM27AMagnetCoilHeight;
	G4double fM27AMagnetCoilLength;
	G4double fM27AMagnetCoilThickness;
	
	G4double fM34MagnetRadius;
	G4double fM34MagnetInnerRadius;
    G4double fM34MagnetOuterRadius;
    G4double fM34MagnetHeight;
    G4double fM34MagnetThetaStart;
    G4double fM34MagnetThetaEnd;
    G4double fM34MagnetCoilHeight;
    G4double fM34MagnetCoilThickness; 
	G4double fM34MagnetCoilThetaStart;
    G4double fM34MagnetCoilThetaEnd;
    G4double fM34MagnetCoilHoleThetaStart;
    G4double fM34MagnetCoilHoleThetaEnd;
    
    G4double fThetaElectron;
    G4double fThetaM34;

    G4double fM32GirderLength;
    G4double fM32X;    
    G4double fM33GirderLength;
    G4double fM33X;
    G4double fM34GirderLength;
    G4double fM34X; 
       
    G4double fCSPECInnerRadius;
    G4double fCSPECOuterRadius;
    G4double fCSPECLength;
    G4double fCSPECWindowLength;
        
    G4Material* fGirderMaterial;
    G4Material* fPedestalMaterial;
    G4Material* fPedestalInsideMaterial;
    G4Material* fMagnetMaterial;
    G4Material* fCoilMaterial;
   
    	G4LogicalVolume* fGirderJointLogic;
   		G4LogicalVolume* fPedestalLogic;
   		G4LogicalVolume* fPedestalInsideLogic;
    	G4LogicalVolume* fM30GirderLogic;
        G4LogicalVolume* fM31GirderLogic;
        G4LogicalVolume* fM27AGirderLogic;
        G4LogicalVolume* fM32GirderLogic;
        G4LogicalVolume* fM32Logic;        
        G4LogicalVolume* fM33GirderLogic;
        G4LogicalVolume* fM33Logic;
        G4LogicalVolume* fM34GirderLogic;
        G4LogicalVolume* fM34Logic;       
         
        G4LogicalVolume* fCSPECLogic;
        G4LogicalVolume* fCSPECWindowLogic;   
        
        G4LogicalVolume* fM27AMagnetLogic;    
        G4LogicalVolume* fM27AMagnetBaseLogic; 
        G4LogicalVolume* fM27AMagnetCoilLogic;  
        
        G4LogicalVolume* fM34MagnetLogic;
        G4LogicalVolume* fM34MagnetCoilLogic;
        
        G4VPhysicalVolume* fM30LGirderPhysical;
        G4VPhysicalVolume* fM30RGirderPhysical;
        G4VPhysicalVolume* fM31LGirderPhysical;
        G4VPhysicalVolume* fM31RGirderPhysical;
        G4VPhysicalVolume* fM27ALGirderPhysical;
        G4VPhysicalVolume* fM27ARGirderPhysical;
        G4VPhysicalVolume* fM32LGirderPhysical;
        G4VPhysicalVolume* fM32RGirderPhysical;
        G4VPhysicalVolume* fM33LGirderPhysical;
        G4VPhysicalVolume* fM33RGirderPhysical;
        G4VPhysicalVolume* fM34LGirderPhysical;
        G4VPhysicalVolume* fM34RGirderPhysical;   
                            
        G4VPhysicalVolume* fCSPECPhysical;
        G4VPhysicalVolume* fCSPECWindow0Physical;
        G4VPhysicalVolume* fCSPECWindow1Physical;
        G4VPhysicalVolume* fPbDiskM30Physical;
                
        G4VPhysicalVolume* fM30Joint1Physical;
        G4VPhysicalVolume* fM30Joint2Physical;
        G4VPhysicalVolume* fM31Joint1Physical;
        G4VPhysicalVolume* fM31Joint2Physical;
        G4VPhysicalVolume* fM27AJoint1Physical;
        G4VPhysicalVolume* fM27AJoint2Physical;
        G4VPhysicalVolume* fM32Joint1Physical;
        G4VPhysicalVolume* fM32Joint2Physical;
        G4VPhysicalVolume* fM33Joint1Physical;
        G4VPhysicalVolume* fM33Joint2Physical;   
        G4VPhysicalVolume* fM34Joint1Physical;
        G4VPhysicalVolume* fM34Joint2Physical;        
                   
        G4VPhysicalVolume* fM30Pedestal1Physical;
        G4VPhysicalVolume* fM30Pedestal1InsidePhysical;
        G4VPhysicalVolume* fM30Pedestal2Physical;
        G4VPhysicalVolume* fM30Pedestal2InsidePhysical;
        G4VPhysicalVolume* fM31Pedestal1Physical;
        G4VPhysicalVolume* fM31Pedestal1InsidePhysical;
        G4VPhysicalVolume* fM31Pedestal2Physical;
        G4VPhysicalVolume* fM31Pedestal2InsidePhysical;
        G4VPhysicalVolume* fM27APedestal1Physical;
        G4VPhysicalVolume* fM27APedestal1InsidePhysical;
        G4VPhysicalVolume* fM27APedestal2Physical; 
        G4VPhysicalVolume* fM27APedestal2InsidePhysical;
        G4VPhysicalVolume* fM32Pedestal1Physical;
        G4VPhysicalVolume* fM32Pedestal1InsidePhysical; 
        G4VPhysicalVolume* fM32Pedestal2Physical; 
        G4VPhysicalVolume* fM32Pedestal2InsidePhysical;  
        G4VPhysicalVolume* fM32Physical;        
        G4VPhysicalVolume* fM33Pedestal1Physical;
        G4VPhysicalVolume* fM33Pedestal1InsidePhysical; 
        G4VPhysicalVolume* fM33Pedestal2Physical; 
        G4VPhysicalVolume* fM33Pedestal2InsidePhysical;  
        G4VPhysicalVolume* fM33Physical;
        G4VPhysicalVolume* fM34Pedestal1Physical;
        G4VPhysicalVolume* fM34Pedestal1InsidePhysical; 
        G4VPhysicalVolume* fM34Pedestal2Physical; 
        G4VPhysicalVolume* fM34Pedestal2InsidePhysical;  
        G4VPhysicalVolume* fM34Physical;
        
        G4VPhysicalVolume* fM27AMagnetPhysical;
        G4VPhysicalVolume* fM27AMagnetBasePhysical;
        G4VPhysicalVolume* fM27AMagnetCoilTopPhysical;
        G4VPhysicalVolume* fM27AMagnetCoilBottomPhysical;
        
        G4VPhysicalVolume* fM34MagnetPhysical;
        G4VPhysicalVolume* fM34MagnetCoilTopPhysical;
        G4VPhysicalVolume* fM34MagnetCoilBottomPhysical;
                   
    // Transparent detector
private:
    G4bool bTransparentDetector;
    G4LogicalVolume* fTransparentDetectorLogic;
    G4LogicalVolume* fTransparentDetectorBoxLogic;
       
        G4VPhysicalVolume* fTransparentDetectorBoxPhysical;
    
    G4double fTransparentDetectorWidth;
    G4double fTransparentDetectorHeight;
    G4double fTransparentDetectorLength;
    
    	G4LogicalVolume* fTransparentDetectorRack1Logic;
   		G4LogicalVolume* fTransparentDetectorRack2Logic;

        G4VPhysicalVolume* fTransparentDetectorPhysical;

    //G4Solid* fBeamPipeHoleSolid;
    //G4LogicalVolume* fBeamPipeHoleLogic;
      
    //Detector racks //Variables Added
	G4double fTransparentRackWidth;
	G4double fTransparentRackLength;
	G4double fTransparentRackHeight;
	
        G4VPhysicalVolume* fTransparentDetectorRack1Physical;
		G4VPhysicalVolume* fTransparentDetectorRack2Physical;

	G4double fRack1PositionX;
    G4double fRack1PositionY;
    G4double fRack1PositionZ;
    
    G4double fRack2PositionX;
    G4double fRack2PositionY;
    G4double fRack2PositionZ;
    
    
    // Transparent detector
public:
    void SetPbDisks(G4int pbdisks) {PbDisks = pbdisks;};
    
private:
    G4int PbDisks;
    
    G4VPhysicalVolume* fPbDiskPhysical;
    
    G4double fPbDiskLength;
    G4double fPbDiskOuterRadius;
    
    G4double fPbDiskA0Distance;
    G4double fPbDiskA1Distance;
    
    G4Material* fPbDiskMaterial;
};


