#General makefile template
COMPILER = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fpic -fstack-protector-all -O3
CSTD= -ansi
IOSTD= -std=c99
LIBSDIR = -L. -L/usr/lib
INCLUDEDIR = -I. -I/usr/include

EXESOURCE=radixsortmain.c
LIBSOURCE=BaseNIntegerList.c
LIB2SOURCE=BaseNIntegerListOfList.c
IOSOURCE=io.c
EXECUTABLE=Radix-Sort.exe

LIB=lib$(LIBSOURCE:.c=.so)
LIB2=lib$(LIB2SOURCE:.c=.so)
IO=lib$(IOSOURCE:.c=.so)
EXEOBJECT=$(EXESOURCE:.c=.o)
LIBOBJECT=$(LIBSOURCE:.c=.o)
LIB2OBJECT=$(LIB2SOURCE:.c=.o)
IOOBJECT=$(IOSOURCE:.c=.o)

#Builds the executable
all: $(EXECUTABLE)
	@echo -e "\033[0m\nYou may run the executable using '\033[35mmake run\033[0m'"

#Builds and runs the executable
run: $(EXECUTABLE)
	@echo -e "\nExecuting "$(EXECUTABLE)
	@LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:. ./$(EXECUTABLE)

#Builds the executable
$(EXECUTABLE): $(LIB) $(LIB2) $(IO) $(EXEOBJECT)
	@echo -e "\nBuilding the executable..."
	@$(COMPILER) $(CFLAGS) $(CSTD) $(EXEOBJECT) $(LIBSDIR) -l$(LIBSOURCE:.c=) -l$(LIB2SOURCE:.c=) -l$(IOSOURCE:.c=) -o $(EXECUTABLE)
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
	@$(COMPILER) $(CFLAGS) $(IOSTD) $(LIBSDIR) $(INCLUDEDIR) -shared -o $@ $<

#Builds IO object files from IO source code files
$(IOOBJECT): $(IOSOURCE)
	@echo "Building" $< "into" $@"..."
	@$(COMPILER) $(CFLAGS) $(IOSTD) $(LIBSDIR) $(INCLUDEDIR) -o $@ -c $<

#Builds libraries files from libraries object files
$(LIB2): $(LIB2OBJECT)
	@echo "Building" $< "into" $@"..."
	@$(COMPILER) $(CFLAGS) $(CSTD) $(LIBSDIR) $(INCLUDEDIR) -shared -o $@ $<
$(LIB): $(LIBOBJECT)
	@echo "Building" $< "into" lib$@"..."
	@$(COMPILER) $(CFLAGS) $(CSTD) $(LIBSDIR) $(INCLUDEDIR) -shared -o $@ $<

#Builds libraries object files from libraries source code files
$(LIB2OBJECT): $(LIB2SOURCE)
	@echo "Building" $< "into" $@"..."
	@$(COMPILER) $(CFLAGS) $(CSTD) $(LIBSDIR) $(INCLUDEDIR) -o $@ -c $<
$(LIBOBJECT): $(LIBSOURCE)
	@echo "Building" $< "into" $@"..."
	@$(COMPILER) $(CFLAGS) $(CSTD) $(LIBSDIR) $(INCLUDEDIR) -o $@ -c $<

#Removes temporary files
clear: clean
clean:
	@echo "Cleaning files"
	@rm -f $(EXECUTABLE) $(LIB) $(LIB2) $(IO) $(IOOBJECT) $(LIB2OBJECT) $(LIBOBJECT) $(EXEOBJECT)
	@echo "Done"
