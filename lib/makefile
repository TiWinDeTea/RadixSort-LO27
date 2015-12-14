#General makefile template
COMPILER = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -fPIC
CSTD= -ansi
IOSTD= -std=c99
LIBSDIR = -L. -L/usr/lib
INCLUDEDIR = -I. -I/usr/include

EXESOURCE=radixsortmain.c
LIBSOURCE=BaseNIntegerList.c BaseNIntegerListOfList.c
IOSOURCE=io.c

EXECUTABLE=$(EXESOURCE:.c=.exe)
LIBS=$(LIBSOURCE:.c=.so)
IO=$(IOSOURCE:.c=.so)
EXEOBJECT=$(EXESOURCE:.c=.o)
LIBSOBJECTS=$(LIBSOURCE:.c=.o)
IOOBJECT=$(IOSOURCE:.c=.o)

#Builds and runs the executable
run: $(EXECUTABLE)
	@echo -e "\nExecuting "$(EXECUTABLE)
	@sh run.sh $(EXECUTABLE)

#Builds the executable
all: $(EXECUTABLE)
	@echo -e "\033[0m\nYou may run the executable using '\033[35mmake run\033[0m' or '\033[35m./run.sh "$(EXECUTABLE)"\033[0m'."

#Builds the executable
$(EXECUTABLE): $(LIBS) $(IO) $(EXEOBJECT)
	@echo -e "\nBuilding the executable..."
	@$(COMPILER) $(CFLAGS) $(CSTD) $(LIBSDIR) $(INCLUDEDIR) $(LIBS) $(IO) -o $(EXECUTABLE) $(EXESOURCE)
	@echo "Done"

#Builds libraries
libs: lib
lib: $(LIBS) $(IO)
	@echo "Done"

#Builds executable object files from executable source code
$(EXEOBJECT): $(EXESOURCE)
	@echo "Building" $< "into" $@"..."
	@$(COMPILER) $(CFLAGS) $(CSTD) $(LIBS) $(IO) -o $@ $<

#Builds IO libraries files from IO objects code files
$(IO): $(IOOBJECT)
	@echo "Building" $< "into" $@"..."
	@$(COMPILER) $(CFLAGS) $(IOSTD) -shared -o $@ $<

#Builds IO object files from IO source code files
$(IOOBJECT): $(IOSOURCE)
	@echo "Building" $< "into" $@"..."
	@$(COMPILER) $(CFLAGS) $(IOSTD) -o $@ -c $<

#Builds libraries files from libraries object files
$(LIBS): $(LIBSOBJECTS)
	@echo "Building" $< "into" $@"..."
	@$(COMPILER) $(CFLAGS) $(CSTD) -shared -o $@ $<

#Builds libraries object files from libraries source code files
$(LIBSOBJECTS): $(LIBSOURCE)
	@echo "Building" $< "into" $@"..."
	@$(COMPILER) $(CFLAGS) $(CSTD) -o $@ -c $<

#Removes temporary files
clean:
	@echo "Cleaning temporary files"
	@rm -f *.o *~ *.so *.exe
	@echo "Done"
