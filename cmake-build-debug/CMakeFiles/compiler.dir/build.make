# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2024.3.1.1\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2024.3.1.1\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\blues\OneDrive\Documents\GitHub\Compiler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\blues\OneDrive\Documents\GitHub\Compiler\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/compiler.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/compiler.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/compiler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/compiler.dir/flags.make

CMakeFiles/compiler.dir/main.cpp.obj: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/main.cpp.obj: C:/Users/blues/OneDrive/Documents/GitHub/Compiler/main.cpp
CMakeFiles/compiler.dir/main.cpp.obj: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\blues\OneDrive\Documents\GitHub\Compiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/compiler.dir/main.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/compiler.dir/main.cpp.obj -MF CMakeFiles\compiler.dir\main.cpp.obj.d -o CMakeFiles\compiler.dir\main.cpp.obj -c C:\Users\blues\OneDrive\Documents\GitHub\Compiler\main.cpp

CMakeFiles/compiler.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/compiler.dir/main.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\blues\OneDrive\Documents\GitHub\Compiler\main.cpp > CMakeFiles\compiler.dir\main.cpp.i

CMakeFiles/compiler.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/main.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\blues\OneDrive\Documents\GitHub\Compiler\main.cpp -o CMakeFiles\compiler.dir\main.cpp.s

CMakeFiles/compiler.dir/LexAnalyzer.cpp.obj: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/LexAnalyzer.cpp.obj: C:/Users/blues/OneDrive/Documents/GitHub/Compiler/LexAnalyzer.cpp
CMakeFiles/compiler.dir/LexAnalyzer.cpp.obj: CMakeFiles/compiler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\blues\OneDrive\Documents\GitHub\Compiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/compiler.dir/LexAnalyzer.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/compiler.dir/LexAnalyzer.cpp.obj -MF CMakeFiles\compiler.dir\LexAnalyzer.cpp.obj.d -o CMakeFiles\compiler.dir\LexAnalyzer.cpp.obj -c C:\Users\blues\OneDrive\Documents\GitHub\Compiler\LexAnalyzer.cpp

CMakeFiles/compiler.dir/LexAnalyzer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/compiler.dir/LexAnalyzer.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\blues\OneDrive\Documents\GitHub\Compiler\LexAnalyzer.cpp > CMakeFiles\compiler.dir\LexAnalyzer.cpp.i

CMakeFiles/compiler.dir/LexAnalyzer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/LexAnalyzer.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\blues\OneDrive\Documents\GitHub\Compiler\LexAnalyzer.cpp -o CMakeFiles\compiler.dir\LexAnalyzer.cpp.s

# Object files for target compiler
compiler_OBJECTS = \
"CMakeFiles/compiler.dir/main.cpp.obj" \
"CMakeFiles/compiler.dir/LexAnalyzer.cpp.obj"

# External object files for target compiler
compiler_EXTERNAL_OBJECTS =

compiler.exe: CMakeFiles/compiler.dir/main.cpp.obj
compiler.exe: CMakeFiles/compiler.dir/LexAnalyzer.cpp.obj
compiler.exe: CMakeFiles/compiler.dir/build.make
compiler.exe: CMakeFiles/compiler.dir/linkLibs.rsp
compiler.exe: CMakeFiles/compiler.dir/objects1.rsp
compiler.exe: CMakeFiles/compiler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\blues\OneDrive\Documents\GitHub\Compiler\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable compiler.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\compiler.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/compiler.dir/build: compiler.exe
.PHONY : CMakeFiles/compiler.dir/build

CMakeFiles/compiler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\compiler.dir\cmake_clean.cmake
.PHONY : CMakeFiles/compiler.dir/clean

CMakeFiles/compiler.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\blues\OneDrive\Documents\GitHub\Compiler C:\Users\blues\OneDrive\Documents\GitHub\Compiler C:\Users\blues\OneDrive\Documents\GitHub\Compiler\cmake-build-debug C:\Users\blues\OneDrive\Documents\GitHub\Compiler\cmake-build-debug C:\Users\blues\OneDrive\Documents\GitHub\Compiler\cmake-build-debug\CMakeFiles\compiler.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/compiler.dir/depend

