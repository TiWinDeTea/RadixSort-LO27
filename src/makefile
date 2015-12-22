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

EXECUTABLE=$(EXESOURCE:.c=.exe)
LIB=$(LIBSOURCE:.c=.so)
LIB2=$(LIB2SOURCE:.c=.so)
IO=$(IOSOURCE:.c=.so)
EXEOBJECT=$(EXESOURCE:.c=.o)
LIBOBJECT=$(LIBSOURCE:.c=.o)
LIB2OBJECT=$(LIB2SOURCE:.c=.o)
IOOBJECT=$(IOSOURCE:.c=.o)

#Builds the executable
all: $(EXECUTABLE)
	@echo -e "\033[0m\nYou may run the executable using '\033[35mmake run\033[0m' or '\033[35m./run.sh "$(EXECUTABLE)"\033[0m'."

#Builds and runs the executable
run: $(EXECUTABLE)
	@echo -e "\nExecuting "$(EXECUTABLE)
	LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:. ./$(EXECUTABLE)

#Builds the executable
$(EXECUTABLE): lib$(LIB) lib$(LIB2) lib$(IO) $(EXEOBJECT)
	@echo -e "\nBuilding the executable..."
	@$(COMPILER) $(CFLAGS) $(CSTD) $(EXEOBJECT) $(LIBSDIR) -l$(LIB:.so=) -l$(LIB2:.so=) -l$(IO:.so=) -o $(EXECUTABLE)
	@echo "Done"

#Builds libraries
libs: lib
lib: lib$(LIB) lib$(LIB2) lib$(IO)
	@echo "Done"

#Builds executable object files from executable source code
$(EXEOBJECT): $(EXESOURCE)
	@echo "Building" $< "into" $@"..."
	@$(COMPILER) $(CFLAGS) $(CSTD) -o $@ -c $<

#Builds IO libraries files from IO objects code files
lib$(IO): $(IOOBJECT)
	@echo "Building" $< "into" $@"..."
	@$(COMPILER) $(CFLAGS) $(IOSTD) -shared -o $@ $<

#Builds IO object files from IO source code files
$(IOOBJECT): $(IOSOURCE)
	@echo "Building" $< "into" $@"..."
	@$(COMPILER) $(CFLAGS) $(IOSTD) -o $@ -c $<

#Builds libraries files from libraries object files
lib$(LIB2): $(LIB2OBJECT)
	@echo "Building" $< "into" $@"..."
	@$(COMPILER) $(CFLAGS) $(CSTD) -shared -o $@ $<
lib$(LIB): $(LIBOBJECT)
	@echo "Building" $< "into" lib$@"..."
	@$(COMPILER) $(CFLAGS) $(CSTD) -shared -o $@ $<

#Builds libraries object files from libraries source code files
$(LIB2OBJECT): $(LIB2SOURCE)
	@echo "Building" $< "into" $@"..."
	@$(COMPILER) $(CFLAGS) $(CSTD) -o $@ -c $<
$(LIBOBJECT): $(LIBSOURCE)
	@echo "Building" $< "into" $@"..."
	@$(COMPILER) $(CFLAGS) $(CSTD) -o $@ -c $<

#Removes temporary files
clear:clean
clean:
	@echo "Cleaning temporary files"
	@rm -f *.o *~ *.so *.exe
	@echo "Done"
