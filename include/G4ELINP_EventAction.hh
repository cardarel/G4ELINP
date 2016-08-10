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
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef G4ELINP_EventAction_h
#define G4ELINP_EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include <iostream>
#include <fstream>
#include <map>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4ELINP_EventActionMessenger;

class G4ELINP_EventAction : public G4UserEventAction
{
public:
	G4ELINP_EventAction();
	virtual ~G4ELINP_EventAction();

	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event*);
    
private:
	G4int fG4ELINP_SensitiveDetector_ID;
    G4int fVerboseLevel;
    G4bool newEvent;
    std::map<G4int,G4int> fInteractionNumber;

public:
	inline void SetVerbose(G4int val) {fVerboseLevel = val;}
	inline G4int GetVerbose() const {return fVerboseLevel;}
	G4bool SetNewEventFlag() {newEvent = false;}
	G4bool GetNewEventFlag() {return newEvent;}
	void SetInteractionNumber(G4int key, G4int number) {fInteractionNumber[key] = number;}
	G4int GetInteractionNumber(G4int key) {return fInteractionNumber[key];}
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
