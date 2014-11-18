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

private:
    G4ThreeVector fRomanPotSupportAngle;

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

