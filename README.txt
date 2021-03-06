######################################################################################

									G4ELINP 

	The code allows simulating the ELINP beam-line. Both the High-Energy line and 
the Low-Energy line can be considered. All the main (massive) elements of 
the beam-line are modeled. In particular, the chamber housing the collimation system 
is modeled in detail.
	The photon source can be chosen between a GPS beam settable via the Geant4 
built-in commands and the phase-space file obtained through a proper simulation of 
the collisions between accelerated electrons and laser photons.  
	The physics list comprises the most precise models for electromagnetic 
and hadronic processes. Modular physics lists can be set via UI commands.
	The scoring is performed by recording the hits on sensitive detectors represented 
by transparent screens with a proper cross section positioned in hot positions. 
Dose scorers are also defined.
	
######################################################################################

							   setup instructions

- Create a directory that will contain both source and compiled files of G4ELINP
- Download the file G4ELINP.tar.gz from https://github.com/cardarel/G4ELINP
- Untar it and put the directory G4ELINP in the directory created just before
- Create the directory G4ELINP-build
- Move into this directory
- Build the project: cmake path_to_geant4_install_directory path_to_G4ELINP/G4ELINP
- Complile the source files of G4ELINP: make -jNcores
- run g4elinp in interactive mode: ./g4elinp 
- the macro intrun.mac can be launched from the UI (/control/execute/ intrun.mac)

  This procedure can be done automatically through the attached script G4ELINP_setup.sh
  
#######################################################################################

						Second Release (Gian, June - July 2016)

- Changed geometry of the collimation chamber according to the new design
- Changed messenger class accordingly
- Updated the overall beamline geometry
- Improved the code and its appearance (indentation, comments, ...)
- Changed name ELIMED -> ELINP (everywhere)
- Introduced mac init.mac, which starts automatically in interactive mode
- Improved vis.mac
- Introduced a setup script
- Introduced vTrack->SetTrackStatus(fStopAndKill) in G4ELINP_SensitiveDetector.cc 
  to avoid retracking the same particle in case of scattering and created SDmessenger
  class to enable this feature via macro  
- fixed the problem of "core dumped" when launch a macro from UI
- introduced new methods of DetConstruction for Getting scoring and Sensitive Volumes
- introduced SteppingAction for setting interactions ntuple (July 2016)
- introduced the capability of changing the Dose Scoring Volume by macro (July 2016)
- introduced the capability of changing the Sensitive Volume by macro (July 2016)

######################################################################################

