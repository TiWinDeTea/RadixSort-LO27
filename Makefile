#General makefile template
COMPILER	= gcc
CFLAGS		= -Wall -Werror -Wextra -pedantic -fpic -fstack-protector-all -O3
CSTD		= -ansi
IOSTD		= -std=c99
BINDIR		= bin/
OBJDIR		= obj/
SOURCEDIR	= src/
LIBSDIR		= -L. -L/usr/lib -L./$(BINDIR)
INCLUDEDIR	= -I. -I/usr/include -I./include/

EXESOURCENAME	= radixsortmain.c
LIBSOURCENAME	= BaseNIntegerList.c
LIB2SOURCENAME	= BaseNIntegerListOfList.c
IOSOURCENAME	= io.c
EXECUTABLENAME	= Radix-Sort.exe

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

#Builds the executable
all: $(EXECUTABLE)
	@echo -e "\033[0m\nYou may run the executable using '\033[35mmake run\033[0m'"

#Builds and runs the executable
run: $(EXECUTABLE)
	@echo -e "\nExecuting "$(EXECUTABLE)
	@LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:./bin/ ./$(EXECUTABLE)

#Builds the executable
$(EXECUTABLE): $(LIB) $(LIB2) $(IO) $(EXEOBJECT)
	@echo -e "\nBuilding the executable..."
	@$(COMPILER) $(CFLAGS) $(CSTD) $(EXEOBJECT) $(LIBSDIR) -l$(IOSOURCENAME:.c=) -l$(LIBSOURCENAME:.c=) -l$(LIB2SOURCENAME:.c=) -o $(EXECUTABLE)
	@echo "Done"

#Builds libraries
libs: lib
lib: $(LIB) $(LIB2) $(IO)
	@echo "Done"

#Builds executable object files from executable source code
$(EXEOBJECT): $(EXESOURCE)
	@echo "Building" $< "into" $@"..."
	@$(COMPILER) $(CFLAGS) $(CSTD) $(LIBSDIR) $(INCLUDEDIR) -o $@ -c $<

#Builds IO libraries files from IO objects code files
$(IO): $(IOOBJECT)
	@echo "Building" $< "into" $@"..."
	@mkdir -p $(BINDIR)
	@$(COMPILER) $(CFLAGS) $(IOSTD) $(LIBSDIR) $(INCLUDEDIR) -shared -o $@ $<

#Builds IO object files from IO source code files
$(IOOBJECT): $(IOSOURCE)
	@echo "Building" $< "into" $@"..."
	@mkdir -p $(OBJDIR)
	@$(COMPILER) $(CFLAGS) $(IOSTD) $(LIBSDIR) $(INCLUDEDIR) -o $@ -c $<

#Builds libraries files from libraries object files
$(LIB2): $(LIB2OBJECT)
	@echo "Building" $< "into" $@"..."
	@mkdir -p $(BINDIR)
	@$(COMPILER) $(CFLAGS) $(CSTD) $(LIBSDIR) $(INCLUDEDIR) -shared -o $@ $<
$(LIB): $(LIBOBJECT)
	@echo "Building" $< "into" $@"..."
	@mkdir -p $(BINDIR)
	@$(COMPILER) $(CFLAGS) $(CSTD) $(LIBSDIR) $(INCLUDEDIR) -shared -o $@ $<

#Builds libraries object files from libraries source code files
$(LIB2OBJECT): $(LIB2SOURCE)
	@echo "Building" $< "into" $@"..."
	@mkdir -p $(OBJDIR)
	@$(COMPILER) $(CFLAGS) $(CSTD) $(LIBSDIR) $(INCLUDEDIR) -o $@ -c $<
$(LIBOBJECT): $(LIBSOURCE)
	@echo "Building" $< "into" $@"..."
	@mkdir -p $(OBJDIR)
	@$(COMPILER) $(CFLAGS) $(CSTD) $(LIBSDIR) $(INCLUDEDIR) -o $@ -c $<

#Removes temporary files
clear: clean
clean:
	@echo "Cleaning files"
	@rm -f $(EXECUTABLE) $(LIB) $(LIB2) $(IO) $(IOOBJECT) $(LIB2OBJECT) $(LIBOBJECT) $(EXEOBJECT)
	@echo "Done"
