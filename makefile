# Compiler settings
CC = g++
CXXFLAGS = -std=c++17 -I. -g

# Makefile settings
APPNAME = app
EXT = .cpp
SRCDIR = ./src

# preview widgets
OBJDIR = ./obj

# Linking lib
LDFLAGS =  -lwthttp -lwt -lwtdbo -lwtdbosqlite3 -lpthread

# Runtime lib
RLIB = --docroot . -c ./wt_config.xml --http-address 0.0.0.0 --http-port 9090

############## Creating variables #############
SRC = $(wildcard $(SRCDIR)/*$(EXT)) 
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=$(OBJDIR)/%.d)

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ) 
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Creates the dependecy rules
$(OBJDIR)/%.d: $(SRCDIR)/%$(EXT)
	@$(CXX) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@

# Includes all .h files
-include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT) 
	$(CC) $(CXXFLAGS) -o $@ -c $<

################## Run #################
run:
	./$(APPNAME) $(RLIB)

dbg:
	gdb ./$(APPNAME)

.PHONY: gen_obj_dir
gen_obj_dir:
	mkdir -p $(OBJDIR)

################### Cleaning rules ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(APPNAME) $(DEP) $(OBJ)

cleanDependencies:
	$(RM) $(DEP)

################### Display variables ###################
echo:
	@for dep in $(DEP); do \
		echo $$dep; \
	done