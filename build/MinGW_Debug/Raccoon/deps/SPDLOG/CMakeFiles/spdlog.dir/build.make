# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

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
CMAKE_SOURCE_DIR = C:\Code\GitHub\RaccoonPublic

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Code\GitHub\RaccoonPublic\build\MinGW_Debug

# Include any dependencies generated for this target.
include Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/compiler_depend.make

# Include the progress variables for this target.
include Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/progress.make

# Include the compile flags for this target's objects.
include Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/flags.make

Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/RE_BUILD.cpp.obj: Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/flags.make
Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/RE_BUILD.cpp.obj: Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/includes_CXX.rsp
Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/RE_BUILD.cpp.obj: C:/Code/GitHub/RaccoonPublic/Raccoon/deps/SPDLOG/RE_BUILD.cpp
Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/RE_BUILD.cpp.obj: Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Code\GitHub\RaccoonPublic\build\MinGW_Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/RE_BUILD.cpp.obj"
	cd /d C:\Code\GitHub\RaccoonPublic\build\MinGW_Debug\Raccoon\deps\SPDLOG && C:\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/RE_BUILD.cpp.obj -MF CMakeFiles\spdlog.dir\RE_BUILD.cpp.obj.d -o CMakeFiles\spdlog.dir\RE_BUILD.cpp.obj -c C:\Code\GitHub\RaccoonPublic\Raccoon\deps\SPDLOG\RE_BUILD.cpp

Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/RE_BUILD.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/spdlog.dir/RE_BUILD.cpp.i"
	cd /d C:\Code\GitHub\RaccoonPublic\build\MinGW_Debug\Raccoon\deps\SPDLOG && C:\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Code\GitHub\RaccoonPublic\Raccoon\deps\SPDLOG\RE_BUILD.cpp > CMakeFiles\spdlog.dir\RE_BUILD.cpp.i

Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/RE_BUILD.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/spdlog.dir/RE_BUILD.cpp.s"
	cd /d C:\Code\GitHub\RaccoonPublic\build\MinGW_Debug\Raccoon\deps\SPDLOG && C:\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Code\GitHub\RaccoonPublic\Raccoon\deps\SPDLOG\RE_BUILD.cpp -o CMakeFiles\spdlog.dir\RE_BUILD.cpp.s

# Object files for target spdlog
spdlog_OBJECTS = \
"CMakeFiles/spdlog.dir/RE_BUILD.cpp.obj"

# External object files for target spdlog
spdlog_EXTERNAL_OBJECTS =

Raccoon/deps/SPDLOG/libspdlog.a: Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/RE_BUILD.cpp.obj
Raccoon/deps/SPDLOG/libspdlog.a: Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/build.make
Raccoon/deps/SPDLOG/libspdlog.a: Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Code\GitHub\RaccoonPublic\build\MinGW_Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libspdlog.a"
	cd /d C:\Code\GitHub\RaccoonPublic\build\MinGW_Debug\Raccoon\deps\SPDLOG && $(CMAKE_COMMAND) -P CMakeFiles\spdlog.dir\cmake_clean_target.cmake
	cd /d C:\Code\GitHub\RaccoonPublic\build\MinGW_Debug\Raccoon\deps\SPDLOG && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\spdlog.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/build: Raccoon/deps/SPDLOG/libspdlog.a
.PHONY : Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/build

Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/clean:
	cd /d C:\Code\GitHub\RaccoonPublic\build\MinGW_Debug\Raccoon\deps\SPDLOG && $(CMAKE_COMMAND) -P CMakeFiles\spdlog.dir\cmake_clean.cmake
.PHONY : Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/clean

Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Code\GitHub\RaccoonPublic C:\Code\GitHub\RaccoonPublic\Raccoon\deps\SPDLOG C:\Code\GitHub\RaccoonPublic\build\MinGW_Debug C:\Code\GitHub\RaccoonPublic\build\MinGW_Debug\Raccoon\deps\SPDLOG C:\Code\GitHub\RaccoonPublic\build\MinGW_Debug\Raccoon\deps\SPDLOG\CMakeFiles\spdlog.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : Raccoon/deps/SPDLOG/CMakeFiles/spdlog.dir/depend

