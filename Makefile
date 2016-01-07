 #########################################################################################
 #                                                                                       #
 # General Makefile template, compiling up to 3 shared libraries together with           #
 # an executable, and giving access to various recipes.                                  #
 # Use 'make help' or 'make ?' or 'make h' for help.                                     #
 #                                                                                       #
 # Copyright (C) 2015 LAZARE Lucas (lazarelucas@yahoo.fr)                                #
 #                                                                                       #
 # This software is provided 'as-is', WITHOUT ANY EXPRESS OR IMPLIED WARRANTY.           #
 # In NO EVENT will the authors be held liable for any damages arising from the          #
 # use of this software.                                                                 #
 #                                                                                       #
 # Permission is granted to anyone to use this software for any purpose,                 #
 # including commercial applications, and to alter it and redistribute it freely,        #
 # subject to the following restrictions:                                                #
 #                                                                                       #
 # 1. The origin of this software must not be misrepresented;                            #
 # you must not claim that you wrote the original software.                              #
 # If you use this software in a product, an acknowledgment                              #
 # in the product documentation would be appreciated but is not required.                #
 #                                                                                       #
 # 2. Altered source versions must be plainly marked as such,                            #
 # and must not be misrepresented as being the original software.                        #
 #                                                                                       #
 # 3. This notice may not be removed or altered from any source distribution.            #
 #                                                                                       #
 #########################################################################################

# User-set variables ; OBJDIR and SOURCEDIR should end with '/'
# nb : DEBUGFLAG should contain the flag that tells the compiler to build in debug mode
# DARGS and LCARGS are the flags/arguments used together with your debugger and leakchecker.

EXESOURCENAME	= radixsortmain.c
LIBSOURCENAME	= BaseNIntegerList.c
LIB2SOURCENAME	= BaseNIntegerListOfList.c
LIB3SOURCENAME	= io.c
EXECUTABLENAME	= Radix-Sort.exe

EXEDIR		= bin/
LIBDIR		= lib/
OBJDIR		= obj/
SOURCEDIR	= src/
HEADERSDIR	= include/
LIBSDIR		= -L/usr/lib -L$(LIBDIR)
INCLUDEDIR	= -I/usr/include -I$(HEADERSDIR)

COMPILER	= gcc
CFLAGS		= -Wall -Werror -Wextra -pedantic -fpic -fstack-protector-all -O3 -ansi
DEBUGFLAG	= -g
DEBUGGER	= gdb
DARGS		= -se $(EXEDIR)$(EXECUTABLENAME)
LEAKCHECKER	= valgrind
LCARGS		= --leak-check=full --show-leak-kinds=all $(EXEDIR)$(EXECUTABLENAME)


# In most cases, you won't have to modify anything beyond this point.

# Other Variables
DISPLAY		= printf
RMDIR		= rmdir -p
MKDIR		= mkdir -p
RM		= rm -f
LIBPREFIX	= lib

# Generating variables from previous ones
EXESOURCE	= $(SOURCEDIR)$(EXESOURCENAME)
LIBSOURCE	= $(SOURCEDIR)$(LIBSOURCENAME)
LIB2SOURCE	= $(SOURCEDIR)$(LIB2SOURCENAME)
LIB3SOURCE	= $(SOURCEDIR)$(LIB3SOURCENAME)
EXECUTABLE	= $(EXEDIR)$(EXECUTABLENAME)
LIB		= $(LIBDIR)$(LIBPREFIX)$(LIBSOURCENAME:.c=.so)
LIB2		= $(LIBDIR)$(LIBPREFIX)$(LIB2SOURCENAME:.c=.so)
LIB3		= $(LIBDIR)$(LIBPREFIX)$(LIB3SOURCENAME:.c=.so)
EXEOBJECT	= $(OBJDIR)$(EXESOURCENAME:.c=.o)
LIBOBJECT	= $(OBJDIR)$(LIBSOURCENAME:.c=.o)
LIB2OBJECT	= $(OBJDIR)$(LIB2SOURCENAME:.c=.o)
LIB3OBJECT	= $(OBJDIR)$(LIB3SOURCENAME:.c=.o)

# Builds the executable without echoing recipies by default
.PHONY: silent
silent:
	@$(DISPLAY) "Building without echoing recipes\n"
	@$(DISPLAY) "Use '\033[35mmake all\033[0m' to build with recipes echoes\n"
	@$(DISPLAY) "(you may need to use '\033[35mmake clean\033[0m' before rebuilding)\n\n"
	@make --silent all
# Builds the executable
.PHONY: $(EXECUTABLENAME)
$(EXECUTABLENAME): all

.PHONY: all
all: $(EXECUTABLE)
	@$(DISPLAY) "\033[0m\nYou may run the executable using '\033[35mmake run\033[0m'\n"

# Builds and runs the executable
.PHONY: run
run: $(EXECUTABLE)
	@$(DISPLAY) "\nExecuting \033[33m$(EXECUTABLENAME)\033[0m\n"
	LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$(LIBDIR) $(EXECUTABLE)

# Builds the executable
$(EXECUTABLE): $(LIB) $(LIB2) $(LIB3) $(EXEOBJECT)
	@$(DISPLAY) "\nBuilding the executable into \033[33m $(EXECUTABLE)\033[0m...\n"
	@$(MKDIR) $(EXEDIR)
	$(COMPILER) $(CFLAGS) $(EXEOBJECT) $(LIBSDIR) -l$(LIB3SOURCENAME:.c=) -l$(LIBSOURCENAME:.c=) -l$(LIB2SOURCENAME:.c=) -o $(EXECUTABLE)
	@$(DISPLAY) "Done\n"

# Builds libraries
libs:
	@$(DISPLAY) "Building libraries without echoing recipes\n"
	@$(DISPLAY) "Use '\033[35mmake lib\033[0m' to build with recipes echoes\n"
	@$(DISPLAY) "(you may need to use '\033[35mmake clean\033[0m' before rebuilding)\n\n"
	@make --silent lib
lib: $(LIB) $(LIB2) $(LIB3)
	@$(DISPLAY) "\nLibraries generated in '\033[35m$(LIBDIR)\033[0m'\n"

# Builds executable object files from executable source code
$(EXEOBJECT): $(EXESOURCE)
	@$(DISPLAY) "Building\033[33m $< \033[0minto\033[33m $@\033[0m...\n"
	@$(MKDIR) $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(INCLUDEDIR) -o $@ -c $<

# Builds LIB3 libraries files from LIB3 objects code files
$(LIB3): $(LIB3OBJECT)
	@$(DISPLAY) "Building\033[33m $< \033[0minto\033[33m $@\033[0m...\n"
	@$(MKDIR) $(LIBDIR)
	$(COMPILER) $(CFLAGS) $(LIBSDIR) -shared -o $@ $<

# Builds LIB3 object files from LIB3 source code files
$(LIB3OBJECT): $(LIB3SOURCE)
	@$(DISPLAY) "Building\033[33m $< \033[0minto\033[33m $@\033[0m...\n"
	@$(MKDIR) $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(INCLUDEDIR) -o $@ -c $<

# Builds libraries files from libraries object files
$(LIB2): $(LIB2OBJECT)
	@$(DISPLAY) "Building\033[33m $< \033[0minto\033[33m $@\033[0m...\n"
	@$(MKDIR) $(LIBDIR)
	$(COMPILER) $(CFLAGS) $(LIBSDIR) -shared -o $@ $<
$(LIB): $(LIBOBJECT)
	@$(DISPLAY) "Building\033[33m $< \033[0minto\033[33m $@\033[0m...\n"
	@$(MKDIR) $(LIBDIR)
	$(COMPILER) $(CFLAGS) $(LIBSDIR) -shared -o $@ $<

# Builds libraries object files from libraries source code files
$(LIB2OBJECT): $(LIB2SOURCE)
	@$(DISPLAY) "Building\033[33m $< \033[0minto\033[33m $@\033[0m...\n"
	@$(MKDIR) $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(INCLUDEDIR) -o $@ -c $<
$(LIBOBJECT): $(LIBSOURCE)
	@$(DISPLAY) "Building\033[33m $< \033[0minto\033[33m $@\033[0m...\n"
	@$(MKDIR) $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(INCLUDEDIR) -o $@ -c $<

# Removes temporary files
.PHONY: clean
clear: clean
clean:
	@$(DISPLAY) "Cleaning files...\n"
	@$(RM) $(EXECUTABLE) $(LIB) $(LIB2) $(LIB3) $(LIB3OBJECT) $(LIB2OBJECT) $(LIBOBJECT) $(EXEOBJECT)
	@$(DISPLAY) "Cleaning empty builds directories...\n"
	@$(RMDIR) $(OBJDIR) 2> /dev/null || $(DISPLAY) "$(OBJDIR) wasn't deleted.\n"
	@$(RMDIR) $(EXEDIR) 2> /dev/null || $(DISPLAY) "$(EXEDIR) wasn't deleted.\n"
	@$(RMDIR) $(LIBDIR) 2> /dev/null || $(DISPLAY) "$(LIBDIR) wasn't deleted.\n"
	@$(DISPLAY) "Done\n"

# Rebuilds the executable in debug and starts it
.PHONY: debug
debug: CFLAGS += $(DEBUGFLAG)
debug: __building_in_debug__ clean $(EXECUTABLE)
	@$(DISPLAY) "Launching $(DEBUGGER) : \n"
	LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$(LIBDIR) $(DEBUGGER) $(DARGS)

# Starts the leakchecker
.PHONY: memleak
memleak: CFLAGS += $(DEBUGFLAG)
memleak: __building_in_debug__ clean $(EXECUTABLE)
	@$(DISPLAY) "Launching $(LEAKCHECKER) : \n"
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(LIBDIR) $(LEAKCHECKER) $(LCARGS)

.PHONY: __building_in_debug__
__building_in_debug__:
	@$(DISPLAY) "\033[1mCleaning and rebuilding with debug flag\033[0m\n"

# Help
.PHONY: ? h help
?:help
h:help
help:
	@$(DISPLAY) "\n\033[0m"
	@$(DISPLAY) "\033[1mRecipes :\033[0m\n"
	@$(DISPLAY) "  \033[36mall\033[0m          Builds all targets (lib$(LIB2SOURCENAME:.c=.so), lib$(LIBSOURCENAME:.c=.so), lib$(LIB3SOURCENAME:.c=.so), $(EXECUTABLENAME)) and their objects\n"
	@$(DISPLAY) "  \033[36msilent\033[0m       Similar to 'make --silent all' \033[31m(default)\033[0m\n"
	@$(DISPLAY) "  \033[36mrun\033[0m          Executes the executable (builds it if required)\n"
	@$(DISPLAY) "  \033[36mlib\033[0m          Builds all libs (lib$(LIB2SOURCENAME:.c=.so), lib$(LIBSOURCENAME:.c=.so), lib$(LIB3SOURCENAME:.c=.so))\n"
	@$(DISPLAY) "  \033[36mlibs\033[0m         Similar to 'make --silent lib'\n"
	@$(DISPLAY) "  \033[36mdebug\033[0m        Rebuilds the executable with the additionnal flag '$(DEBUGFLAG)' and runs $(DEBUGGER)\n"
	@$(DISPLAY) "  \033[36mmemleak\033[0m      Runs $(LEAKCHECKER)\n"
	@$(DISPLAY) "  \033[36mclean/clear\033[0m  Cleans all generated files and folders (if empty)\n\n"
	@$(DISPLAY) "\033[1mBuild folders\033[0m\n"
	@$(DISPLAY) "  objects files : \033[36m$(OBJDIR)\033[0m\n"
	@$(DISPLAY) "  libraries :     \033[36m$(LIBDIR)\033[0m\n"
	@$(DISPLAY) "  elf file :      \033[36m$(EXEDIR)\033[0m\n\n"
	@$(DISPLAY) "\033[1mCompiler and general compiler options :\n  \033[0m\033[36m$(COMPILER) $(CFLAGS)\033[0m\n\n"
	@$(DISPLAY) "\033[1mDebugger and debugger arguments :\n  \033[0m\033[36m$(DEBUGGER) $(DARGS)\033[0m\n\n"
	@$(DISPLAY) "\033[1mLeakChecker and leakchecker arguments :\n  \033[0m\033[36m$(LEAKCHECKER) $(LCARGS)\033[0m\n\n"
