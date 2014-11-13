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

#include "G4ELIMED_RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "G4ELIMED_RunActionMessenger.hh"
#include "G4ELIMED_Analysis.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ELIMED_RunAction::G4ELIMED_RunAction():
G4UserRunAction(),
fMessenger(0){
    G4RunManager::GetRunManager()->SetPrintProgress(1000);
    
    fMessenger = new G4ELIMED_RunActionMessenger(this);
    fFileName = "G4ELIMED";
    
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    G4cout << "Using " << analysisManager->GetType() << G4endl;
    
    // Creating ntuples
    analysisManager->CreateNtuple("part","Particle");
    analysisManager->CreateNtupleDColumn("e");
    analysisManager->CreateNtupleDColumn("eP");
    analysisManager->CreateNtupleDColumn("posx");
    analysisManager->CreateNtupleDColumn("posy");
    analysisManager->CreateNtupleDColumn("posz");
    analysisManager->CreateNtupleDColumn("momx");
    analysisManager->CreateNtupleDColumn("momy");
    analysisManager->CreateNtupleDColumn("momz");
    analysisManager->CreateNtupleDColumn("t");
    analysisManager->CreateNtupleIColumn("type");
    analysisManager->CreateNtupleIColumn("Z");
    analysisManager->CreateNtupleIColumn("A");
    analysisManager->CreateNtupleIColumn("ZP");
    analysisManager->CreateNtupleIColumn("AP");
    analysisManager->CreateNtupleIColumn("trackID");
    analysisManager->CreateNtupleIColumn("trackIDP");
    analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ELIMED_RunAction::~G4ELIMED_RunAction(){
    delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4ELIMED_RunAction::BeginOfRunAction(const G4Run* /*run*/){
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile(fFileName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4ELIMED_RunAction::EndOfRunAction(const G4Run* /*run*/){
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();    
    analysisManager->Write();
    analysisManager->CloseFile();
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4ELIMED_RunAction::SetFileName(G4String filename){
    if(filename != ""){
        fFileName = filename;
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
