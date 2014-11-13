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
/// \file analysis//src/G4ELIMED_EventAction.cc
/// \brief Implementation of the G4ELIMED_EventAction class
//
// $Id$
// --------------------------------------------------------------
//

#include "G4ELIMED_EventAction.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

#include "G4ELIMED_SensitiveDetectorHit.hh"

#include "G4ELIMED_TrackingAction.hh"
#include "G4ELIMED_Analysis.hh"

G4ELIMED_EventAction::G4ELIMED_EventAction(){
    fG4ELIMED_SensitiveDetector_ID = -1;
    fVerboseLevel = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4ELIMED_EventAction::~G4ELIMED_EventAction(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void G4ELIMED_EventAction::BeginOfEventAction(const G4Event*){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void G4ELIMED_EventAction::EndOfEventAction(const G4Event* aEvent){
    
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    
    
    //Hit Detection System
    if(fG4ELIMED_SensitiveDetector_ID==-1) {
        G4String G4ELIMED_SensitiveDetectorName;
        if(SDman->FindSensitiveDetector(G4ELIMED_SensitiveDetectorName="det",0)){
            fG4ELIMED_SensitiveDetector_ID = SDman->GetCollectionID(G4ELIMED_SensitiveDetectorName="det/collection");
        }
    }
    
    G4ELIMED_SensitiveDetectorHitsCollection* fG4ELIMED_SensitiveDetector = 0;
    G4HCofThisEvent * HCE = aEvent->GetHCofThisEvent();
    
    if(HCE)
    {
        if(fG4ELIMED_SensitiveDetector_ID != -1){
            G4VHitsCollection* aHCBeamPipe = HCE->GetHC(fG4ELIMED_SensitiveDetector_ID);
            fG4ELIMED_SensitiveDetector = (G4ELIMED_SensitiveDetectorHitsCollection*)(aHCBeamPipe);
        }
    }
    
    
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    
    if(fG4ELIMED_SensitiveDetector){
        int vNumberOfHitBeamPipe = fG4ELIMED_SensitiveDetector->entries();
        for(int i=0;i<vNumberOfHitBeamPipe;i++){
            G4ELIMED_SensitiveDetectorHit* aHitBP = (*fG4ELIMED_SensitiveDetector)[i];
            analysisManager->FillNtupleDColumn(0,0, aHitBP->GetEnergy() / CLHEP::MeV);
            analysisManager->FillNtupleDColumn(0,1, aHitBP->GetEnergyPrevious() / CLHEP::MeV);
            analysisManager->FillNtupleDColumn(0,2, aHitBP->GetPos().x() / CLHEP::mm);
            analysisManager->FillNtupleDColumn(0,3, aHitBP->GetPos().y() / CLHEP::mm);
            analysisManager->FillNtupleDColumn(0,4, aHitBP->GetPos().z() / CLHEP::mm);
            analysisManager->FillNtupleDColumn(0,5, aHitBP->GetMom().x() / CLHEP::MeV);
            analysisManager->FillNtupleDColumn(0,6, aHitBP->GetMom().y() / CLHEP::MeV);
            analysisManager->FillNtupleDColumn(0,7, aHitBP->GetMom().z() / CLHEP::MeV);
            analysisManager->FillNtupleDColumn(0,8, aHitBP->GetTime() / CLHEP::ns);
            analysisManager->FillNtupleIColumn(0,9, aHitBP->GetType());
            analysisManager->FillNtupleIColumn(0,10, aHitBP->GetZ());
            analysisManager->FillNtupleIColumn(0,11, aHitBP->GetA());
            analysisManager->FillNtupleIColumn(0,12, aHitBP->GetZP());
            analysisManager->FillNtupleIColumn(0,13, aHitBP->GetAP());
            analysisManager->FillNtupleIColumn(0,14, aHitBP->GetTrackID());
            analysisManager->FillNtupleIColumn(0,15, aHitBP->GetTrackIDP());
            analysisManager->AddNtupleRow(0);
            
        }
    }
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
