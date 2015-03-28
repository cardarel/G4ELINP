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
/// \file analysis//include/G4ELIMED_DetectorConstructionMessenger.hh
/// \brief Definition of the G4ELIMED_DetectorConstructionMessenger class
//
// $Id$
// --------------------------------------------------------------
//
#ifndef G4ELIMED_DetectorConstructionMessenger_h
#define G4ELIMED_DetectorConstructionMessenger_h 1

class G4ELIMED_DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcmdWith3VectorAndUnit;

#include "G4UImessenger.hh"
#include "globals.hh"

class G4ELIMED_DetectorConstructionMessenger: public G4UImessenger
{
  public:
    G4ELIMED_DetectorConstructionMessenger(G4ELIMED_DetectorConstruction* mpga);
    ~G4ELIMED_DetectorConstructionMessenger();

    virtual void SetNewValue(G4UIcommand * command,G4String newValues);
    virtual G4String GetCurrentValue(G4UIcommand * command);

  private:
    G4ELIMED_DetectorConstruction * fDetectorTarget;
    
    G4UIdirectory* fCollimatorDir;

    G4UIcmdWith3VectorAndUnit* fRomanPotSupportAngleCmd;
    G4UIcmdWith3VectorAndUnit* fRomanPotSupportPositionCmd;
    G4UIcmdWithADoubleAndUnit* fCollimatorApertureCmd;

    G4UIcmdWithADoubleAndUnit* fCollimatorDistanceCmd;
    G4UIcmdWithAnInteger* fCollimatorNumberCmd;

    G4UIcmdWithAnInteger* fCollimatorRandDisplCmd;
    G4UIcmdWithADoubleAndUnit* fCollimatorRandDisplMeanCmd;
    G4UIcmdWithADoubleAndUnit* fCollimatorRandDisplSigmaCmd;

    G4UIcmdWithADoubleAndUnit* fCollimatorSingleDisplMeanCmd[64];

    G4UIcmdWithAnInteger* fCollimatorSetupCmd;
    
    G4UIcmdWithAnInteger* fPbDisksCmd;
      
    G4UIcmdWithAnInteger* fModulesOnCmd;
    

};

#endif


