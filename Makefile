# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = "/Users/wuzishu/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-2/203.8084.11/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/wuzishu/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-2/203.8084.11/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/wuzishu/sources/study

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/wuzishu/sources/study

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	"/Users/wuzishu/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-2/203.8084.11/CLion.app/Contents/bin/cmake/mac/bin/cmake" --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	"/Users/wuzishu/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-2/203.8084.11/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/wuzishu/sources/study/CMakeFiles /Users/wuzishu/sources/study/CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/wuzishu/sources/study/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named study

# Build rule for target.
study: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 study
.PHONY : study

# fast build rule for target.
study/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/build
.PHONY : study/fast

Box.o: Box.cpp.o

.PHONY : Box.o

# target to build an object file
Box.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/Box.cpp.o
.PHONY : Box.cpp.o

Box.i: Box.cpp.i

.PHONY : Box.i

# target to preprocess a source file
Box.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/Box.cpp.i
.PHONY : Box.cpp.i

Box.s: Box.cpp.s

.PHONY : Box.s

# target to generate assembly for a file
Box.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/Box.cpp.s
.PHONY : Box.cpp.s

Shape.o: Shape.cpp.o

.PHONY : Shape.o

# target to build an object file
Shape.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/Shape.cpp.o
.PHONY : Shape.cpp.o

Shape.i: Shape.cpp.i

.PHONY : Shape.i

# target to preprocess a source file
Shape.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/Shape.cpp.i
.PHONY : Shape.cpp.i

Shape.s: Shape.cpp.s

.PHONY : Shape.s

# target to generate assembly for a file
Shape.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/Shape.cpp.s
.PHONY : Shape.cpp.s

array_metric.o: array_metric.cc.o

.PHONY : array_metric.o

# target to build an object file
array_metric.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/array_metric.cc.o
.PHONY : array_metric.cc.o

array_metric.i: array_metric.cc.i

.PHONY : array_metric.i

# target to preprocess a source file
array_metric.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/array_metric.cc.i
.PHONY : array_metric.cc.i

array_metric.s: array_metric.cc.s

.PHONY : array_metric.s

# target to generate assembly for a file
array_metric.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/array_metric.cc.s
.PHONY : array_metric.cc.s

bucket_leap_array.o: bucket_leap_array.cc.o

.PHONY : bucket_leap_array.o

# target to build an object file
bucket_leap_array.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/bucket_leap_array.cc.o
.PHONY : bucket_leap_array.cc.o

bucket_leap_array.i: bucket_leap_array.cc.i

.PHONY : bucket_leap_array.i

# target to preprocess a source file
bucket_leap_array.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/bucket_leap_array.cc.i
.PHONY : bucket_leap_array.cc.i

bucket_leap_array.s: bucket_leap_array.cc.s

.PHONY : bucket_leap_array.s

# target to generate assembly for a file
bucket_leap_array.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/bucket_leap_array.cc.s
.PHONY : bucket_leap_array.cc.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/main.cpp.s
.PHONY : main.cpp.s

metric_bucket.o: metric_bucket.cc.o

.PHONY : metric_bucket.o

# target to build an object file
metric_bucket.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/metric_bucket.cc.o
.PHONY : metric_bucket.cc.o

metric_bucket.i: metric_bucket.cc.i

.PHONY : metric_bucket.i

# target to preprocess a source file
metric_bucket.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/metric_bucket.cc.i
.PHONY : metric_bucket.cc.i

metric_bucket.s: metric_bucket.cc.s

.PHONY : metric_bucket.s

# target to generate assembly for a file
metric_bucket.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/metric_bucket.cc.s
.PHONY : metric_bucket.cc.s

stastic_node.o: stastic_node.cc.o

.PHONY : stastic_node.o

# target to build an object file
stastic_node.cc.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/stastic_node.cc.o
.PHONY : stastic_node.cc.o

stastic_node.i: stastic_node.cc.i

.PHONY : stastic_node.i

# target to preprocess a source file
stastic_node.cc.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/stastic_node.cc.i
.PHONY : stastic_node.cc.i

stastic_node.s: stastic_node.cc.s

.PHONY : stastic_node.s

# target to generate assembly for a file
stastic_node.cc.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/study.dir/build.make CMakeFiles/study.dir/stastic_node.cc.s
.PHONY : stastic_node.cc.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... study"
	@echo "... Box.o"
	@echo "... Box.i"
	@echo "... Box.s"
	@echo "... Shape.o"
	@echo "... Shape.i"
	@echo "... Shape.s"
	@echo "... array_metric.o"
	@echo "... array_metric.i"
	@echo "... array_metric.s"
	@echo "... bucket_leap_array.o"
	@echo "... bucket_leap_array.i"
	@echo "... bucket_leap_array.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... metric_bucket.o"
	@echo "... metric_bucket.i"
	@echo "... metric_bucket.s"
	@echo "... stastic_node.o"
	@echo "... stastic_node.i"
	@echo "... stastic_node.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

