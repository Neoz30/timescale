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
include CMakeFiles/Graphics.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Graphics.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Graphics.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Graphics.dir/flags.make

CMakeFiles/Graphics.dir/codegen:
.PHONY : CMakeFiles/Graphics.dir/codegen

CMakeFiles/Graphics.dir/timescale/graphics/graphics.cpp.obj: CMakeFiles/Graphics.dir/flags.make
CMakeFiles/Graphics.dir/timescale/graphics/graphics.cpp.obj: CMakeFiles/Graphics.dir/includes_CXX.rsp
CMakeFiles/Graphics.dir/timescale/graphics/graphics.cpp.obj: C:/Users/enzom/Desktop/Projets/Timescale/timescale/graphics/graphics.cpp
CMakeFiles/Graphics.dir/timescale/graphics/graphics.cpp.obj: CMakeFiles/Graphics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\enzom\Desktop\Projets\Timescale\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Graphics.dir/timescale/graphics/graphics.cpp.obj"
	C:\MinGW\x86_64-14.2.0-release-posix-seh-ucrt-rt_v12-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Graphics.dir/timescale/graphics/graphics.cpp.obj -MF CMakeFiles\Graphics.dir\timescale\graphics\graphics.cpp.obj.d -o CMakeFiles\Graphics.dir\timescale\graphics\graphics.cpp.obj -c C:\Users\enzom\Desktop\Projets\Timescale\timescale\graphics\graphics.cpp

CMakeFiles/Graphics.dir/timescale/graphics/graphics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Graphics.dir/timescale/graphics/graphics.cpp.i"
	C:\MinGW\x86_64-14.2.0-release-posix-seh-ucrt-rt_v12-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\enzom\Desktop\Projets\Timescale\timescale\graphics\graphics.cpp > CMakeFiles\Graphics.dir\timescale\graphics\graphics.cpp.i

CMakeFiles/Graphics.dir/timescale/graphics/graphics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Graphics.dir/timescale/graphics/graphics.cpp.s"
	C:\MinGW\x86_64-14.2.0-release-posix-seh-ucrt-rt_v12-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\enzom\Desktop\Projets\Timescale\timescale\graphics\graphics.cpp -o CMakeFiles\Graphics.dir\timescale\graphics\graphics.cpp.s

# Object files for target Graphics
Graphics_OBJECTS = \
"CMakeFiles/Graphics.dir/timescale/graphics/graphics.cpp.obj"

# External object files for target Graphics
Graphics_EXTERNAL_OBJECTS =

libGraphics.a: CMakeFiles/Graphics.dir/timescale/graphics/graphics.cpp.obj
libGraphics.a: CMakeFiles/Graphics.dir/build.make
libGraphics.a: CMakeFiles/Graphics.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\enzom\Desktop\Projets\Timescale\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libGraphics.a"
	$(CMAKE_COMMAND) -P CMakeFiles\Graphics.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Graphics.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Graphics.dir/build: libGraphics.a
.PHONY : CMakeFiles/Graphics.dir/build

CMakeFiles/Graphics.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Graphics.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Graphics.dir/clean

CMakeFiles/Graphics.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\enzom\Desktop\Projets\Timescale C:\Users\enzom\Desktop\Projets\Timescale C:\Users\enzom\Desktop\Projets\Timescale\build C:\Users\enzom\Desktop\Projets\Timescale\build C:\Users\enzom\Desktop\Projets\Timescale\build\CMakeFiles\Graphics.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Graphics.dir/depend

