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
/// \file analysis//src/G4ELIMED_SensitiveDetector.cc
/// \brief Implementation of the G4ELIMED_SensitiveDetector class
//
// $Id$
// --------------------------------------------------------------
//
#include "G4ELIMED_SensitiveDetector.hh"
#include "G4ELIMED_SensitiveDetectorHit.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4Navigator.hh"
#include "G4ios.hh"

G4ELIMED_SensitiveDetector::G4ELIMED_SensitiveDetector(G4String name):G4VSensitiveDetector(name)
{
    G4String HCname;
    collectionName.insert(HCname="collection");
    fHCID = -1;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4ELIMED_SensitiveDetector::~G4ELIMED_SensitiveDetector(){
    ;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void G4ELIMED_SensitiveDetector::Initialize(G4HCofThisEvent*HCE)
{
    fHitsCollection = new G4ELIMED_SensitiveDetectorHitsCollection(SensitiveDetectorName,collectionName[0]);
    if(fHCID<0){
        fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    }
    HCE->AddHitsCollection(fHCID,fHitsCollection);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

bool G4ELIMED_SensitiveDetector::ProcessHits(G4Step *aStep,G4TouchableHistory* /*ROhist*/){
    
    G4Track* vTrack = aStep->GetTrack();
    
    G4StepPoint* preStepPoint = aStep->GetPreStepPoint();

    std::map<int,int>::const_iterator it = fAParent.find(vTrack->GetTrackID());
    if(it==fAParent.end()){
        fAParent[vTrack->GetTrackID()] = vTrack->GetDefinition()->GetAtomicMass();
        fZParent[vTrack->GetTrackID()] = vTrack->GetDefinition()->GetAtomicNumber();
    }
    
    if(!(preStepPoint->GetStepStatus() == fGeomBoundary)){
        fEnParent = preStepPoint->GetKineticEnergy();
        return true;
    }
    
    G4ThreeVector pos = preStepPoint->GetPosition();
    G4ThreeVector mom = preStepPoint->GetMomentum();
    
    G4ELIMED_SensitiveDetectorHit* aHit = new G4ELIMED_SensitiveDetectorHit();

    aHit->SetMom(mom);
    aHit->SetPos(pos);
    aHit->SetTime(preStepPoint->GetGlobalTime());
    aHit->SetEnergy(preStepPoint->GetKineticEnergy());
    
 
    G4int vType = -1;
    if(preStepPoint->GetMass() == 0 &&
       preStepPoint->GetCharge() == 0){
        vType = 0;
    }
    else if(preStepPoint->GetMass() != 0 &&
            preStepPoint->GetCharge() == 0){
        vType = 1;
    }
    else if(preStepPoint->GetMass() != 0 &&
            preStepPoint->GetCharge() > 0){
        vType = 2;
    }
    else if(preStepPoint->GetMass() != 0 &&
            preStepPoint->GetCharge() < 0){
        vType = 3;
    }
    
    if(vTrack->GetTrackID() == 1 ){
        aHit->SetAP(-1);
        aHit->SetZP(-1);
    }
    else{
        it = fAParent.find(vTrack->GetParentID());
        if(it==fAParent.end()){
            aHit->SetAP(-2);
            aHit->SetZP(-2);
        }
        else{
            aHit->SetAP(fAParent[vTrack->GetParentID()]);
            aHit->SetZP(fZParent[vTrack->GetParentID()]);
        }
    }
    
    aHit->SetTrackID(vTrack->GetTrackID());
    aHit->SetTrackIDP(vTrack->GetParentID());
    
    aHit->SetType(vType);

    aHit->SetA(vTrack->GetDefinition()->GetAtomicMass());
    aHit->SetZ(vTrack->GetDefinition()->GetAtomicNumber());

    fHitsCollection->insert(aHit);
    
    fEnParent = preStepPoint->GetKineticEnergy();

    return true;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void G4ELIMED_SensitiveDetector::EndOfEvent(G4HCofThisEvent* /*HCE*/)
{
    ;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
