##########################################################
# Name: Anthonian Universal C/C++ Makefile               #
# Description: Universal Makefile For Anthonian          #
#              C/C++ Projects                            #
# Download: wget https://gist.anth.dev/fs/c/Makefile     #
# Date: May 28, 2018                                     #
# Created with <3 by Anthony Kung                        #
# Author URI: https://anth.dev                           #
# License: Apache 2.0 (See /LICENSE.md for details)      #
##########################################################

# Define Executable Name
IAEXE := smallsh

# Define Standard Version
CVER := -std=gnu99

# Define Compiler (gcc or g++)
CC := gcc

# Define Source Directory (Where your program is)
SDIR := .

# Define Build Directory (Where you want the result to go)
BDIR := ./build

CFLAGS := -Wall -ansi -lncurses

# Find all C and C++ files
SRC := $(shell find $(SDIR) -name '*.cpp' -or -name '*.c')
OBJ := $(SRC:%=$(BDIR)/%.o)
DEP := $(OBJ:.o=.d)

# Include Directories
IDIR := $(shell find $(SDIR) -type d)
IFLAGS := $(addprefix -I, $(IDIR))
MFLAGS := $(IFLAGS) -MMD -MP

# Build
$(BDIR)/$(IAEXE): $(OBJ)
	$(CC) $(CVER) $(CFLAGS) $(OBJ) -o $@

# Get rid of annoying messages
-include $(DEP)

# For C Files
$(BDIR)/%.c.o: %.c
	mkdir -p $(BDIR)
	$(CC) $(CVER) $(MFLAGS) $(CFLAGS) -c $< -o $@

# For C++ Files
$(BDIR)/%.cpp.o: %.cpp
	mkdir -p $(BDIR)
	$(CC) $(CVER) $(MFLAGS) $(CFLAGS) -c $< -o $@

# Clean Up Build
.PHONY: clean
clean:
	rm -f $(BDIR)/*.out
	rm -f $(BDIR)/*.o
	rm -f $(BDIR)/*.d
	rm -f $(BDIR)/$(IAEXE)
	rm -rf $(BDIR)/kungc.movies.*
	rm -f $(BDIR)/*.txt

# Delete Entire Build Directory (BEWARE OF YOUR ACTION)
.PHONY: cleandir
cleandir:
	rm -rf $(BDIR)

# Run Program With Logs
.PHONY: run
run:
	mkdir -p $(SDIR)/logs
	echo "Log File: " $(SDIR)/logs/$$(date +%Y-%m-%d-%H:%M:%S)-error.log
	$(BDIR)/$(IAEXE) debug 2> $(SDIR)/logs/$$(date +%Y-%m-%d-%H:%M:%S)-error.log
	echo "Log File: " $(SDIR)/logs/$$(date +%Y-%m-%d-%H:%M:%S)-error.log

# Delete Log Files (BEWARE OF YOUR ACTION)
.PHONY: cleanlog
cleanlog:
	rm -rf $(SDIR)/logs/*.log

# Delete Entire Log Directory (BEWARE OF YOUR ACTION)
.PHONY: cleanlogdir
cleanlogdir:
	rm -rf $(SDIR)/logs

# ZIP Directory
.PHONY: zip
zip:
	zip -r kungc_program4.zip ./
