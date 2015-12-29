#User-set variables ; OBJDIR and SOURCEDIR should end with '/'
COMPILER	= gcc
CFLAGS		= -Wall -Werror -Wextra -pedantic -fpic -fstack-protector-all -O3 -ansi
BINDIR		= bin/
OBJDIR		= obj/
SOURCEDIR	= src/
HEADERSDIR	= include/

EXESOURCENAME	= radixsortmain.c
LIBSOURCENAME	= BaseNIntegerList.c
LIB2SOURCENAME	= BaseNIntegerListOfList.c
IOSOURCENAME	= io.c
EXECUTABLENAME	= Radix-Sort.exe

LIBSDIR		= -L/usr/lib -L$(BINDIR)
INCLUDEDIR	= -I/usr/include -I$(HEADERSDIR)

#Generating variables from previous vars
EXESOURCE	= $(SOURCEDIR)$(EXESOURCENAME)
LIBSOURCE	= $(SOURCEDIR)$(LIBSOURCENAME)
LIB2SOURCE	= $(SOURCEDIR)$(LIB2SOURCENAME)
IOSOURCE	= $(SOURCEDIR)$(IOSOURCENAME)
EXECUTABLE	= $(BINDIR)$(EXECUTABLENAME)
LIB		= $(BINDIR)lib$(LIBSOURCENAME:.c=.so)
LIB2		= $(BINDIR)lib$(LIB2SOURCENAME:.c=.so)
IO		= $(BINDIR)lib$(IOSOURCENAME:.c=.so)
EXEOBJECT	= $(OBJDIR)$(EXESOURCENAME:.c=.o)
LIBOBJECT	= $(OBJDIR)$(LIBSOURCENAME:.c=.o)
LIB2OBJECT	= $(OBJDIR)$(LIB2SOURCENAME:.c=.o)
IOOBJECT	= $(OBJDIR)$(IOSOURCENAME:.c=.o)

#Builds the executable without echoing recipies by default
silent:
	@printf "Building without echoing recipes\n"
	@printf "Use '\033[35mmake all\033[0m' to build with recipes echoes\n"
	@printf "(you may need to use '\033[35mmake clean\033[0m' before rebuilding)\n\n"
	@make --silent all
#Builds the executable
all: $(EXECUTABLE)
	@printf "\033[0m\nYou may run the executable using '\033[35mmake run\033[0m'\n"

#Builds and runs the executable
run: $(EXECUTABLE)
	@printf "\nExecuting \033[33m$(EXECUTABLENAME)\033[0m\n"
	LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$(BINDIR) $(EXECUTABLE)

#Builds the executable
$(EXECUTABLE): $(LIB) $(LIB2) $(IO) $(EXEOBJECT)
	@printf "\nBuilding the executable into \033[33m $(EXECUTABLE)\033[0m...\n"
	$(COMPILER) $(CFLAGS) $(EXEOBJECT) $(LIBSDIR) -l$(IOSOURCENAME:.c=) -l$(LIBSOURCENAME:.c=) -l$(LIB2SOURCENAME:.c=) -o $(EXECUTABLE)
	@printf "Done\n"

#Builds libraries
libs:
	@printf "Building libraries without echoing recipes\n"
	@printf "Use '\033[35mmake lib\033[0m' to build with recipes echoes\n"
	@printf "(you may need to use '\033[35mmake clean\033[0m' before rebuilding)\n\n"
	@make --silent lib
lib: $(LIB) $(LIB2) $(IO)
	@printf "\nLibraries generated in '\033[35m$(BINDIR)\033[0m'\n"

#Builds executable object files from executable source code
$(EXEOBJECT): $(EXESOURCE)
	@printf "Building\033[33m $< \033[0minto\033[33m $@\033[0m...\n"
	$(COMPILER) $(CFLAGS) $(LIBSDIR) $(INCLUDEDIR) -o $@ -c $<

#Builds IO libraries files from IO objects code files
$(IO): $(IOOBJECT)
	@printf "Building\033[33m $< \033[0minto\033[33m $@\033[0m...\n"
	@mkdir -p $(BINDIR)
	$(COMPILER) $(CFLAGS) $(LIBSDIR) $(INCLUDEDIR) -shared -o $@ $<

#Builds IO object files from IO source code files
$(IOOBJECT): $(IOSOURCE)
	@printf "Building\033[33m $< \033[0minto\033[33m $@\033[0m...\n"
	@mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(LIBSDIR) $(INCLUDEDIR) -o $@ -c $<

#Builds libraries files from libraries object files
$(LIB2): $(LIB2OBJECT)
	@printf "Building\033[33m $< \033[0minto\033[33m $@\033[0m...\n"
	@mkdir -p $(BINDIR)
	$(COMPILER) $(CFLAGS) $(LIBSDIR) $(INCLUDEDIR) -shared -o $@ $<
$(LIB): $(LIBOBJECT)
	@printf "Building\033[33m $< \033[0minto\033[33m $@\033[0m...\n"
	@mkdir -p $(BINDIR)
	$(COMPILER) $(CFLAGS) $(LIBSDIR) $(INCLUDEDIR) -shared -o $@ $<

#Builds libraries object files from libraries source code files
$(LIB2OBJECT): $(LIB2SOURCE)
	@printf "Building\033[33m $< \033[0minto\033[33m $@\033[0m...\n"
	@mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(LIBSDIR) $(INCLUDEDIR) -o $@ -c $<
$(LIBOBJECT): $(LIBSOURCE)
	@printf "Building\033[33m $< \033[0minto\033[33m $@\033[0m...\n"
	@mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(LIBSDIR) $(INCLUDEDIR) -o $@ -c $<

#Removes temporary files
clear: clean
clean:
	@printf "Cleaning files...\n"
	@rm -f $(EXECUTABLE) $(LIB) $(LIB2) $(IO) $(IOOBJECT) $(LIB2OBJECT) $(LIBOBJECT) $(EXEOBJECT)
	@printf "Cleaning empty builds directories...\n"
	@rmdir -p $(OBJDIR) 2> /dev/null || true
	@rmdir -p $(BINDIR) 2> /dev/null || true
	@printf "Done\n"

#rebuilds the executable in debug and starts it
debug: CFLAGS=-Wall -Werror -Wextra -pedantic -fpic -fstack-protector-all -g
debug: clean $(EXECUTABLE)
	@LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$(BINDIR) gdb $(EXECUTABLE)


#help
?:help
h:help
help:
	@printf "\nRecipes :\n"
	@printf "  all          Builds all targets (lib$(LIB2SOURCENAME:.c=.so), lib$(LIBSOURCENAME:.c=.so), lib$(IOSOURCENAME:.c=.so), $(EXECUTABLENAME)) and their objects\n"
	@printf "  silent       Similar to 'make --silent all' (default)\n"
	@printf "  run          Executes the executable (builds it if required)\n"
	@printf "  lib          Builds all libs (lib$(LIB2SOURCENAME:.c=.so), lib$(LIBSOURCENAME:.c=.so), lib$(IOSOURCENAME:.c=.so))\n"
	@printf "  libs         Similar to 'make --silent lib'\n"
	@printf "  clean/clear  Cleans all generated files and folders (if empty)\n\n"
	@printf "Build folder for objects files : $(OBJDIR)\n"
	@printf "Build folder for elf files :     $(BINDIR)\n\n"
	@printf "Compiler and general compiler options :\n  $(COMPILER) $(CFLAGS)\n\n"
