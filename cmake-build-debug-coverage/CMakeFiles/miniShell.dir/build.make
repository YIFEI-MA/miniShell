# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = "/Users/yifeima/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/202.6948.80/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/yifeima/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/202.6948.80/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/yifeima/CLionProjects/miniShell

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/yifeima/CLionProjects/miniShell/cmake-build-debug-coverage

# Include any dependencies generated for this target.
include CMakeFiles/miniShell.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/miniShell.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/miniShell.dir/flags.make

CMakeFiles/miniShell.dir/main.c.o: CMakeFiles/miniShell.dir/flags.make
CMakeFiles/miniShell.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yifeima/CLionProjects/miniShell/cmake-build-debug-coverage/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/miniShell.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/miniShell.dir/main.c.o   -c /Users/yifeima/CLionProjects/miniShell/main.c

CMakeFiles/miniShell.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/miniShell.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/yifeima/CLionProjects/miniShell/main.c > CMakeFiles/miniShell.dir/main.c.i

CMakeFiles/miniShell.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/miniShell.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/yifeima/CLionProjects/miniShell/main.c -o CMakeFiles/miniShell.dir/main.c.s

CMakeFiles/miniShell.dir/Calc_time.c.o: CMakeFiles/miniShell.dir/flags.make
CMakeFiles/miniShell.dir/Calc_time.c.o: ../Calc_time.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yifeima/CLionProjects/miniShell/cmake-build-debug-coverage/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/miniShell.dir/Calc_time.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/miniShell.dir/Calc_time.c.o   -c /Users/yifeima/CLionProjects/miniShell/Calc_time.c

CMakeFiles/miniShell.dir/Calc_time.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/miniShell.dir/Calc_time.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/yifeima/CLionProjects/miniShell/Calc_time.c > CMakeFiles/miniShell.dir/Calc_time.c.i

CMakeFiles/miniShell.dir/Calc_time.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/miniShell.dir/Calc_time.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/yifeima/CLionProjects/miniShell/Calc_time.c -o CMakeFiles/miniShell.dir/Calc_time.c.s

CMakeFiles/miniShell.dir/helperFunction.c.o: CMakeFiles/miniShell.dir/flags.make
CMakeFiles/miniShell.dir/helperFunction.c.o: ../helperFunction.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/yifeima/CLionProjects/miniShell/cmake-build-debug-coverage/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/miniShell.dir/helperFunction.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/miniShell.dir/helperFunction.c.o   -c /Users/yifeima/CLionProjects/miniShell/helperFunction.c

CMakeFiles/miniShell.dir/helperFunction.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/miniShell.dir/helperFunction.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/yifeima/CLionProjects/miniShell/helperFunction.c > CMakeFiles/miniShell.dir/helperFunction.c.i

CMakeFiles/miniShell.dir/helperFunction.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/miniShell.dir/helperFunction.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/yifeima/CLionProjects/miniShell/helperFunction.c -o CMakeFiles/miniShell.dir/helperFunction.c.s

# Object files for target miniShell
miniShell_OBJECTS = \
"CMakeFiles/miniShell.dir/main.c.o" \
"CMakeFiles/miniShell.dir/Calc_time.c.o" \
"CMakeFiles/miniShell.dir/helperFunction.c.o"

# External object files for target miniShell
miniShell_EXTERNAL_OBJECTS =

miniShell: CMakeFiles/miniShell.dir/main.c.o
miniShell: CMakeFiles/miniShell.dir/Calc_time.c.o
miniShell: CMakeFiles/miniShell.dir/helperFunction.c.o
miniShell: CMakeFiles/miniShell.dir/build.make
miniShell: CMakeFiles/miniShell.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/yifeima/CLionProjects/miniShell/cmake-build-debug-coverage/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable miniShell"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/miniShell.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/miniShell.dir/build: miniShell

.PHONY : CMakeFiles/miniShell.dir/build

CMakeFiles/miniShell.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/miniShell.dir/cmake_clean.cmake
.PHONY : CMakeFiles/miniShell.dir/clean

CMakeFiles/miniShell.dir/depend:
	cd /Users/yifeima/CLionProjects/miniShell/cmake-build-debug-coverage && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/yifeima/CLionProjects/miniShell /Users/yifeima/CLionProjects/miniShell /Users/yifeima/CLionProjects/miniShell/cmake-build-debug-coverage /Users/yifeima/CLionProjects/miniShell/cmake-build-debug-coverage /Users/yifeima/CLionProjects/miniShell/cmake-build-debug-coverage/CMakeFiles/miniShell.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/miniShell.dir/depend

