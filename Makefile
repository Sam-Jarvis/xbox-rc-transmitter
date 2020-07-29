# Generic Makefile
#
# Author: yanick.rochon@gmail.com, Date: 2011-08-10
# Edited: samjarvis.nam@gmail.com, Date: 2020-07-16
#
# Changelog :
#   2010-11-05 - first version
#   2011-08-10 - added structure : sources, objects, binaries
#                thanks to http://stackoverflow.com/users/128940/beta
#   2017-04-24 - changed order of linker params
#
#	2020-07-16 - added flags, fixed tabs
# ------------------------------------------------

# project name (generate executable with this name)
TARGET   = xbox-one-s

CC       = gcc
# compiling flags here
CFLAGS   = -lusb-1.0 -lrf24 -lstdc++ -Wall -I.

LINKER   = gcc
# linking flags here
LFLAGS   = -lusb-1.0 -lrf24 -lstdc++ -Wall -I. -lm

# change these to proper directories where each file should be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.hpp)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm       = rm -f

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"