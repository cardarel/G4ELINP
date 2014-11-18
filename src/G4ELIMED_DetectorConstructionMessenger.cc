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
/// \file analysis//src/G4ELIMED_DetectorConstructionMessenger.cc
/// \brief Implementation of the G4ELIMED_DetectorConstructionMessenger class
//
// $Id$
// --------------------------------------------------------------
//
#include "G4ELIMED_DetectorConstructionMessenger.hh"
#include "G4ELIMED_DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4RunManager.hh"

#include "G4ios.hh"

G4ELIMED_DetectorConstructionMessenger::G4ELIMED_DetectorConstructionMessenger(G4ELIMED_DetectorConstruction* mpga)
:fDetectorTarget(mpga)
{
    fCollimatorDir = new G4UIdirectory("/collimator/");
    fCollimatorDir->SetGuidance("Detector Control.");
    
    fCollimatorNumberCmd = new G4UIcmdWithAnInteger("/collimator/setNumber",this);
    fCollimatorNumberCmd->SetGuidance("Set collimator number.");
    fCollimatorNumberCmd->SetParameterName("number",false);
    fCollimatorNumberCmd->SetRange("number>=0");
    fCollimatorNumberCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fCollimatorDistanceCmd = new G4UIcmdWithADoubleAndUnit("/collimator/setDistance",this);
    fCollimatorDistanceCmd->SetGuidance("Set collimator distance.");
    fCollimatorDistanceCmd->SetParameterName("distance",false);
    fCollimatorDistanceCmd->SetUnitCategory("Length");
    fCollimatorDistanceCmd->SetRange("distance>=0.0");
    fCollimatorDistanceCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fCollimatorApertureCmd = new G4UIcmdWithADoubleAndUnit("/collimator/setAperture",this);
    fCollimatorApertureCmd->SetGuidance("Set collimator aperture.");
    fCollimatorApertureCmd->SetParameterName("aperture",false);
    fCollimatorApertureCmd->SetUnitCategory("Length");
    fCollimatorApertureCmd->SetRange("aperture>0.0");
    fCollimatorApertureCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fRomanPotSupportAngleCmd = new G4UIcmdWith3VectorAndUnit("/collimator/setAngle",this);
    fRomanPotSupportAngleCmd->SetGuidance("Set collimator angle.");
    fRomanPotSupportAngleCmd->SetParameterName("angX","angY","angZ",false);
    fRomanPotSupportAngleCmd->SetUnitCategory("Angle");
    fRomanPotSupportAngleCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    
    fCollimatorSetupCmd = new G4UIcmdWithAnInteger("/line/set",this);
    fCollimatorSetupCmd->SetGuidance("Set line type 0->[1-5] MeV; 1->[5-20] MeV.");
    fCollimatorSetupCmd->SetParameterName("line",false);
    fCollimatorSetupCmd->SetRange("line>=0 && line<=1");
    fCollimatorSetupCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fPbDisksCmd = new G4UIcmdWithAnInteger("/collimator/PbDisks",this);
    fPbDisksCmd->SetGuidance("Set disk 1 (1), disk 2 (2), no disk (0), both disks (3).");
    fPbDisksCmd->SetParameterName("disk",false);
    fPbDisksCmd->SetRange("disk>=0");
    fPbDisksCmd->AvailableForStates(G4State_PreInit,G4State_Idle);


    fCollimatorRandDisplCmd = new G4UIcmdWithAnInteger("/collimator/setRandDispl",this);
    fCollimatorRandDisplCmd->SetGuidance("Set random aperture collimator: (0) no random, (1) uniform, (2) gauss.");
    fCollimatorRandDisplCmd->SetParameterName("randdispl",false);
    fCollimatorRandDisplCmd->SetRange("randdispl>=0");
    fCollimatorRandDisplCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fCollimatorRandDisplMeanCmd = new G4UIcmdWithADoubleAndUnit("/collimator/setRandDisplMean",this);
    fCollimatorRandDisplMeanCmd->SetGuidance("Set random aperture collimator mean.");
    fCollimatorRandDisplMeanCmd->SetParameterName("randmean",false);
    fCollimatorRandDisplMeanCmd->SetUnitCategory("Length");
    fCollimatorRandDisplMeanCmd->SetRange("randmean>=0.0");
    fCollimatorRandDisplMeanCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fCollimatorRandDisplSigmaCmd = new G4UIcmdWithADoubleAndUnit("/collimator/setRandDisplSigma",this);
    fCollimatorRandDisplSigmaCmd->SetGuidance("Set random aperture collimator sigma.");
    fCollimatorRandDisplSigmaCmd->SetParameterName("randsigma",false);
    fCollimatorRandDisplSigmaCmd->SetUnitCategory("Length");
    fCollimatorRandDisplSigmaCmd->SetRange("randsigma>=0.0");
    fCollimatorRandDisplSigmaCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4ELIMED_DetectorConstructionMessenger::~G4ELIMED_DetectorConstructionMessenger()
{
    delete fCollimatorDir;
    delete fCollimatorNumberCmd;
    delete fCollimatorDistanceCmd;
    delete fCollimatorApertureCmd;
    delete fRomanPotSupportAngleCmd;
    delete fCollimatorSetupCmd;
    delete fPbDisksCmd;
    delete fCollimatorRandDisplCmd;
    delete fCollimatorRandDisplMeanCmd;
    delete fCollimatorRandDisplSigmaCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void G4ELIMED_DetectorConstructionMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{
    if( command == fCollimatorNumberCmd )
    { fDetectorTarget->SetCollimatorNumber(fCollimatorNumberCmd->GetNewIntValue(newValue));}
    
    if( command == fCollimatorDistanceCmd )
    { fDetectorTarget->SetCollimatorDistance(fCollimatorDistanceCmd->GetNewDoubleValue(newValue));}
    
    if( command == fCollimatorApertureCmd )
    { fDetectorTarget->SetCollimatorAperture(fCollimatorApertureCmd->GetNewDoubleValue(newValue));}

    if( command == fRomanPotSupportAngleCmd )
    { fDetectorTarget->SetRomanPotSupportAngle(fRomanPotSupportAngleCmd->GetNew3VectorValue(newValue));}


    if( command == fCollimatorSetupCmd )
    { fDetectorTarget->ResetDetectorForSetup(fCollimatorSetupCmd->GetNewIntValue(newValue));}
    
    if( command == fPbDisksCmd )
    { fDetectorTarget->SetPbDisks(fPbDisksCmd->GetNewIntValue(newValue));}

    if( command == fCollimatorRandDisplCmd )
    { fDetectorTarget->SetCollRandDispl(fCollimatorRandDisplCmd->GetNewIntValue(newValue));}
 
    if( command == fCollimatorRandDisplMeanCmd )
    { fDetectorTarget->SetCollRandDisplMean(fCollimatorRandDisplMeanCmd->GetNewDoubleValue(newValue));}

    if( command == fCollimatorRandDisplSigmaCmd )
    { fDetectorTarget->SetCollRandDisplSigma(fCollimatorRandDisplSigmaCmd->GetNewDoubleValue(newValue));}
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4String G4ELIMED_DetectorConstructionMessenger::GetCurrentValue(G4UIcommand * command)
{
    G4String cv;
    
    if(command==fCollimatorNumberCmd ){
        cv = fCollimatorNumberCmd->ConvertToString(fDetectorTarget->GetCollimatorNumber());
    }
    if(command==fCollimatorDistanceCmd ){
        cv = fCollimatorDistanceCmd->ConvertToString(fDetectorTarget->GetCollimatorDistance(),"mm");
    }
    if(command==fCollimatorApertureCmd ){
        cv = fCollimatorApertureCmd->ConvertToString(fDetectorTarget->GetCollimatorAperture(),"mm");
    }
    if(command==fRomanPotSupportAngleCmd ){
        cv = fRomanPotSupportAngleCmd->ConvertToString(fDetectorTarget->GetRomanPotSupportAngle(),"deg");
    }
    
    if(command==fCollimatorRandDisplCmd ){
        cv = fCollimatorRandDisplCmd->ConvertToString(fDetectorTarget->GetCollRandDispl());
    }
    if(command==fCollimatorRandDisplMeanCmd ){
        cv = fCollimatorRandDisplMeanCmd->ConvertToString(fDetectorTarget->GetCollRandDisplMean(),"mm");
    }
    if(command==fCollimatorRandDisplSigmaCmd ){
        cv = fCollimatorRandDisplSigmaCmd->ConvertToString(fDetectorTarget->GetCollRandDisplSigma(),"mm");
    }
    return cv;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....