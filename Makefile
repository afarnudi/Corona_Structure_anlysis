TARGET=CSA

CXXFLAGS=-std=c++14 -O3
CXX = g++  

gsl_INSTALL_DIR=/usr/local/Cellar/gsl/2.6
LIBS = -lm  -lgsl -lgslcblas

BINDIR=bin
SRCDIR=source
INCDIR=include
OBJDIR=objects

INCDIRS=-I$(INCDIR) -I$(gsl_INSTALL_DIR)/include

SRCFILES=$(wildcard $(SRCDIR)/*.cpp) 
OBJFILES=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCFILES)) 
DEPFILES=$(wildcard $(INCDIR)/*.hpp) $(wildcard $(INCDIR)/*.h) $(wildcard $(INCDIR)/stb-master/*.h)


INC=-I$(DEPFILES) -I$(gsl_INSTALL_DIR)/include
LIB_DIR=-L$(gsl_INSTALL_DIR)/lib

all: $(BINDIR)/$(TARGET)
	@echo Finished!

$(BINDIR)/$(TARGET): $(OBJFILES)
	@$(CXX) $(CXXFLAGS) $(LIB_DIR) $(LIBS) $? -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)	
	$(CXX) $(CXXFLAGS) $(INCDIRS) -c $< -o $@

SUBDIR_ROOTS := objects 
DIRS := . $(shell find $(SUBDIR_ROOTS) -type d)
GARBAGE_PATTERNS := *.o
GARBAGE := $(foreach DIR,$(DIRS),$(addprefix $(DIR)/,$(GARBAGE_PATTERNS)))

clean: 
	rm -rf $(GARBAGE)
	rm bin/CSA
