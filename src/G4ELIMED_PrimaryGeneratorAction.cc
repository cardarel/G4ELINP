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
// $Id: PrimaryGeneratorAction.cc,v 1.1 2010-10-18 15:56:17 maire Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4ELIMED_PrimaryGeneratorAction.hh"
#include "G4ELIMED_FileReader.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4AutoLock.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"

#include "G4GeneralParticleSource.hh"
#include "G4ParticleGun.hh"

namespace { G4Mutex G4ELIMED_PrimaryGeneratorActionMutex = G4MUTEX_INITIALIZER; }
G4ELIMED_FileReader* G4ELIMED_PrimaryGeneratorAction::fFileReader = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ELIMED_PrimaryGeneratorAction::G4ELIMED_PrimaryGeneratorAction()
{
    G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
    
    fParticleGPS = new G4GeneralParticleSource();
    
    fParticleGPS->SetParticleDefinition(particle);

    fMessenger = new G4ELIMED_PrimaryGeneratorActionMessenger(this);
    //fReadFromFile = false;
    // Position distribution
    G4SPSPosDistribution *vPosDist = fParticleGPS->GetCurrentSource()->GetPosDist() ;
    vPosDist->SetPosDisType("Beam");
    vPosDist->SetPosDisShape("Circle");
    vPosDist->SetBeamSigmaInR(0.01 * CLHEP::mm);

    // Angular distribution
    G4SPSAngDistribution *vAngDist = fParticleGPS->GetCurrentSource()->GetAngDist() ;
    vAngDist->SetBeamSigmaInAngR(0.);
    vAngDist->SetAngDistType("beam1d");
    vAngDist->SetParticleMomentumDirection(G4ThreeVector(0.,0.,-1.));
    
    // Energy distribution
    G4SPSEneDistribution *vEneDist = fParticleGPS->GetCurrentSource()->GetEneDist() ;
    vEneDist->SetEnergyDisType("Mono");
    vEneDist->SetMonoEnergy(5. * CLHEP::MeV);
    
    
//    G4AutoLock lock(&G4ELIMED_PrimaryGeneratorActionMutex);
//    // Read From File
//    fFileName = "/home/ebagli/DATA/ELIMED/LE_5.0MeV/photons20000.dat";
//    
//    if(!fFileReader){
//        fFileReader = new G4ELIMED_FileReader(fFileName);
//        if(fReadFromFile){
//            fFileReader->StoreEvents();
//        }
//    }

    fParticleGun = new G4ParticleGun();
    fParticleGun->SetParticleDefinition(particle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ELIMED_PrimaryGeneratorAction::~G4ELIMED_PrimaryGeneratorAction(){
    G4AutoLock lock(&G4ELIMED_PrimaryGeneratorActionMutex);
    if(fFileReader){
        delete fFileReader;
        fFileReader = 0;
    }
    delete fParticleGun;
    delete fParticleGPS;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4ELIMED_PrimaryGeneratorAction::SetFileName(G4String vFileName){
    fFileName = vFileName;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void G4ELIMED_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
    G4AutoLock lock(&G4ELIMED_PrimaryGeneratorActionMutex);
    
    if(!fFileReader){
        fFileReader = new G4ELIMED_FileReader(fFileName);
        if(fReadFromFile){
            G4cout << "Read file ..." << G4endl;
            fFileReader->StoreEvents();
            G4cout << "... file readed" << G4endl;
        }
    }
    
    if(fReadFromFile){
        fParticleGun->SetParticlePosition(fFileReader->GetAnEventPosition(anEvent->GetEventID()));
        fParticleGun->SetParticleMomentumDirection(fFileReader->GetAnEventMomentum(anEvent->GetEventID()).unit());
        fParticleGun->SetParticleEnergy(fFileReader->GetAnEventEnergy(anEvent->GetEventID()));
                
        fParticleGun->GeneratePrimaryVertex(anEvent);
    }
    else{
        fParticleGPS->GeneratePrimaryVertex(anEvent);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

