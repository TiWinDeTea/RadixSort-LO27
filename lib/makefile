#general makefile template
CXX = gcc
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
EXENAME=$(EXESOURCE:.c=.exe)

export LD_LIBRARY_PATH="."

all: $(EXECUTABLE)
run: $(EXECUTABLE)
	@echo ""
	@echo "Executing "$(EXECUTABLE)
	sh exportLD.sh ./$(EXECUTABLE)

$(EXECUTABLE): $(LIBS) $(IO) $(EXEOBJECT)
	@echo -e "\nBuilding the executable..."
	@$(CXX) $(CFLAGS) $(CSTD) $(LIBSDIR) $(INCLUDEDIR) $(LIBS) $(IO) -o $(EXENAME) $(EXESOURCE)
	@echo "Done"
	@echo -e "\nYou may run the executable using 'make run'"

lib: $(LIBS) $(IO)
	@echo "Done"

$(EXEOBJECT): $(EXESOURCE) $(LIBS) $(IO)
	@echo "Building" $< "into" $@"..."
	@$(CXX) $(CFLAGS) $(CSTD) $(LIBS) $(IO) -o $@ $<

$(IO): $(IOOBJECT)
	@echo "Building" $< "into" $@"..."
	@$(CXX) $(CFLAGS) $(IOSTD) -shared -o $@ $<

$(IOOBJECT): $(IOSOURCE)
	@echo "Building" $< "into" $@"..."
	@$(CXX) $(CFLAGS) $(IOSTD) -o $@ -c $<

$(LIBS): $(LIBSOBJECTS)
	@echo "Building" $< "into" $@"..."
	@$(CXX) $(CFLAGS) $(CSTD) -shared -o $@ $<

$(LIBSOBJECTS): $(LIBSOURCE)
	@echo "Building" $< "into" $@"..."
	@$(CXX) $(CFLAGS) $(CSTD) -o $@ -c $<

clean:
	@echo "Cleaning temporary files"
	rm -f *.o *~ *.so *.exe
