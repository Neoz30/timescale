# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\enzom\Desktop\Projets\Timescale

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\enzom\Desktop\Projets\Timescale\build

# Include any dependencies generated for this target.
include CMakeFiles/Vec2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Vec2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Vec2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Vec2.dir/flags.make

CMakeFiles/Vec2.dir/codegen:
.PHONY : CMakeFiles/Vec2.dir/codegen

CMakeFiles/Vec2.dir/timescale/libmath/vec2.cpp.obj: CMakeFiles/Vec2.dir/flags.make
CMakeFiles/Vec2.dir/timescale/libmath/vec2.cpp.obj: C:/Users/enzom/Desktop/Projets/Timescale/timescale/libmath/vec2.cpp
CMakeFiles/Vec2.dir/timescale/libmath/vec2.cpp.obj: CMakeFiles/Vec2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\enzom\Desktop\Projets\Timescale\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Vec2.dir/timescale/libmath/vec2.cpp.obj"
	C:\MinGW\x86_64-14.2.0-release-posix-seh-ucrt-rt_v12-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Vec2.dir/timescale/libmath/vec2.cpp.obj -MF CMakeFiles\Vec2.dir\timescale\libmath\vec2.cpp.obj.d -o CMakeFiles\Vec2.dir\timescale\libmath\vec2.cpp.obj -c C:\Users\enzom\Desktop\Projets\Timescale\timescale\libmath\vec2.cpp

CMakeFiles/Vec2.dir/timescale/libmath/vec2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Vec2.dir/timescale/libmath/vec2.cpp.i"
	C:\MinGW\x86_64-14.2.0-release-posix-seh-ucrt-rt_v12-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\enzom\Desktop\Projets\Timescale\timescale\libmath\vec2.cpp > CMakeFiles\Vec2.dir\timescale\libmath\vec2.cpp.i

CMakeFiles/Vec2.dir/timescale/libmath/vec2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Vec2.dir/timescale/libmath/vec2.cpp.s"
	C:\MinGW\x86_64-14.2.0-release-posix-seh-ucrt-rt_v12-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\enzom\Desktop\Projets\Timescale\timescale\libmath\vec2.cpp -o CMakeFiles\Vec2.dir\timescale\libmath\vec2.cpp.s

# Object files for target Vec2
Vec2_OBJECTS = \
"CMakeFiles/Vec2.dir/timescale/libmath/vec2.cpp.obj"

# External object files for target Vec2
Vec2_EXTERNAL_OBJECTS =

libVec2.a: CMakeFiles/Vec2.dir/timescale/libmath/vec2.cpp.obj
libVec2.a: CMakeFiles/Vec2.dir/build.make
libVec2.a: CMakeFiles/Vec2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\enzom\Desktop\Projets\Timescale\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libVec2.a"
	$(CMAKE_COMMAND) -P CMakeFiles\Vec2.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Vec2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Vec2.dir/build: libVec2.a
.PHONY : CMakeFiles/Vec2.dir/build

CMakeFiles/Vec2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Vec2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Vec2.dir/clean

CMakeFiles/Vec2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\enzom\Desktop\Projets\Timescale C:\Users\enzom\Desktop\Projets\Timescale C:\Users\enzom\Desktop\Projets\Timescale\build C:\Users\enzom\Desktop\Projets\Timescale\build C:\Users\enzom\Desktop\Projets\Timescale\build\CMakeFiles\Vec2.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Vec2.dir/depend

