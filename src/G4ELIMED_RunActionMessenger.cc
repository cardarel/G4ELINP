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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4ELIMED_RunActionMessenger.hh"

#include "G4ELIMED_RunAction.hh"
#include "G4UIcmdWithAString.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ELIMED_RunActionMessenger::G4ELIMED_RunActionMessenger(G4ELIMED_RunAction* runaction)
:G4UImessenger(),
fSetFileNameCmd(0){
    fRunAction = runaction;
    
    fSetFileNameCmd = new G4UIcmdWithAString("/run/setfilenamesave",this);
    fSetFileNameCmd->SetGuidance("Set File Name Save.");
    fSetFileNameCmd->SetParameterName("SetFileNameSave",false);
    fSetFileNameCmd->SetDefaultValue("G4ELIMED");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ELIMED_RunActionMessenger::~G4ELIMED_RunActionMessenger(){

    delete fSetFileNameCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4ELIMED_RunActionMessenger::SetNewValue(G4UIcommand* command,G4String newValue){
    if(command == fSetFileNameCmd){
        fRunAction->SetFileName(newValue);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
