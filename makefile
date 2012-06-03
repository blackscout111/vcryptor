################################################################################
# Makefile for imgstats
################################################################################

#-------------------------------------------------------------------------------
# NOTE: Make sure that you have the following environment variables set in order
# to compile and run this project
#
# LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/usr/lib:/usr/local/lib"
# LIBRARY_PATH="$LIBRARY_PATH:/usr/lib:/usr/local/lib"
#
#-------------------------------------------------------------------------------

#===============================================================================
# Standard macros
#===============================================================================

# The directory containing the source files
SRC_DIR = src

# The directory containing the object files
OBJ_DIR = obj

# The directory containin the include files
INC_DIR = inc

# Include directories
INCLUDE_DIRS =	-I/usr/include \
				-I/usr/local/include \
				-I$(INC_DIR)

# Library directories
LIB_DIRS =	-L/usr/lib \
			-L/usr/local/lib

# Libraries to link to
#LINK_LIBS = 

# The compiler
COMPILER = gcc

# Compiler flags
CFLAGS = -Wall

# The source object files needed
# - These objects should correspond to .cpp or .c files in the source directory
# that need to be included in the project. Each of these files should have a
# corresponding header file in the include directory
SRC_FILES = vcryptor.c \
            vcryptor_main.c

# These are the objects to be made corresponding to the needed source files
SRC_OBJS = $(patsubst %.c, %.o, $(SRC_FILES))

# The name of the executable
EXECNAME = vcryptor

# The executable
EXEC = $(EXECNAME).exe

# The object files needed by the executable
OBJS =  $(SRC_OBJS)

#===============================================================================
# Build the executable from the object files
#===============================================================================

# Build the executable
$(EXEC) : $(OBJS)
	@echo Building the executable
	@$(COMPILER) $(CFLAGS) \
	$(OBJS) \
	$(INCLUDE_DIRS) $(LIB_DIRS) $(LINK_LIBS) \
	-o $(EXEC)

#===============================================================================
# Build all of the source object files (These should be in the source folder)
#===============================================================================

# Build the object files corresponding to the source files
# (each should have a corresponding header file)
$(SRC_OBJS) : %.o : $(SRC_DIR)/%.c $(INC_DIR)/%.h
	@echo Building $@
	@$(COMPILER) $(CFLAGS) \
	$(INCLUDE_DIRS) $(LIB_DIRS) -c $< \
	$(LINK_LIBS)
	

################################################################################
# Clean up the build dependencies
################################################################################
clean:
	@echo Removing the object files
	@rm -f *.o


