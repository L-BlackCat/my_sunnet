# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /home/cmake/bin/cmake

# The command to remove a file.
RM = /home/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /usr/local/c_lua_demo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /usr/local/c_lua_demo/build

# Include any dependencies generated for this target.
include CMakeFiles/my_sunnet.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/my_sunnet.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/my_sunnet.dir/flags.make

CMakeFiles/my_sunnet.dir/src/com.blackCat.core/ConnWriter.cpp.o: CMakeFiles/my_sunnet.dir/flags.make
CMakeFiles/my_sunnet.dir/src/com.blackCat.core/ConnWriter.cpp.o: ../src/com.blackCat.core/ConnWriter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/usr/local/c_lua_demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/my_sunnet.dir/src/com.blackCat.core/ConnWriter.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_sunnet.dir/src/com.blackCat.core/ConnWriter.cpp.o -c /usr/local/c_lua_demo/src/com.blackCat.core/ConnWriter.cpp

CMakeFiles/my_sunnet.dir/src/com.blackCat.core/ConnWriter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_sunnet.dir/src/com.blackCat.core/ConnWriter.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /usr/local/c_lua_demo/src/com.blackCat.core/ConnWriter.cpp > CMakeFiles/my_sunnet.dir/src/com.blackCat.core/ConnWriter.cpp.i

CMakeFiles/my_sunnet.dir/src/com.blackCat.core/ConnWriter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_sunnet.dir/src/com.blackCat.core/ConnWriter.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /usr/local/c_lua_demo/src/com.blackCat.core/ConnWriter.cpp -o CMakeFiles/my_sunnet.dir/src/com.blackCat.core/ConnWriter.cpp.s

CMakeFiles/my_sunnet.dir/src/com.blackCat.core/LuaApi.cpp.o: CMakeFiles/my_sunnet.dir/flags.make
CMakeFiles/my_sunnet.dir/src/com.blackCat.core/LuaApi.cpp.o: ../src/com.blackCat.core/LuaApi.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/usr/local/c_lua_demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/my_sunnet.dir/src/com.blackCat.core/LuaApi.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_sunnet.dir/src/com.blackCat.core/LuaApi.cpp.o -c /usr/local/c_lua_demo/src/com.blackCat.core/LuaApi.cpp

CMakeFiles/my_sunnet.dir/src/com.blackCat.core/LuaApi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_sunnet.dir/src/com.blackCat.core/LuaApi.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /usr/local/c_lua_demo/src/com.blackCat.core/LuaApi.cpp > CMakeFiles/my_sunnet.dir/src/com.blackCat.core/LuaApi.cpp.i

CMakeFiles/my_sunnet.dir/src/com.blackCat.core/LuaApi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_sunnet.dir/src/com.blackCat.core/LuaApi.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /usr/local/c_lua_demo/src/com.blackCat.core/LuaApi.cpp -o CMakeFiles/my_sunnet.dir/src/com.blackCat.core/LuaApi.cpp.s

CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Main.cpp.o: CMakeFiles/my_sunnet.dir/flags.make
CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Main.cpp.o: ../src/com.blackCat.core/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/usr/local/c_lua_demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Main.cpp.o -c /usr/local/c_lua_demo/src/com.blackCat.core/Main.cpp

CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /usr/local/c_lua_demo/src/com.blackCat.core/Main.cpp > CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Main.cpp.i

CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /usr/local/c_lua_demo/src/com.blackCat.core/Main.cpp -o CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Main.cpp.s

CMakeFiles/my_sunnet.dir/src/com.blackCat.core/MySunnet.cpp.o: CMakeFiles/my_sunnet.dir/flags.make
CMakeFiles/my_sunnet.dir/src/com.blackCat.core/MySunnet.cpp.o: ../src/com.blackCat.core/MySunnet.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/usr/local/c_lua_demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/my_sunnet.dir/src/com.blackCat.core/MySunnet.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_sunnet.dir/src/com.blackCat.core/MySunnet.cpp.o -c /usr/local/c_lua_demo/src/com.blackCat.core/MySunnet.cpp

CMakeFiles/my_sunnet.dir/src/com.blackCat.core/MySunnet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_sunnet.dir/src/com.blackCat.core/MySunnet.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /usr/local/c_lua_demo/src/com.blackCat.core/MySunnet.cpp > CMakeFiles/my_sunnet.dir/src/com.blackCat.core/MySunnet.cpp.i

CMakeFiles/my_sunnet.dir/src/com.blackCat.core/MySunnet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_sunnet.dir/src/com.blackCat.core/MySunnet.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /usr/local/c_lua_demo/src/com.blackCat.core/MySunnet.cpp -o CMakeFiles/my_sunnet.dir/src/com.blackCat.core/MySunnet.cpp.s

CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Service.cpp.o: CMakeFiles/my_sunnet.dir/flags.make
CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Service.cpp.o: ../src/com.blackCat.core/Service.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/usr/local/c_lua_demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Service.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Service.cpp.o -c /usr/local/c_lua_demo/src/com.blackCat.core/Service.cpp

CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Service.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Service.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /usr/local/c_lua_demo/src/com.blackCat.core/Service.cpp > CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Service.cpp.i

CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Service.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Service.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /usr/local/c_lua_demo/src/com.blackCat.core/Service.cpp -o CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Service.cpp.s

CMakeFiles/my_sunnet.dir/src/com.blackCat.core/SocketWorker.cpp.o: CMakeFiles/my_sunnet.dir/flags.make
CMakeFiles/my_sunnet.dir/src/com.blackCat.core/SocketWorker.cpp.o: ../src/com.blackCat.core/SocketWorker.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/usr/local/c_lua_demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/my_sunnet.dir/src/com.blackCat.core/SocketWorker.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_sunnet.dir/src/com.blackCat.core/SocketWorker.cpp.o -c /usr/local/c_lua_demo/src/com.blackCat.core/SocketWorker.cpp

CMakeFiles/my_sunnet.dir/src/com.blackCat.core/SocketWorker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_sunnet.dir/src/com.blackCat.core/SocketWorker.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /usr/local/c_lua_demo/src/com.blackCat.core/SocketWorker.cpp > CMakeFiles/my_sunnet.dir/src/com.blackCat.core/SocketWorker.cpp.i

CMakeFiles/my_sunnet.dir/src/com.blackCat.core/SocketWorker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_sunnet.dir/src/com.blackCat.core/SocketWorker.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /usr/local/c_lua_demo/src/com.blackCat.core/SocketWorker.cpp -o CMakeFiles/my_sunnet.dir/src/com.blackCat.core/SocketWorker.cpp.s

CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Worker.cpp.o: CMakeFiles/my_sunnet.dir/flags.make
CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Worker.cpp.o: ../src/com.blackCat.core/Worker.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/usr/local/c_lua_demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Worker.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Worker.cpp.o -c /usr/local/c_lua_demo/src/com.blackCat.core/Worker.cpp

CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Worker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Worker.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /usr/local/c_lua_demo/src/com.blackCat.core/Worker.cpp > CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Worker.cpp.i

CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Worker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Worker.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /usr/local/c_lua_demo/src/com.blackCat.core/Worker.cpp -o CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Worker.cpp.s

# Object files for target my_sunnet
my_sunnet_OBJECTS = \
"CMakeFiles/my_sunnet.dir/src/com.blackCat.core/ConnWriter.cpp.o" \
"CMakeFiles/my_sunnet.dir/src/com.blackCat.core/LuaApi.cpp.o" \
"CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Main.cpp.o" \
"CMakeFiles/my_sunnet.dir/src/com.blackCat.core/MySunnet.cpp.o" \
"CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Service.cpp.o" \
"CMakeFiles/my_sunnet.dir/src/com.blackCat.core/SocketWorker.cpp.o" \
"CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Worker.cpp.o"

# External object files for target my_sunnet
my_sunnet_EXTERNAL_OBJECTS =

my_sunnet: CMakeFiles/my_sunnet.dir/src/com.blackCat.core/ConnWriter.cpp.o
my_sunnet: CMakeFiles/my_sunnet.dir/src/com.blackCat.core/LuaApi.cpp.o
my_sunnet: CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Main.cpp.o
my_sunnet: CMakeFiles/my_sunnet.dir/src/com.blackCat.core/MySunnet.cpp.o
my_sunnet: CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Service.cpp.o
my_sunnet: CMakeFiles/my_sunnet.dir/src/com.blackCat.core/SocketWorker.cpp.o
my_sunnet: CMakeFiles/my_sunnet.dir/src/com.blackCat.core/Worker.cpp.o
my_sunnet: CMakeFiles/my_sunnet.dir/build.make
my_sunnet: CMakeFiles/my_sunnet.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/usr/local/c_lua_demo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable my_sunnet"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/my_sunnet.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/my_sunnet.dir/build: my_sunnet

.PHONY : CMakeFiles/my_sunnet.dir/build

CMakeFiles/my_sunnet.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/my_sunnet.dir/cmake_clean.cmake
.PHONY : CMakeFiles/my_sunnet.dir/clean

CMakeFiles/my_sunnet.dir/depend:
	cd /usr/local/c_lua_demo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /usr/local/c_lua_demo /usr/local/c_lua_demo /usr/local/c_lua_demo/build /usr/local/c_lua_demo/build /usr/local/c_lua_demo/build/CMakeFiles/my_sunnet.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/my_sunnet.dir/depend

