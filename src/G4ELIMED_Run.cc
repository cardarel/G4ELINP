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
// $Id: G4ELIMED_Run.cc 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file G4ELIMED_Run.cc
/// \brief Implementation of the G4ELIMED_Run class

#include "G4ELIMED_Run.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"

#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4THitsMap.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ELIMED_Run::G4ELIMED_Run()
 : G4Run(), 
   fCollID_dose(-1),
   fPrintModulo(10000),
   fGoodEvents(0),
   fSumDose(0.)
{ }


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ELIMED_Run::~G4ELIMED_Run()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4ELIMED_Run::RecordEvent(const G4Event* event)
{

    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    
    
    //Hit Detection System
   
  if ( fCollID_dose < 0 ) {
  G4String G4ELIMED_SensitiveDetectorName;
        if(SDman->FindSensitiveDetector(G4ELIMED_SensitiveDetectorName="multisd/dose",0)){
           fCollID_dose  =  SDman->GetCollectionID(G4ELIMED_SensitiveDetectorName="det/collection");
        }
       }

        if(fCollID_dose > 0)   {      
  //Hits collections
  //  
  G4HCofThisEvent* HCE = event->GetHCofThisEvent();
  if(!HCE) return;
               
  G4THitsMap<G4double>* evtMap = 
    static_cast<G4THitsMap<G4double>*>(HCE->GetHC(fCollID_dose));
               
  std::map<G4int,G4double*>::iterator itr;
  
  //Dose deposit in patient
  //
  G4double dose = 0.;
               
  for (itr = evtMap->GetMap()->begin(); itr != evtMap->GetMap()->end(); itr++) {
    dose = *(itr->second);
  }
  fSumDose += dose;
  }
  G4Run::RecordEvent(event);      
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4ELIMED_Run::Merge(const G4Run* aRun)
{
  const G4ELIMED_Run* localRun = static_cast<const G4ELIMED_Run*>(aRun);
  fGoodEvents += localRun->fGoodEvents;
  fSumDose    += localRun->fSumDose;

  G4Run::Merge(aRun); 
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
