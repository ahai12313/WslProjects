# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ahai/project/project1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ahai/project/project1/build

# Include any dependencies generated for this target.
include CMakeFiles/MemoryPool.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MemoryPool.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MemoryPool.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MemoryPool.dir/flags.make

CMakeFiles/MemoryPool.dir/main.cpp.o: CMakeFiles/MemoryPool.dir/flags.make
CMakeFiles/MemoryPool.dir/main.cpp.o: ../main.cpp
CMakeFiles/MemoryPool.dir/main.cpp.o: CMakeFiles/MemoryPool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ahai/project/project1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MemoryPool.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MemoryPool.dir/main.cpp.o -MF CMakeFiles/MemoryPool.dir/main.cpp.o.d -o CMakeFiles/MemoryPool.dir/main.cpp.o -c /home/ahai/project/project1/main.cpp

CMakeFiles/MemoryPool.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MemoryPool.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ahai/project/project1/main.cpp > CMakeFiles/MemoryPool.dir/main.cpp.i

CMakeFiles/MemoryPool.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MemoryPool.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ahai/project/project1/main.cpp -o CMakeFiles/MemoryPool.dir/main.cpp.s

# Object files for target MemoryPool
MemoryPool_OBJECTS = \
"CMakeFiles/MemoryPool.dir/main.cpp.o"

# External object files for target MemoryPool
MemoryPool_EXTERNAL_OBJECTS =

MemoryPool: CMakeFiles/MemoryPool.dir/main.cpp.o
MemoryPool: CMakeFiles/MemoryPool.dir/build.make
MemoryPool: /usr/lib/x86_64-linux-gnu/libfmt.so.8.1.1
MemoryPool: CMakeFiles/MemoryPool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ahai/project/project1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MemoryPool"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MemoryPool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MemoryPool.dir/build: MemoryPool
.PHONY : CMakeFiles/MemoryPool.dir/build

CMakeFiles/MemoryPool.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MemoryPool.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MemoryPool.dir/clean

CMakeFiles/MemoryPool.dir/depend:
	cd /home/ahai/project/project1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ahai/project/project1 /home/ahai/project/project1 /home/ahai/project/project1/build /home/ahai/project/project1/build /home/ahai/project/project1/build/CMakeFiles/MemoryPool.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MemoryPool.dir/depend

