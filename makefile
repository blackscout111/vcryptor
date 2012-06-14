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

# The directory containing the include files
INC_DIR = inc

# The directory containing the libraries made for this project
LIB_DIR = lib

# Include directories
INCLUDE_DIRS =	-I/usr/include \
				-I/usr/local/include \
				-I$(INC_DIR)

# Library directories
LIB_DIRS =	-L/usr/lib \
			-L/usr/local/lib \
			-L$(LIB_DIR)

# Other libraries to link to (Example -lm)
LINK_LIBS = 

# The compiler
COMPILER = gcc

# Compiler flags
CFLAGS = -Wall

# The source object files needed
# - These objects should correspond to .cpp or .c files in the source directory
# that need to be included in the project. Each of these files should have a
# corresponding header file in the include directory
SRC_FILES = vcryptor.c

# The name of the src file with the main function
MAIN_FILE = main.c

# These are the objects to be made corresponding to the needed source files
SRC_OBJS = $(patsubst %.c, %.o, $(SRC_FILES))
MAIN_OBJ = $(patsubst %.c, %.o, $(MAIN_FILE))

# The name of the executable
EXECNAME = vcryptor

# The executable
EXEC = $(EXECNAME)

# The libraries to make
LIB = $(LIB_DIR)/lib$(EXECNAME).a


#===============================================================================
# Target Rules
#===============================================================================

# Build the executable
$(EXEC) : $(LIB) $(MAIN_OBJ)
	@echo Building $@
	@$(COMPILER) $(CFLAGS) \
	$(INCLUDE_DIRS) $(LIB_DIRS) \
	$(MAIN_OBJ) $(LINK_LIBS) -l$(EXECNAME) \
	-o $(EXEC)
	
# Build the library
$(LIB) : $(SRC_OBJS)
	@mkdir -p $(LIB_DIR)
	@echo Building $@
	@ar cr $(LIB) $(SRC_OBJS)

# Build the object file corresponding to the the src file with the main function
$(MAIN_OBJ) : %.o : $(SRC_DIR)/%.c
	@echo Building $@
	@$(COMPILER) $(CFLAGS) \
	$(INCLUDE_DIRS) $(LIB_DIRS) -c $< \
	$(LINK_LIBS)

# Build the object files corresponding to the source files
# (each should have a corresponding header file)
$(SRC_OBJS) : %.o : $(SRC_DIR)/%.c $(INC_DIR)/%.h
	@echo Building $@
	@$(COMPILER) $(CFLAGS) \
	$(INCLUDE_DIRS) $(LIB_DIRS) -c $< \
	$(LINK_LIBS)
	
# Remove all of the object files
clean :
	@echo Removing object files
	@rm -f *.o


