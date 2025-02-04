# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.15.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.15.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/zhanmingming/code/EmCache

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/zhanmingming/code/EmCache/build

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/local/Cellar/cmake/3.15.4/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/local/Cellar/cmake/3.15.4/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/Cellar/cmake/3.15.4/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/local/Cellar/cmake/3.15.4/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/local/Cellar/cmake/3.15.4/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/local/Cellar/cmake/3.15.4/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/local/Cellar/cmake/3.15.4/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/local/Cellar/cmake/3.15.4/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components

.PHONY : list_install_components/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/zhanmingming/code/EmCache/build/CMakeFiles /Users/zhanmingming/code/EmCache/build/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/zhanmingming/code/EmCache/build/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named emcache

# Build rule for target.
emcache: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 emcache
.PHONY : emcache

# fast build rule for target.
emcache/fast:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/build
.PHONY : emcache/fast

src/CacheManager.o: src/CacheManager.cpp.o

.PHONY : src/CacheManager.o

# target to build an object file
src/CacheManager.cpp.o:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/CacheManager.cpp.o
.PHONY : src/CacheManager.cpp.o

src/CacheManager.i: src/CacheManager.cpp.i

.PHONY : src/CacheManager.i

# target to preprocess a source file
src/CacheManager.cpp.i:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/CacheManager.cpp.i
.PHONY : src/CacheManager.cpp.i

src/CacheManager.s: src/CacheManager.cpp.s

.PHONY : src/CacheManager.s

# target to generate assembly for a file
src/CacheManager.cpp.s:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/CacheManager.cpp.s
.PHONY : src/CacheManager.cpp.s

src/CloseableThread.o: src/CloseableThread.cpp.o

.PHONY : src/CloseableThread.o

# target to build an object file
src/CloseableThread.cpp.o:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/CloseableThread.cpp.o
.PHONY : src/CloseableThread.cpp.o

src/CloseableThread.i: src/CloseableThread.cpp.i

.PHONY : src/CloseableThread.i

# target to preprocess a source file
src/CloseableThread.cpp.i:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/CloseableThread.cpp.i
.PHONY : src/CloseableThread.cpp.i

src/CloseableThread.s: src/CloseableThread.cpp.s

.PHONY : src/CloseableThread.s

# target to generate assembly for a file
src/CloseableThread.cpp.s:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/CloseableThread.cpp.s
.PHONY : src/CloseableThread.cpp.s

src/ConditionVariable.o: src/ConditionVariable.cpp.o

.PHONY : src/ConditionVariable.o

# target to build an object file
src/ConditionVariable.cpp.o:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/ConditionVariable.cpp.o
.PHONY : src/ConditionVariable.cpp.o

src/ConditionVariable.i: src/ConditionVariable.cpp.i

.PHONY : src/ConditionVariable.i

# target to preprocess a source file
src/ConditionVariable.cpp.i:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/ConditionVariable.cpp.i
.PHONY : src/ConditionVariable.cpp.i

src/ConditionVariable.s: src/ConditionVariable.cpp.s

.PHONY : src/ConditionVariable.s

# target to generate assembly for a file
src/ConditionVariable.cpp.s:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/ConditionVariable.cpp.s
.PHONY : src/ConditionVariable.cpp.s

src/HandleTable.o: src/HandleTable.cpp.o

.PHONY : src/HandleTable.o

# target to build an object file
src/HandleTable.cpp.o:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/HandleTable.cpp.o
.PHONY : src/HandleTable.cpp.o

src/HandleTable.i: src/HandleTable.cpp.i

.PHONY : src/HandleTable.i

# target to preprocess a source file
src/HandleTable.cpp.i:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/HandleTable.cpp.i
.PHONY : src/HandleTable.cpp.i

src/HandleTable.s: src/HandleTable.cpp.s

.PHONY : src/HandleTable.s

# target to generate assembly for a file
src/HandleTable.cpp.s:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/HandleTable.cpp.s
.PHONY : src/HandleTable.cpp.s

src/Hash.o: src/Hash.cpp.o

.PHONY : src/Hash.o

# target to build an object file
src/Hash.cpp.o:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/Hash.cpp.o
.PHONY : src/Hash.cpp.o

src/Hash.i: src/Hash.cpp.i

.PHONY : src/Hash.i

# target to preprocess a source file
src/Hash.cpp.i:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/Hash.cpp.i
.PHONY : src/Hash.cpp.i

src/Hash.s: src/Hash.cpp.s

.PHONY : src/Hash.s

# target to generate assembly for a file
src/Hash.cpp.s:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/Hash.cpp.s
.PHONY : src/Hash.cpp.s

src/HashLRUCache.o: src/HashLRUCache.cpp.o

.PHONY : src/HashLRUCache.o

# target to build an object file
src/HashLRUCache.cpp.o:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/HashLRUCache.cpp.o
.PHONY : src/HashLRUCache.cpp.o

src/HashLRUCache.i: src/HashLRUCache.cpp.i

.PHONY : src/HashLRUCache.i

# target to preprocess a source file
src/HashLRUCache.cpp.i:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/HashLRUCache.cpp.i
.PHONY : src/HashLRUCache.cpp.i

src/HashLRUCache.s: src/HashLRUCache.cpp.s

.PHONY : src/HashLRUCache.s

# target to generate assembly for a file
src/HashLRUCache.cpp.s:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/HashLRUCache.cpp.s
.PHONY : src/HashLRUCache.cpp.s

src/HashTable.o: src/HashTable.cpp.o

.PHONY : src/HashTable.o

# target to build an object file
src/HashTable.cpp.o:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/HashTable.cpp.o
.PHONY : src/HashTable.cpp.o

src/HashTable.i: src/HashTable.cpp.i

.PHONY : src/HashTable.i

# target to preprocess a source file
src/HashTable.cpp.i:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/HashTable.cpp.i
.PHONY : src/HashTable.cpp.i

src/HashTable.s: src/HashTable.cpp.s

.PHONY : src/HashTable.s

# target to generate assembly for a file
src/HashTable.cpp.s:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/HashTable.cpp.s
.PHONY : src/HashTable.cpp.s

src/LRUCache.o: src/LRUCache.cpp.o

.PHONY : src/LRUCache.o

# target to build an object file
src/LRUCache.cpp.o:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/LRUCache.cpp.o
.PHONY : src/LRUCache.cpp.o

src/LRUCache.i: src/LRUCache.cpp.i

.PHONY : src/LRUCache.i

# target to preprocess a source file
src/LRUCache.cpp.i:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/LRUCache.cpp.i
.PHONY : src/LRUCache.cpp.i

src/LRUCache.s: src/LRUCache.cpp.s

.PHONY : src/LRUCache.s

# target to generate assembly for a file
src/LRUCache.cpp.s:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/LRUCache.cpp.s
.PHONY : src/LRUCache.cpp.s

src/Mutex.o: src/Mutex.cpp.o

.PHONY : src/Mutex.o

# target to build an object file
src/Mutex.cpp.o:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/Mutex.cpp.o
.PHONY : src/Mutex.cpp.o

src/Mutex.i: src/Mutex.cpp.i

.PHONY : src/Mutex.i

# target to preprocess a source file
src/Mutex.cpp.i:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/Mutex.cpp.i
.PHONY : src/Mutex.cpp.i

src/Mutex.s: src/Mutex.cpp.s

.PHONY : src/Mutex.s

# target to generate assembly for a file
src/Mutex.cpp.s:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/Mutex.cpp.s
.PHONY : src/Mutex.cpp.s

src/ReadWriteLock.o: src/ReadWriteLock.cpp.o

.PHONY : src/ReadWriteLock.o

# target to build an object file
src/ReadWriteLock.cpp.o:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/ReadWriteLock.cpp.o
.PHONY : src/ReadWriteLock.cpp.o

src/ReadWriteLock.i: src/ReadWriteLock.cpp.i

.PHONY : src/ReadWriteLock.i

# target to preprocess a source file
src/ReadWriteLock.cpp.i:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/ReadWriteLock.cpp.i
.PHONY : src/ReadWriteLock.cpp.i

src/ReadWriteLock.s: src/ReadWriteLock.cpp.s

.PHONY : src/ReadWriteLock.s

# target to generate assembly for a file
src/ReadWriteLock.cpp.s:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/ReadWriteLock.cpp.s
.PHONY : src/ReadWriteLock.cpp.s

src/SysTem.o: src/SysTem.cpp.o

.PHONY : src/SysTem.o

# target to build an object file
src/SysTem.cpp.o:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/SysTem.cpp.o
.PHONY : src/SysTem.cpp.o

src/SysTem.i: src/SysTem.cpp.i

.PHONY : src/SysTem.i

# target to preprocess a source file
src/SysTem.cpp.i:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/SysTem.cpp.i
.PHONY : src/SysTem.cpp.i

src/SysTem.s: src/SysTem.cpp.s

.PHONY : src/SysTem.s

# target to generate assembly for a file
src/SysTem.cpp.s:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/SysTem.cpp.s
.PHONY : src/SysTem.cpp.s

src/Thread.o: src/Thread.cpp.o

.PHONY : src/Thread.o

# target to build an object file
src/Thread.cpp.o:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/Thread.cpp.o
.PHONY : src/Thread.cpp.o

src/Thread.i: src/Thread.cpp.i

.PHONY : src/Thread.i

# target to preprocess a source file
src/Thread.cpp.i:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/Thread.cpp.i
.PHONY : src/Thread.cpp.i

src/Thread.s: src/Thread.cpp.s

.PHONY : src/Thread.s

# target to generate assembly for a file
src/Thread.cpp.s:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/Thread.cpp.s
.PHONY : src/Thread.cpp.s

src/Util.o: src/Util.cpp.o

.PHONY : src/Util.o

# target to build an object file
src/Util.cpp.o:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/Util.cpp.o
.PHONY : src/Util.cpp.o

src/Util.i: src/Util.cpp.i

.PHONY : src/Util.i

# target to preprocess a source file
src/Util.cpp.i:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/Util.cpp.i
.PHONY : src/Util.cpp.i

src/Util.s: src/Util.cpp.s

.PHONY : src/Util.s

# target to generate assembly for a file
src/Util.cpp.s:
	$(MAKE) -f CMakeFiles/emcache.dir/build.make CMakeFiles/emcache.dir/src/Util.cpp.s
.PHONY : src/Util.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... install/local"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... install/strip"
	@echo "... install"
	@echo "... list_install_components"
	@echo "... emcache"
	@echo "... src/CacheManager.o"
	@echo "... src/CacheManager.i"
	@echo "... src/CacheManager.s"
	@echo "... src/CloseableThread.o"
	@echo "... src/CloseableThread.i"
	@echo "... src/CloseableThread.s"
	@echo "... src/ConditionVariable.o"
	@echo "... src/ConditionVariable.i"
	@echo "... src/ConditionVariable.s"
	@echo "... src/HandleTable.o"
	@echo "... src/HandleTable.i"
	@echo "... src/HandleTable.s"
	@echo "... src/Hash.o"
	@echo "... src/Hash.i"
	@echo "... src/Hash.s"
	@echo "... src/HashLRUCache.o"
	@echo "... src/HashLRUCache.i"
	@echo "... src/HashLRUCache.s"
	@echo "... src/HashTable.o"
	@echo "... src/HashTable.i"
	@echo "... src/HashTable.s"
	@echo "... src/LRUCache.o"
	@echo "... src/LRUCache.i"
	@echo "... src/LRUCache.s"
	@echo "... src/Mutex.o"
	@echo "... src/Mutex.i"
	@echo "... src/Mutex.s"
	@echo "... src/ReadWriteLock.o"
	@echo "... src/ReadWriteLock.i"
	@echo "... src/ReadWriteLock.s"
	@echo "... src/SysTem.o"
	@echo "... src/SysTem.i"
	@echo "... src/SysTem.s"
	@echo "... src/Thread.o"
	@echo "... src/Thread.i"
	@echo "... src/Thread.s"
	@echo "... src/Util.o"
	@echo "... src/Util.i"
	@echo "... src/Util.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

