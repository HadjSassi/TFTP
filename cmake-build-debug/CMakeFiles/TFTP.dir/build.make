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
CMAKE_SOURCE_DIR = /mnt/c/Users/mahdi/Desktop/ENSEA/2024-2025/TpSynthese/TFTP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/mahdi/Desktop/ENSEA/2024-2025/TpSynthese/TFTP/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TFTP.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TFTP.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TFTP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TFTP.dir/flags.make

CMakeFiles/TFTP.dir/main.c.o: CMakeFiles/TFTP.dir/flags.make
CMakeFiles/TFTP.dir/main.c.o: ../main.c
CMakeFiles/TFTP.dir/main.c.o: CMakeFiles/TFTP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/mahdi/Desktop/ENSEA/2024-2025/TpSynthese/TFTP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TFTP.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TFTP.dir/main.c.o -MF CMakeFiles/TFTP.dir/main.c.o.d -o CMakeFiles/TFTP.dir/main.c.o -c /mnt/c/Users/mahdi/Desktop/ENSEA/2024-2025/TpSynthese/TFTP/main.c

CMakeFiles/TFTP.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TFTP.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/mahdi/Desktop/ENSEA/2024-2025/TpSynthese/TFTP/main.c > CMakeFiles/TFTP.dir/main.c.i

CMakeFiles/TFTP.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TFTP.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/mahdi/Desktop/ENSEA/2024-2025/TpSynthese/TFTP/main.c -o CMakeFiles/TFTP.dir/main.c.s

CMakeFiles/TFTP.dir/gettftp.c.o: CMakeFiles/TFTP.dir/flags.make
CMakeFiles/TFTP.dir/gettftp.c.o: ../gettftp.c
CMakeFiles/TFTP.dir/gettftp.c.o: CMakeFiles/TFTP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/mahdi/Desktop/ENSEA/2024-2025/TpSynthese/TFTP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/TFTP.dir/gettftp.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TFTP.dir/gettftp.c.o -MF CMakeFiles/TFTP.dir/gettftp.c.o.d -o CMakeFiles/TFTP.dir/gettftp.c.o -c /mnt/c/Users/mahdi/Desktop/ENSEA/2024-2025/TpSynthese/TFTP/gettftp.c

CMakeFiles/TFTP.dir/gettftp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TFTP.dir/gettftp.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/mahdi/Desktop/ENSEA/2024-2025/TpSynthese/TFTP/gettftp.c > CMakeFiles/TFTP.dir/gettftp.c.i

CMakeFiles/TFTP.dir/gettftp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TFTP.dir/gettftp.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/mahdi/Desktop/ENSEA/2024-2025/TpSynthese/TFTP/gettftp.c -o CMakeFiles/TFTP.dir/gettftp.c.s

CMakeFiles/TFTP.dir/puttftp.c.o: CMakeFiles/TFTP.dir/flags.make
CMakeFiles/TFTP.dir/puttftp.c.o: ../puttftp.c
CMakeFiles/TFTP.dir/puttftp.c.o: CMakeFiles/TFTP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/mahdi/Desktop/ENSEA/2024-2025/TpSynthese/TFTP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/TFTP.dir/puttftp.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TFTP.dir/puttftp.c.o -MF CMakeFiles/TFTP.dir/puttftp.c.o.d -o CMakeFiles/TFTP.dir/puttftp.c.o -c /mnt/c/Users/mahdi/Desktop/ENSEA/2024-2025/TpSynthese/TFTP/puttftp.c

CMakeFiles/TFTP.dir/puttftp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TFTP.dir/puttftp.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/mahdi/Desktop/ENSEA/2024-2025/TpSynthese/TFTP/puttftp.c > CMakeFiles/TFTP.dir/puttftp.c.i

CMakeFiles/TFTP.dir/puttftp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TFTP.dir/puttftp.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/mahdi/Desktop/ENSEA/2024-2025/TpSynthese/TFTP/puttftp.c -o CMakeFiles/TFTP.dir/puttftp.c.s

# Object files for target TFTP
TFTP_OBJECTS = \
"CMakeFiles/TFTP.dir/main.c.o" \
"CMakeFiles/TFTP.dir/gettftp.c.o" \
"CMakeFiles/TFTP.dir/puttftp.c.o"

# External object files for target TFTP
TFTP_EXTERNAL_OBJECTS =

TFTP: CMakeFiles/TFTP.dir/main.c.o
TFTP: CMakeFiles/TFTP.dir/gettftp.c.o
TFTP: CMakeFiles/TFTP.dir/puttftp.c.o
TFTP: CMakeFiles/TFTP.dir/build.make
TFTP: CMakeFiles/TFTP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/mahdi/Desktop/ENSEA/2024-2025/TpSynthese/TFTP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable TFTP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TFTP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TFTP.dir/build: TFTP
.PHONY : CMakeFiles/TFTP.dir/build

CMakeFiles/TFTP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TFTP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TFTP.dir/clean

CMakeFiles/TFTP.dir/depend:
	cd /mnt/c/Users/mahdi/Desktop/ENSEA/2024-2025/TpSynthese/TFTP/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/mahdi/Desktop/ENSEA/2024-2025/TpSynthese/TFTP /mnt/c/Users/mahdi/Desktop/ENSEA/2024-2025/TpSynthese/TFTP /mnt/c/Users/mahdi/Desktop/ENSEA/2024-2025/TpSynthese/TFTP/cmake-build-debug /mnt/c/Users/mahdi/Desktop/ENSEA/2024-2025/TpSynthese/TFTP/cmake-build-debug /mnt/c/Users/mahdi/Desktop/ENSEA/2024-2025/TpSynthese/TFTP/cmake-build-debug/CMakeFiles/TFTP.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TFTP.dir/depend

