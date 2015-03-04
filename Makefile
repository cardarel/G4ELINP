# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cardarelli/G4ELINP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cardarelli/G4ELINP

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: install/local
.PHONY : install/local/fast

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: install/strip
.PHONY : install/strip/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components
.PHONY : list_install_components/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/cardarelli/G4ELINP/CMakeFiles /home/cardarelli/G4ELINP/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/cardarelli/G4ELINP/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named G4elimed

# Build rule for target.
G4elimed: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 G4elimed
.PHONY : G4elimed

# fast build rule for target.
G4elimed/fast:
	$(MAKE) -f CMakeFiles/G4elimed.dir/build.make CMakeFiles/G4elimed.dir/build
.PHONY : G4elimed/fast

#=============================================================================
# Target rules for targets named g4elimed

# Build rule for target.
g4elimed: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 g4elimed
.PHONY : g4elimed

# fast build rule for target.
g4elimed/fast:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/build
.PHONY : g4elimed/fast

g4elimed.o: g4elimed.cc.o
.PHONY : g4elimed.o

# target to build an object file
g4elimed.cc.o:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/g4elimed.cc.o
.PHONY : g4elimed.cc.o

g4elimed.i: g4elimed.cc.i
.PHONY : g4elimed.i

# target to preprocess a source file
g4elimed.cc.i:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/g4elimed.cc.i
.PHONY : g4elimed.cc.i

g4elimed.s: g4elimed.cc.s
.PHONY : g4elimed.s

# target to generate assembly for a file
g4elimed.cc.s:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/g4elimed.cc.s
.PHONY : g4elimed.cc.s

src/G4ELIMED_DetectorConstruction.o: src/G4ELIMED_DetectorConstruction.cc.o
.PHONY : src/G4ELIMED_DetectorConstruction.o

# target to build an object file
src/G4ELIMED_DetectorConstruction.cc.o:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_DetectorConstruction.cc.o
.PHONY : src/G4ELIMED_DetectorConstruction.cc.o

src/G4ELIMED_DetectorConstruction.i: src/G4ELIMED_DetectorConstruction.cc.i
.PHONY : src/G4ELIMED_DetectorConstruction.i

# target to preprocess a source file
src/G4ELIMED_DetectorConstruction.cc.i:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_DetectorConstruction.cc.i
.PHONY : src/G4ELIMED_DetectorConstruction.cc.i

src/G4ELIMED_DetectorConstruction.s: src/G4ELIMED_DetectorConstruction.cc.s
.PHONY : src/G4ELIMED_DetectorConstruction.s

# target to generate assembly for a file
src/G4ELIMED_DetectorConstruction.cc.s:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_DetectorConstruction.cc.s
.PHONY : src/G4ELIMED_DetectorConstruction.cc.s

src/G4ELIMED_DetectorConstructionMessenger.o: src/G4ELIMED_DetectorConstructionMessenger.cc.o
.PHONY : src/G4ELIMED_DetectorConstructionMessenger.o

# target to build an object file
src/G4ELIMED_DetectorConstructionMessenger.cc.o:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_DetectorConstructionMessenger.cc.o
.PHONY : src/G4ELIMED_DetectorConstructionMessenger.cc.o

src/G4ELIMED_DetectorConstructionMessenger.i: src/G4ELIMED_DetectorConstructionMessenger.cc.i
.PHONY : src/G4ELIMED_DetectorConstructionMessenger.i

# target to preprocess a source file
src/G4ELIMED_DetectorConstructionMessenger.cc.i:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_DetectorConstructionMessenger.cc.i
.PHONY : src/G4ELIMED_DetectorConstructionMessenger.cc.i

src/G4ELIMED_DetectorConstructionMessenger.s: src/G4ELIMED_DetectorConstructionMessenger.cc.s
.PHONY : src/G4ELIMED_DetectorConstructionMessenger.s

# target to generate assembly for a file
src/G4ELIMED_DetectorConstructionMessenger.cc.s:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_DetectorConstructionMessenger.cc.s
.PHONY : src/G4ELIMED_DetectorConstructionMessenger.cc.s

src/G4ELIMED_EventAction.o: src/G4ELIMED_EventAction.cc.o
.PHONY : src/G4ELIMED_EventAction.o

# target to build an object file
src/G4ELIMED_EventAction.cc.o:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_EventAction.cc.o
.PHONY : src/G4ELIMED_EventAction.cc.o

src/G4ELIMED_EventAction.i: src/G4ELIMED_EventAction.cc.i
.PHONY : src/G4ELIMED_EventAction.i

# target to preprocess a source file
src/G4ELIMED_EventAction.cc.i:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_EventAction.cc.i
.PHONY : src/G4ELIMED_EventAction.cc.i

src/G4ELIMED_EventAction.s: src/G4ELIMED_EventAction.cc.s
.PHONY : src/G4ELIMED_EventAction.s

# target to generate assembly for a file
src/G4ELIMED_EventAction.cc.s:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_EventAction.cc.s
.PHONY : src/G4ELIMED_EventAction.cc.s

src/G4ELIMED_FileReader.o: src/G4ELIMED_FileReader.cc.o
.PHONY : src/G4ELIMED_FileReader.o

# target to build an object file
src/G4ELIMED_FileReader.cc.o:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_FileReader.cc.o
.PHONY : src/G4ELIMED_FileReader.cc.o

src/G4ELIMED_FileReader.i: src/G4ELIMED_FileReader.cc.i
.PHONY : src/G4ELIMED_FileReader.i

# target to preprocess a source file
src/G4ELIMED_FileReader.cc.i:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_FileReader.cc.i
.PHONY : src/G4ELIMED_FileReader.cc.i

src/G4ELIMED_FileReader.s: src/G4ELIMED_FileReader.cc.s
.PHONY : src/G4ELIMED_FileReader.s

# target to generate assembly for a file
src/G4ELIMED_FileReader.cc.s:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_FileReader.cc.s
.PHONY : src/G4ELIMED_FileReader.cc.s

src/G4ELIMED_PhysicsList.o: src/G4ELIMED_PhysicsList.cc.o
.PHONY : src/G4ELIMED_PhysicsList.o

# target to build an object file
src/G4ELIMED_PhysicsList.cc.o:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_PhysicsList.cc.o
.PHONY : src/G4ELIMED_PhysicsList.cc.o

src/G4ELIMED_PhysicsList.i: src/G4ELIMED_PhysicsList.cc.i
.PHONY : src/G4ELIMED_PhysicsList.i

# target to preprocess a source file
src/G4ELIMED_PhysicsList.cc.i:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_PhysicsList.cc.i
.PHONY : src/G4ELIMED_PhysicsList.cc.i

src/G4ELIMED_PhysicsList.s: src/G4ELIMED_PhysicsList.cc.s
.PHONY : src/G4ELIMED_PhysicsList.s

# target to generate assembly for a file
src/G4ELIMED_PhysicsList.cc.s:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_PhysicsList.cc.s
.PHONY : src/G4ELIMED_PhysicsList.cc.s

src/G4ELIMED_PhysicsListMessenger.o: src/G4ELIMED_PhysicsListMessenger.cc.o
.PHONY : src/G4ELIMED_PhysicsListMessenger.o

# target to build an object file
src/G4ELIMED_PhysicsListMessenger.cc.o:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_PhysicsListMessenger.cc.o
.PHONY : src/G4ELIMED_PhysicsListMessenger.cc.o

src/G4ELIMED_PhysicsListMessenger.i: src/G4ELIMED_PhysicsListMessenger.cc.i
.PHONY : src/G4ELIMED_PhysicsListMessenger.i

# target to preprocess a source file
src/G4ELIMED_PhysicsListMessenger.cc.i:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_PhysicsListMessenger.cc.i
.PHONY : src/G4ELIMED_PhysicsListMessenger.cc.i

src/G4ELIMED_PhysicsListMessenger.s: src/G4ELIMED_PhysicsListMessenger.cc.s
.PHONY : src/G4ELIMED_PhysicsListMessenger.s

# target to generate assembly for a file
src/G4ELIMED_PhysicsListMessenger.cc.s:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_PhysicsListMessenger.cc.s
.PHONY : src/G4ELIMED_PhysicsListMessenger.cc.s

src/G4ELIMED_PrimaryGeneratorAction.o: src/G4ELIMED_PrimaryGeneratorAction.cc.o
.PHONY : src/G4ELIMED_PrimaryGeneratorAction.o

# target to build an object file
src/G4ELIMED_PrimaryGeneratorAction.cc.o:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_PrimaryGeneratorAction.cc.o
.PHONY : src/G4ELIMED_PrimaryGeneratorAction.cc.o

src/G4ELIMED_PrimaryGeneratorAction.i: src/G4ELIMED_PrimaryGeneratorAction.cc.i
.PHONY : src/G4ELIMED_PrimaryGeneratorAction.i

# target to preprocess a source file
src/G4ELIMED_PrimaryGeneratorAction.cc.i:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_PrimaryGeneratorAction.cc.i
.PHONY : src/G4ELIMED_PrimaryGeneratorAction.cc.i

src/G4ELIMED_PrimaryGeneratorAction.s: src/G4ELIMED_PrimaryGeneratorAction.cc.s
.PHONY : src/G4ELIMED_PrimaryGeneratorAction.s

# target to generate assembly for a file
src/G4ELIMED_PrimaryGeneratorAction.cc.s:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_PrimaryGeneratorAction.cc.s
.PHONY : src/G4ELIMED_PrimaryGeneratorAction.cc.s

src/G4ELIMED_PrimaryGeneratorActionMessenger.o: src/G4ELIMED_PrimaryGeneratorActionMessenger.cc.o
.PHONY : src/G4ELIMED_PrimaryGeneratorActionMessenger.o

# target to build an object file
src/G4ELIMED_PrimaryGeneratorActionMessenger.cc.o:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_PrimaryGeneratorActionMessenger.cc.o
.PHONY : src/G4ELIMED_PrimaryGeneratorActionMessenger.cc.o

src/G4ELIMED_PrimaryGeneratorActionMessenger.i: src/G4ELIMED_PrimaryGeneratorActionMessenger.cc.i
.PHONY : src/G4ELIMED_PrimaryGeneratorActionMessenger.i

# target to preprocess a source file
src/G4ELIMED_PrimaryGeneratorActionMessenger.cc.i:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_PrimaryGeneratorActionMessenger.cc.i
.PHONY : src/G4ELIMED_PrimaryGeneratorActionMessenger.cc.i

src/G4ELIMED_PrimaryGeneratorActionMessenger.s: src/G4ELIMED_PrimaryGeneratorActionMessenger.cc.s
.PHONY : src/G4ELIMED_PrimaryGeneratorActionMessenger.s

# target to generate assembly for a file
src/G4ELIMED_PrimaryGeneratorActionMessenger.cc.s:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_PrimaryGeneratorActionMessenger.cc.s
.PHONY : src/G4ELIMED_PrimaryGeneratorActionMessenger.cc.s

src/G4ELIMED_Run.o: src/G4ELIMED_Run.cc.o
.PHONY : src/G4ELIMED_Run.o

# target to build an object file
src/G4ELIMED_Run.cc.o:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_Run.cc.o
.PHONY : src/G4ELIMED_Run.cc.o

src/G4ELIMED_Run.i: src/G4ELIMED_Run.cc.i
.PHONY : src/G4ELIMED_Run.i

# target to preprocess a source file
src/G4ELIMED_Run.cc.i:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_Run.cc.i
.PHONY : src/G4ELIMED_Run.cc.i

src/G4ELIMED_Run.s: src/G4ELIMED_Run.cc.s
.PHONY : src/G4ELIMED_Run.s

# target to generate assembly for a file
src/G4ELIMED_Run.cc.s:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_Run.cc.s
.PHONY : src/G4ELIMED_Run.cc.s

src/G4ELIMED_RunAction.o: src/G4ELIMED_RunAction.cc.o
.PHONY : src/G4ELIMED_RunAction.o

# target to build an object file
src/G4ELIMED_RunAction.cc.o:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_RunAction.cc.o
.PHONY : src/G4ELIMED_RunAction.cc.o

src/G4ELIMED_RunAction.i: src/G4ELIMED_RunAction.cc.i
.PHONY : src/G4ELIMED_RunAction.i

# target to preprocess a source file
src/G4ELIMED_RunAction.cc.i:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_RunAction.cc.i
.PHONY : src/G4ELIMED_RunAction.cc.i

src/G4ELIMED_RunAction.s: src/G4ELIMED_RunAction.cc.s
.PHONY : src/G4ELIMED_RunAction.s

# target to generate assembly for a file
src/G4ELIMED_RunAction.cc.s:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_RunAction.cc.s
.PHONY : src/G4ELIMED_RunAction.cc.s

src/G4ELIMED_RunActionMessenger.o: src/G4ELIMED_RunActionMessenger.cc.o
.PHONY : src/G4ELIMED_RunActionMessenger.o

# target to build an object file
src/G4ELIMED_RunActionMessenger.cc.o:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_RunActionMessenger.cc.o
.PHONY : src/G4ELIMED_RunActionMessenger.cc.o

src/G4ELIMED_RunActionMessenger.i: src/G4ELIMED_RunActionMessenger.cc.i
.PHONY : src/G4ELIMED_RunActionMessenger.i

# target to preprocess a source file
src/G4ELIMED_RunActionMessenger.cc.i:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_RunActionMessenger.cc.i
.PHONY : src/G4ELIMED_RunActionMessenger.cc.i

src/G4ELIMED_RunActionMessenger.s: src/G4ELIMED_RunActionMessenger.cc.s
.PHONY : src/G4ELIMED_RunActionMessenger.s

# target to generate assembly for a file
src/G4ELIMED_RunActionMessenger.cc.s:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_RunActionMessenger.cc.s
.PHONY : src/G4ELIMED_RunActionMessenger.cc.s

src/G4ELIMED_SensitiveDetector.o: src/G4ELIMED_SensitiveDetector.cc.o
.PHONY : src/G4ELIMED_SensitiveDetector.o

# target to build an object file
src/G4ELIMED_SensitiveDetector.cc.o:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_SensitiveDetector.cc.o
.PHONY : src/G4ELIMED_SensitiveDetector.cc.o

src/G4ELIMED_SensitiveDetector.i: src/G4ELIMED_SensitiveDetector.cc.i
.PHONY : src/G4ELIMED_SensitiveDetector.i

# target to preprocess a source file
src/G4ELIMED_SensitiveDetector.cc.i:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_SensitiveDetector.cc.i
.PHONY : src/G4ELIMED_SensitiveDetector.cc.i

src/G4ELIMED_SensitiveDetector.s: src/G4ELIMED_SensitiveDetector.cc.s
.PHONY : src/G4ELIMED_SensitiveDetector.s

# target to generate assembly for a file
src/G4ELIMED_SensitiveDetector.cc.s:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_SensitiveDetector.cc.s
.PHONY : src/G4ELIMED_SensitiveDetector.cc.s

src/G4ELIMED_SensitiveDetectorHit.o: src/G4ELIMED_SensitiveDetectorHit.cc.o
.PHONY : src/G4ELIMED_SensitiveDetectorHit.o

# target to build an object file
src/G4ELIMED_SensitiveDetectorHit.cc.o:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_SensitiveDetectorHit.cc.o
.PHONY : src/G4ELIMED_SensitiveDetectorHit.cc.o

src/G4ELIMED_SensitiveDetectorHit.i: src/G4ELIMED_SensitiveDetectorHit.cc.i
.PHONY : src/G4ELIMED_SensitiveDetectorHit.i

# target to preprocess a source file
src/G4ELIMED_SensitiveDetectorHit.cc.i:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_SensitiveDetectorHit.cc.i
.PHONY : src/G4ELIMED_SensitiveDetectorHit.cc.i

src/G4ELIMED_SensitiveDetectorHit.s: src/G4ELIMED_SensitiveDetectorHit.cc.s
.PHONY : src/G4ELIMED_SensitiveDetectorHit.s

# target to generate assembly for a file
src/G4ELIMED_SensitiveDetectorHit.cc.s:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_SensitiveDetectorHit.cc.s
.PHONY : src/G4ELIMED_SensitiveDetectorHit.cc.s

src/G4ELIMED_StackingAction.o: src/G4ELIMED_StackingAction.cc.o
.PHONY : src/G4ELIMED_StackingAction.o

# target to build an object file
src/G4ELIMED_StackingAction.cc.o:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_StackingAction.cc.o
.PHONY : src/G4ELIMED_StackingAction.cc.o

src/G4ELIMED_StackingAction.i: src/G4ELIMED_StackingAction.cc.i
.PHONY : src/G4ELIMED_StackingAction.i

# target to preprocess a source file
src/G4ELIMED_StackingAction.cc.i:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_StackingAction.cc.i
.PHONY : src/G4ELIMED_StackingAction.cc.i

src/G4ELIMED_StackingAction.s: src/G4ELIMED_StackingAction.cc.s
.PHONY : src/G4ELIMED_StackingAction.s

# target to generate assembly for a file
src/G4ELIMED_StackingAction.cc.s:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_StackingAction.cc.s
.PHONY : src/G4ELIMED_StackingAction.cc.s

src/G4ELIMED_StackingActionMessenger.o: src/G4ELIMED_StackingActionMessenger.cc.o
.PHONY : src/G4ELIMED_StackingActionMessenger.o

# target to build an object file
src/G4ELIMED_StackingActionMessenger.cc.o:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_StackingActionMessenger.cc.o
.PHONY : src/G4ELIMED_StackingActionMessenger.cc.o

src/G4ELIMED_StackingActionMessenger.i: src/G4ELIMED_StackingActionMessenger.cc.i
.PHONY : src/G4ELIMED_StackingActionMessenger.i

# target to preprocess a source file
src/G4ELIMED_StackingActionMessenger.cc.i:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_StackingActionMessenger.cc.i
.PHONY : src/G4ELIMED_StackingActionMessenger.cc.i

src/G4ELIMED_StackingActionMessenger.s: src/G4ELIMED_StackingActionMessenger.cc.s
.PHONY : src/G4ELIMED_StackingActionMessenger.s

# target to generate assembly for a file
src/G4ELIMED_StackingActionMessenger.cc.s:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_StackingActionMessenger.cc.s
.PHONY : src/G4ELIMED_StackingActionMessenger.cc.s

src/G4ELIMED_TrackingAction.o: src/G4ELIMED_TrackingAction.cc.o
.PHONY : src/G4ELIMED_TrackingAction.o

# target to build an object file
src/G4ELIMED_TrackingAction.cc.o:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_TrackingAction.cc.o
.PHONY : src/G4ELIMED_TrackingAction.cc.o

src/G4ELIMED_TrackingAction.i: src/G4ELIMED_TrackingAction.cc.i
.PHONY : src/G4ELIMED_TrackingAction.i

# target to preprocess a source file
src/G4ELIMED_TrackingAction.cc.i:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_TrackingAction.cc.i
.PHONY : src/G4ELIMED_TrackingAction.cc.i

src/G4ELIMED_TrackingAction.s: src/G4ELIMED_TrackingAction.cc.s
.PHONY : src/G4ELIMED_TrackingAction.s

# target to generate assembly for a file
src/G4ELIMED_TrackingAction.cc.s:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_TrackingAction.cc.s
.PHONY : src/G4ELIMED_TrackingAction.cc.s

src/G4ELIMED_UserActionInitialization.o: src/G4ELIMED_UserActionInitialization.cc.o
.PHONY : src/G4ELIMED_UserActionInitialization.o

# target to build an object file
src/G4ELIMED_UserActionInitialization.cc.o:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_UserActionInitialization.cc.o
.PHONY : src/G4ELIMED_UserActionInitialization.cc.o

src/G4ELIMED_UserActionInitialization.i: src/G4ELIMED_UserActionInitialization.cc.i
.PHONY : src/G4ELIMED_UserActionInitialization.i

# target to preprocess a source file
src/G4ELIMED_UserActionInitialization.cc.i:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_UserActionInitialization.cc.i
.PHONY : src/G4ELIMED_UserActionInitialization.cc.i

src/G4ELIMED_UserActionInitialization.s: src/G4ELIMED_UserActionInitialization.cc.s
.PHONY : src/G4ELIMED_UserActionInitialization.s

# target to generate assembly for a file
src/G4ELIMED_UserActionInitialization.cc.s:
	$(MAKE) -f CMakeFiles/g4elimed.dir/build.make CMakeFiles/g4elimed.dir/src/G4ELIMED_UserActionInitialization.cc.s
.PHONY : src/G4ELIMED_UserActionInitialization.cc.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... G4elimed"
	@echo "... edit_cache"
	@echo "... g4elimed"
	@echo "... install"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... list_install_components"
	@echo "... rebuild_cache"
	@echo "... g4elimed.o"
	@echo "... g4elimed.i"
	@echo "... g4elimed.s"
	@echo "... src/G4ELIMED_DetectorConstruction.o"
	@echo "... src/G4ELIMED_DetectorConstruction.i"
	@echo "... src/G4ELIMED_DetectorConstruction.s"
	@echo "... src/G4ELIMED_DetectorConstructionMessenger.o"
	@echo "... src/G4ELIMED_DetectorConstructionMessenger.i"
	@echo "... src/G4ELIMED_DetectorConstructionMessenger.s"
	@echo "... src/G4ELIMED_EventAction.o"
	@echo "... src/G4ELIMED_EventAction.i"
	@echo "... src/G4ELIMED_EventAction.s"
	@echo "... src/G4ELIMED_FileReader.o"
	@echo "... src/G4ELIMED_FileReader.i"
	@echo "... src/G4ELIMED_FileReader.s"
	@echo "... src/G4ELIMED_PhysicsList.o"
	@echo "... src/G4ELIMED_PhysicsList.i"
	@echo "... src/G4ELIMED_PhysicsList.s"
	@echo "... src/G4ELIMED_PhysicsListMessenger.o"
	@echo "... src/G4ELIMED_PhysicsListMessenger.i"
	@echo "... src/G4ELIMED_PhysicsListMessenger.s"
	@echo "... src/G4ELIMED_PrimaryGeneratorAction.o"
	@echo "... src/G4ELIMED_PrimaryGeneratorAction.i"
	@echo "... src/G4ELIMED_PrimaryGeneratorAction.s"
	@echo "... src/G4ELIMED_PrimaryGeneratorActionMessenger.o"
	@echo "... src/G4ELIMED_PrimaryGeneratorActionMessenger.i"
	@echo "... src/G4ELIMED_PrimaryGeneratorActionMessenger.s"
	@echo "... src/G4ELIMED_Run.o"
	@echo "... src/G4ELIMED_Run.i"
	@echo "... src/G4ELIMED_Run.s"
	@echo "... src/G4ELIMED_RunAction.o"
	@echo "... src/G4ELIMED_RunAction.i"
	@echo "... src/G4ELIMED_RunAction.s"
	@echo "... src/G4ELIMED_RunActionMessenger.o"
	@echo "... src/G4ELIMED_RunActionMessenger.i"
	@echo "... src/G4ELIMED_RunActionMessenger.s"
	@echo "... src/G4ELIMED_SensitiveDetector.o"
	@echo "... src/G4ELIMED_SensitiveDetector.i"
	@echo "... src/G4ELIMED_SensitiveDetector.s"
	@echo "... src/G4ELIMED_SensitiveDetectorHit.o"
	@echo "... src/G4ELIMED_SensitiveDetectorHit.i"
	@echo "... src/G4ELIMED_SensitiveDetectorHit.s"
	@echo "... src/G4ELIMED_StackingAction.o"
	@echo "... src/G4ELIMED_StackingAction.i"
	@echo "... src/G4ELIMED_StackingAction.s"
	@echo "... src/G4ELIMED_StackingActionMessenger.o"
	@echo "... src/G4ELIMED_StackingActionMessenger.i"
	@echo "... src/G4ELIMED_StackingActionMessenger.s"
	@echo "... src/G4ELIMED_TrackingAction.o"
	@echo "... src/G4ELIMED_TrackingAction.i"
	@echo "... src/G4ELIMED_TrackingAction.s"
	@echo "... src/G4ELIMED_UserActionInitialization.o"
	@echo "... src/G4ELIMED_UserActionInitialization.i"
	@echo "... src/G4ELIMED_UserActionInitialization.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
