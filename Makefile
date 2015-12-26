#User-set variables ; OBJDIR and SOURCEDIR should end with '/'
COMPILER	= gcc
CFLAGS		= -Wall -Werror -Wextra -pedantic -fpic -fstack-protector-all -O3
CSTD		= -ansi
IOSTD		= -std=c99
BINDIR		= bin/
OBJDIR		= obj/
SOURCEDIR	= src/
LIBSDIR		= -L. -L/usr/lib -L$(BINDIR)
INCLUDEDIR	= -I. -I/usr/include -I./include/

EXESOURCENAME	= radixsortmain.c
LIBSOURCENAME	= BaseNIntegerList.c
LIB2SOURCENAME	= BaseNIntegerListOfList.c
IOSOURCENAME	= io.c
EXECUTABLENAME	= Radix-Sort.exe

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
	@printf "Building without echoing recipies\n"
	@printf "Use '\033[35mmake all\033[0m' to build with recipies echoes\n\n"
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
	$(COMPILER) $(CFLAGS) $(CSTD) $(EXEOBJECT) $(LIBSDIR) -l$(IOSOURCENAME:.c=) -l$(LIBSOURCENAME:.c=) -l$(LIB2SOURCENAME:.c=) -o $(EXECUTABLE)
	@printf "Done\n"

#Builds libraries
libs: lib
lib: $(LIB) $(LIB2) $(IO)
	@printf "\nLibraries generated in '\033[35m$(BINDIR)\033[0m'\n"

#Builds executable object files from executable source code
$(EXEOBJECT): $(EXESOURCE)
	@printf "Building\033[33m $< \033[0minto\033[33m $@\033[0m...\n"
	$(COMPILER) $(CFLAGS) $(CSTD) $(LIBSDIR) $(INCLUDEDIR) -o $@ -c $<

#Builds IO libraries files from IO objects code files
$(IO): $(IOOBJECT)
	@printf "Building\033[33m $< \033[0minto\033[33m $@\033[0m...\n"
	@mkdir -p $(BINDIR)
	$(COMPILER) $(CFLAGS) $(IOSTD) $(LIBSDIR) $(INCLUDEDIR) -shared -o $@ $<

#Builds IO object files from IO source code files
$(IOOBJECT): $(IOSOURCE)
	@printf "Building\033[33m $< \033[0minto\033[33m $@\033[0m...\n"
	@mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(IOSTD) $(LIBSDIR) $(INCLUDEDIR) -o $@ -c $<

#Builds libraries files from libraries object files
$(LIB2): $(LIB2OBJECT)
	@printf "Building\033[33m $< \033[0minto\033[33m $@\033[0m...\n"
	@mkdir -p $(BINDIR)
	$(COMPILER) $(CFLAGS) $(CSTD) $(LIBSDIR) $(INCLUDEDIR) -shared -o $@ $<
$(LIB): $(LIBOBJECT)
	@printf "Building\033[33m $< \033[0minto\033[33m $@\033[0m...\n"
	@mkdir -p $(BINDIR)
	$(COMPILER) $(CFLAGS) $(CSTD) $(LIBSDIR) $(INCLUDEDIR) -shared -o $@ $<

#Builds libraries object files from libraries source code files
$(LIB2OBJECT): $(LIB2SOURCE)
	@printf "Building\033[33m $< \033[0minto\033[33m $@\033[0m...\n"
	@mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(CSTD) $(LIBSDIR) $(INCLUDEDIR) -o $@ -c $<
$(LIBOBJECT): $(LIBSOURCE)
	@printf "Building\033[33m $< \033[0minto\033[33m $@\033[0m...\n"
	@mkdir -p $(OBJDIR)
	$(COMPILER) $(CFLAGS) $(CSTD) $(LIBSDIR) $(INCLUDEDIR) -o $@ -c $<

#Removes temporary files
clear: clean
clean:
	@printf "Cleaning files...\n"
	@rm -f $(EXECUTABLE) $(LIB) $(LIB2) $(IO) $(IOOBJECT) $(LIB2OBJECT) $(LIBOBJECT) $(EXEOBJECT)
	@printf "Cleaning empty builds directories...\n"
	@(test -d $(OBJDIR) && rmdir -p --ignore-fail-on-non-empty $(OBJDIR) 2> /dev/null) || true
	@(test -d $(BINDIR) && rmdir -p --ignore-fail-on-non-empty $(BINDIR) 2> /dev/null) || true
	@printf "Done\n"
