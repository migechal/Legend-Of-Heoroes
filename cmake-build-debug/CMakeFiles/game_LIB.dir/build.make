# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /app/extra/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /app/extra/clion/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/migecha/Projects/Games/Legend-Of-Heores

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/migecha/Projects/Games/Legend-Of-Heores/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/game_LIB.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/game_LIB.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/game_LIB.dir/flags.make

CMakeFiles/game_LIB.dir/source/Entity.cpp.o: CMakeFiles/game_LIB.dir/flags.make
CMakeFiles/game_LIB.dir/source/Entity.cpp.o: ../source/Entity.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/migecha/Projects/Games/Legend-Of-Heores/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/game_LIB.dir/source/Entity.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/game_LIB.dir/source/Entity.cpp.o -c /home/migecha/Projects/Games/Legend-Of-Heores/source/Entity.cpp

CMakeFiles/game_LIB.dir/source/Entity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game_LIB.dir/source/Entity.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/migecha/Projects/Games/Legend-Of-Heores/source/Entity.cpp > CMakeFiles/game_LIB.dir/source/Entity.cpp.i

CMakeFiles/game_LIB.dir/source/Entity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game_LIB.dir/source/Entity.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/migecha/Projects/Games/Legend-Of-Heores/source/Entity.cpp -o CMakeFiles/game_LIB.dir/source/Entity.cpp.s

CMakeFiles/game_LIB.dir/source/Game.cpp.o: CMakeFiles/game_LIB.dir/flags.make
CMakeFiles/game_LIB.dir/source/Game.cpp.o: ../source/Game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/migecha/Projects/Games/Legend-Of-Heores/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/game_LIB.dir/source/Game.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/game_LIB.dir/source/Game.cpp.o -c /home/migecha/Projects/Games/Legend-Of-Heores/source/Game.cpp

CMakeFiles/game_LIB.dir/source/Game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game_LIB.dir/source/Game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/migecha/Projects/Games/Legend-Of-Heores/source/Game.cpp > CMakeFiles/game_LIB.dir/source/Game.cpp.i

CMakeFiles/game_LIB.dir/source/Game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game_LIB.dir/source/Game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/migecha/Projects/Games/Legend-Of-Heores/source/Game.cpp -o CMakeFiles/game_LIB.dir/source/Game.cpp.s

CMakeFiles/game_LIB.dir/source/Gui.cpp.o: CMakeFiles/game_LIB.dir/flags.make
CMakeFiles/game_LIB.dir/source/Gui.cpp.o: ../source/Gui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/migecha/Projects/Games/Legend-Of-Heores/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/game_LIB.dir/source/Gui.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/game_LIB.dir/source/Gui.cpp.o -c /home/migecha/Projects/Games/Legend-Of-Heores/source/Gui.cpp

CMakeFiles/game_LIB.dir/source/Gui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game_LIB.dir/source/Gui.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/migecha/Projects/Games/Legend-Of-Heores/source/Gui.cpp > CMakeFiles/game_LIB.dir/source/Gui.cpp.i

CMakeFiles/game_LIB.dir/source/Gui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game_LIB.dir/source/Gui.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/migecha/Projects/Games/Legend-Of-Heores/source/Gui.cpp -o CMakeFiles/game_LIB.dir/source/Gui.cpp.s

CMakeFiles/game_LIB.dir/source/Init.cpp.o: CMakeFiles/game_LIB.dir/flags.make
CMakeFiles/game_LIB.dir/source/Init.cpp.o: ../source/Init.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/migecha/Projects/Games/Legend-Of-Heores/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/game_LIB.dir/source/Init.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/game_LIB.dir/source/Init.cpp.o -c /home/migecha/Projects/Games/Legend-Of-Heores/source/Init.cpp

CMakeFiles/game_LIB.dir/source/Init.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game_LIB.dir/source/Init.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/migecha/Projects/Games/Legend-Of-Heores/source/Init.cpp > CMakeFiles/game_LIB.dir/source/Init.cpp.i

CMakeFiles/game_LIB.dir/source/Init.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game_LIB.dir/source/Init.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/migecha/Projects/Games/Legend-Of-Heores/source/Init.cpp -o CMakeFiles/game_LIB.dir/source/Init.cpp.s

CMakeFiles/game_LIB.dir/source/Input.cpp.o: CMakeFiles/game_LIB.dir/flags.make
CMakeFiles/game_LIB.dir/source/Input.cpp.o: ../source/Input.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/migecha/Projects/Games/Legend-Of-Heores/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/game_LIB.dir/source/Input.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/game_LIB.dir/source/Input.cpp.o -c /home/migecha/Projects/Games/Legend-Of-Heores/source/Input.cpp

CMakeFiles/game_LIB.dir/source/Input.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game_LIB.dir/source/Input.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/migecha/Projects/Games/Legend-Of-Heores/source/Input.cpp > CMakeFiles/game_LIB.dir/source/Input.cpp.i

CMakeFiles/game_LIB.dir/source/Input.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game_LIB.dir/source/Input.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/migecha/Projects/Games/Legend-Of-Heores/source/Input.cpp -o CMakeFiles/game_LIB.dir/source/Input.cpp.s

CMakeFiles/game_LIB.dir/source/KeyboardHandler.cpp.o: CMakeFiles/game_LIB.dir/flags.make
CMakeFiles/game_LIB.dir/source/KeyboardHandler.cpp.o: ../source/KeyboardHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/migecha/Projects/Games/Legend-Of-Heores/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/game_LIB.dir/source/KeyboardHandler.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/game_LIB.dir/source/KeyboardHandler.cpp.o -c /home/migecha/Projects/Games/Legend-Of-Heores/source/KeyboardHandler.cpp

CMakeFiles/game_LIB.dir/source/KeyboardHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game_LIB.dir/source/KeyboardHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/migecha/Projects/Games/Legend-Of-Heores/source/KeyboardHandler.cpp > CMakeFiles/game_LIB.dir/source/KeyboardHandler.cpp.i

CMakeFiles/game_LIB.dir/source/KeyboardHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game_LIB.dir/source/KeyboardHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/migecha/Projects/Games/Legend-Of-Heores/source/KeyboardHandler.cpp -o CMakeFiles/game_LIB.dir/source/KeyboardHandler.cpp.s

CMakeFiles/game_LIB.dir/source/Menu.cpp.o: CMakeFiles/game_LIB.dir/flags.make
CMakeFiles/game_LIB.dir/source/Menu.cpp.o: ../source/Menu.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/migecha/Projects/Games/Legend-Of-Heores/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/game_LIB.dir/source/Menu.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/game_LIB.dir/source/Menu.cpp.o -c /home/migecha/Projects/Games/Legend-Of-Heores/source/Menu.cpp

CMakeFiles/game_LIB.dir/source/Menu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game_LIB.dir/source/Menu.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/migecha/Projects/Games/Legend-Of-Heores/source/Menu.cpp > CMakeFiles/game_LIB.dir/source/Menu.cpp.i

CMakeFiles/game_LIB.dir/source/Menu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game_LIB.dir/source/Menu.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/migecha/Projects/Games/Legend-Of-Heores/source/Menu.cpp -o CMakeFiles/game_LIB.dir/source/Menu.cpp.s

CMakeFiles/game_LIB.dir/source/Object.cpp.o: CMakeFiles/game_LIB.dir/flags.make
CMakeFiles/game_LIB.dir/source/Object.cpp.o: ../source/Object.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/migecha/Projects/Games/Legend-Of-Heores/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/game_LIB.dir/source/Object.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/game_LIB.dir/source/Object.cpp.o -c /home/migecha/Projects/Games/Legend-Of-Heores/source/Object.cpp

CMakeFiles/game_LIB.dir/source/Object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game_LIB.dir/source/Object.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/migecha/Projects/Games/Legend-Of-Heores/source/Object.cpp > CMakeFiles/game_LIB.dir/source/Object.cpp.i

CMakeFiles/game_LIB.dir/source/Object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game_LIB.dir/source/Object.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/migecha/Projects/Games/Legend-Of-Heores/source/Object.cpp -o CMakeFiles/game_LIB.dir/source/Object.cpp.s

CMakeFiles/game_LIB.dir/source/Timer.cpp.o: CMakeFiles/game_LIB.dir/flags.make
CMakeFiles/game_LIB.dir/source/Timer.cpp.o: ../source/Timer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/migecha/Projects/Games/Legend-Of-Heores/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/game_LIB.dir/source/Timer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/game_LIB.dir/source/Timer.cpp.o -c /home/migecha/Projects/Games/Legend-Of-Heores/source/Timer.cpp

CMakeFiles/game_LIB.dir/source/Timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game_LIB.dir/source/Timer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/migecha/Projects/Games/Legend-Of-Heores/source/Timer.cpp > CMakeFiles/game_LIB.dir/source/Timer.cpp.i

CMakeFiles/game_LIB.dir/source/Timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game_LIB.dir/source/Timer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/migecha/Projects/Games/Legend-Of-Heores/source/Timer.cpp -o CMakeFiles/game_LIB.dir/source/Timer.cpp.s

# Object files for target game_LIB
game_LIB_OBJECTS = \
"CMakeFiles/game_LIB.dir/source/Entity.cpp.o" \
"CMakeFiles/game_LIB.dir/source/Game.cpp.o" \
"CMakeFiles/game_LIB.dir/source/Gui.cpp.o" \
"CMakeFiles/game_LIB.dir/source/Init.cpp.o" \
"CMakeFiles/game_LIB.dir/source/Input.cpp.o" \
"CMakeFiles/game_LIB.dir/source/KeyboardHandler.cpp.o" \
"CMakeFiles/game_LIB.dir/source/Menu.cpp.o" \
"CMakeFiles/game_LIB.dir/source/Object.cpp.o" \
"CMakeFiles/game_LIB.dir/source/Timer.cpp.o"

# External object files for target game_LIB
game_LIB_EXTERNAL_OBJECTS =

libgame_LIB.a: CMakeFiles/game_LIB.dir/source/Entity.cpp.o
libgame_LIB.a: CMakeFiles/game_LIB.dir/source/Game.cpp.o
libgame_LIB.a: CMakeFiles/game_LIB.dir/source/Gui.cpp.o
libgame_LIB.a: CMakeFiles/game_LIB.dir/source/Init.cpp.o
libgame_LIB.a: CMakeFiles/game_LIB.dir/source/Input.cpp.o
libgame_LIB.a: CMakeFiles/game_LIB.dir/source/KeyboardHandler.cpp.o
libgame_LIB.a: CMakeFiles/game_LIB.dir/source/Menu.cpp.o
libgame_LIB.a: CMakeFiles/game_LIB.dir/source/Object.cpp.o
libgame_LIB.a: CMakeFiles/game_LIB.dir/source/Timer.cpp.o
libgame_LIB.a: CMakeFiles/game_LIB.dir/build.make
libgame_LIB.a: CMakeFiles/game_LIB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/migecha/Projects/Games/Legend-Of-Heores/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX static library libgame_LIB.a"
	$(CMAKE_COMMAND) -P CMakeFiles/game_LIB.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/game_LIB.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/game_LIB.dir/build: libgame_LIB.a

.PHONY : CMakeFiles/game_LIB.dir/build

CMakeFiles/game_LIB.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/game_LIB.dir/cmake_clean.cmake
.PHONY : CMakeFiles/game_LIB.dir/clean

CMakeFiles/game_LIB.dir/depend:
	cd /home/migecha/Projects/Games/Legend-Of-Heores/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/migecha/Projects/Games/Legend-Of-Heores /home/migecha/Projects/Games/Legend-Of-Heores /home/migecha/Projects/Games/Legend-Of-Heores/cmake-build-debug /home/migecha/Projects/Games/Legend-Of-Heores/cmake-build-debug /home/migecha/Projects/Games/Legend-Of-Heores/cmake-build-debug/CMakeFiles/game_LIB.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/game_LIB.dir/depend

