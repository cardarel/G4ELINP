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
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
#include "G4ScoringManager.hh"
#include "G4UImanager.hh"

#include "Randomize.hh"

#include "G4ELIMED_DetectorConstruction.hh"
#include "G4ELIMED_PhysicsList.hh"

#ifdef G4MULTITHREADED
#include "G4ELIMED_UserActionInitialization.hh"
#else
#include "G4ELIMED_PrimaryGeneratorAction.hh"
#include "G4ELIMED_TrackingAction.hh"
#include "G4ELIMED_StackingAction.hh"
#include "G4ELIMED_RunAction.hh"
#include "G4ELIMED_EventAction.hh"
#endif

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include <sys/time.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// 1 nanoAmpere -> Number of Particles/s = 1.E-9 Ampere / 1.602176565E-19 Coulombs = 6.24150934326017952E9
// Normalize to 200000000 particles -> 6.24150934326017952E9/200000000 = 3.12075467163008966E1
// Nuclear cross section = http://en.wikipedia.org/wiki/Nuclear_cross_section

int main(int argc,char** argv)
{
    struct timeval start,end;
    gettimeofday(&start,NULL);
    
    // Construct the default run manager
#ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
    int vNumberOfThreads = 32;
    if(argv[2]){
        vNumberOfThreads = atoi(argv[2]);
    };
    if(vNumberOfThreads > 0){
        runManager->SetNumberOfThreads(vNumberOfThreads);
    }
    G4cout << "MT MODE ON " << runManager->GetNumberOfThreads() << G4endl;
#else
    G4RunManager* runManager = new G4RunManager;
    G4cout << "MT MODE OFF" << G4endl;
#endif
    
    // Activate UI-command base scorer
    G4ScoringManager * scManager = G4ScoringManager::GetScoringManager();
    scManager->SetVerboseLevel(0);
    
    // Choose the Random engine
#ifndef G4MULTITHREADED
    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    G4int seed = 0;
    G4Random::setTheSeed( seed );
#endif
    
    // Set mandatory initialization classes
    runManager->SetUserInitialization(new G4ELIMED_DetectorConstruction);
    runManager->SetUserInitialization(new G4ELIMED_PhysicsList());
    
#ifndef G4MULTITHREADED
    // Set user action classes
    runManager->SetUserAction(new G4ELIMED_PrimaryGeneratorAction());
    runManager->SetUserAction(new G4ELIMED_EventAction());
    runManager->SetUserAction(new G4ELIMED_RunAction());
    runManager->SetUserAction(new G4ELIMED_StackingAction());
    runManager->SetUserAction(new G4ELIMED_TrackingAction());
#else
    runManager->SetUserInitialization(new G4ELIMED_UserActionInitialization());
#endif
    
    // Get the pointer to the User Interface manager
    G4UImanager* UI = G4UImanager::GetUIpointer();
    
    if(argc!=1) {
        // Batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UI->ApplyCommand(command+fileName);
    }
    
    else {
        // Define visualization and UI terminal for interactive mode
#ifdef G4VIS_USE
        G4VisManager* visManager = new G4VisExecutive;
        visManager->Initialize();
#endif
        
#ifdef G4UI_USE
        G4UIExecutive * ui = new G4UIExecutive(argc,argv);
        ui->SessionStart();
        delete ui;
#endif
        
#ifdef G4VIS_USE
        delete visManager;
#endif
    }
    
    // Job termination
    delete runManager;
    
    gettimeofday(&end,NULL);
    std::cout << "Elapsed time [s] = " << ((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec))/1.E6 << std::endl;
    
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
