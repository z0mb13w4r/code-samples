#
# Define Include Paths
#---------------------------------------------------------------------
LIB_ROOT = .

# Define Source Directories.
#---------------------------------------------------------------------
DIR_SRC =
DIR_CXX = ../$(DIR_SRC)

# Name of c source files to be included in build.
#---------------------------------------------------------------------
SRCS_C = \
	example-032.c

# Name of cpp source files to be included in build.
#---------------------------------------------------------------------
SRCS_CPP =

# Name of target and map file to be built.
#---------------------------------------------------------------------
TARGETBASE = example

ifeq ($(CROSS),ARM32)
else ifeq ($(CROSS),ARM64)
else ifeq ($(CROSS),WIN32)
else ifeq ($(CROSS),WIN64)
else ifeq ($(CROSS),MIPS32)
else ifeq ($(CROSS),MIPS64)
else ifeq ($(CROSS),LINUX32)
else ifeq ($(CROSS),RISCV64)
else
	CROSS = LINUX64
endif

ifeq ($(DEBUG),y)
	DIR_OBJ = debug$(CROSS)/
	TARGET = $(TARGETBASE)d
else
	DIR_OBJ = release$(CROSS)/
	TARGET = $(TARGETBASE)
	DEBUG = n
endif

MAP_FILE = $(TARGET).map
STRIPPED_FILE = $(TARGET)-stripped

#=====================================================================================================================================
# Library Section of Makefile
#
# Section defining the library paths.
#=====================================================================================================================================

# Include Paths List
#---------------------------------------------------------------------
LIB_INCS = \
	-I.

ifeq ($(CROSS),WIN32)
SYS_OBJS =
else ifeq ($(CROSS),WIN64)
SYS_OBJS =
else
SYS_OBJS = \
	-lrt
endif

LIB_OBJS =

LIB_PATHS =

#=====================================================================================================================================
# Command Section of Makefile
#=====================================================================================================================================
# Set compile flags, dependant on DEBUG flag being set.
#---------------------------------------------------------------------

ifeq ($(DEBUG),y)
	CFLAGS = -g -O0 -Wall -c -MMD -MP -ggdb
else
	CFLAGS = -O0 -Wall -c -MMD -MP
	DFLAGS += -DNDEBUG
endif

# GNU toolchain definitions
#---------------------------------------------------------------------
ifeq ($(CROSS),ARM32)
	CROSS_COMPILE = arm-linux-gnueabihf-
	DFLAGS += -DENV_LINUX -DLINUX -DTARGET_ARM32
	EFLAGS  = -Wl,--no-enum-size-warning
	LFLAGS +=
else ifeq ($(CROSS),ARM64)
	CROSS_COMPILE = aarch64-linux-gnu-
	DFLAGS += -DENV_LINUX -DLINUX -DTARGET_ARM64
	EFLAGS  = -Wl,--no-enum-size-warning
	LFLAGS +=
else ifeq ($(CROSS),MIPS32)
	CROSS_COMPILE = mips-linux-gnu-
	DFLAGS += -DENV_LINUX -DLINUX -DTARGET_MIPS32
	EFLAGS  =
	LFLAGS +=
else ifeq ($(CROSS),MIPS64)
	CROSS_COMPILE = mips64-linux-gnuabi64-
	DFLAGS += -DENV_LINUX -DLINUX -DTARGET_MIPS64
	EFLAGS  =
	LFLAGS +=
else ifeq ($(CROSS),RISCV64)
	CROSS_COMPILE = riscv64-linux-gnu-
	DFLAGS += -DENV_LINUX -DLINUX -DTARGET_RISCV64
	EFLAGS  =
	LFLAGS +=
else ifeq ($(CROSS),WIN32)
	CROSS_COMPILE = i686-w64-mingw32-
	DFLAGS += -DWIN32
	EFLAGS  =
	LFLAGS += -static-libgcc -static-libstdc++
else ifeq ($(CROSS),WIN64)
	CROSS_COMPILE = x86_64-w64-mingw32-
	DFLAGS += -DWIN64
	EFLAGS  =
	LFLAGS += -static-libgcc -static-libstdc++
else ifeq ($(CROSS),LINUX32)
	CROSS_COMPILE =
	CFLAGS += -m32
	DFLAGS += -DENV_LINUX -DLINUX
	EFLAGS  = -m32
	LFLAGS +=
else
	CROSS_COMPILE =
	CFLAGS +=
	DFLAGS += -DENV_LINUX -DLINUX
	EFLAGS  =
	LFLAGS +=
endif

AS		= $(CROSS_COMPILE)as
LD		= $(CROSS_COMPILE)ld
CPP		= $(CROSS_COMPILE)g++
CC		= $(CROSS_COMPILE)gcc
AR		= $(CROSS_COMPILE)ar
GDB		= $(CROSS_COMPILE)gdb
STRIP		= $(CROSS_COMPILE)strip
CP		= cp
SCP		= scp
SSH		= ssh
GPROF		= gprof -b
RM		= rm -rf

# Build list of object files and dependants from c and cpp lists.
#---------------------------------------------------------------------
OBJS_CPP = $(addprefix $(DIR_OBJ), $(SRCS_CPP:.cpp=.o))
OBJS_C = $(addprefix $(DIR_OBJ), $(SRCS_C:.c=.o))
OBJS   = $(sort $(OBJS_CPP) $(OBJS_C))
DEPS   = $(OBJS:.o=.d)

#
#=====================================================================================================================================
# BUILD Command Section of Makefile
#=====================================================================================================================================
#
# compile c files.
#---------------------------------------------------------------------
%.o: $(DIR_CXX)%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	$(CC) $(DFLAGS) $(LIB_INCS) $(CFLAGS) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

# compile cpp files.
#---------------------------------------------------------------------
%.o: $(DIR_CXX)%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	$(CPP) $(DFLAGS) $(LIB_INCS) $(CFLAGS) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

# All Target
#---------------------------------------------------------------------
all: rm_exe dir_creation build_dependants $(TARGET)

# Help - list of commands in makefile.
#---------------------------------------------------------------------
help:
	@echo '-----------------------------------------------------------------------------------'
	@echo '----------- ################# Makefile configuration ################# ------------'
	@echo '-----------------------------------------------------------------------------------'
	@echo ' checkall Function to call check external make files.'
	@echo '-----------------------------------------------------------------------------------'
	@echo ' clean    clean all - called from eclipse.'
	@echo ' build    build rule external module attributes.'
	@echo '-----------------------------------------------------------------------------------'
	@echo ' NOTE'
	@echo ' ****'
	@echo ' '
	@echo ' set DEBUG=y to build debug information.'
	@echo ' '
	@echo ' set CROSS=ARM32 to build ARM 32-bit version.'
	@echo ' set CROSS=ARM64 to build ARM 64-bit version.'
	@echo ' set CROSS=WIN32 to build Windows 32-bit version.'
	@echo ' set CROSS=WIN64 to build Windows 64-bit version.'
	@echo ' set CROSS=MIPS32 to build MIPS 32-bit version.'
	@echo ' set CROSS=MIPS64 to build MIPS 64-bit version.'
	@echo ' set CROSS=LINUX32 to build 32-bit version.'
	@echo ' set CROSS=LINUX64 to build native version.'
	@echo ' '
	@echo ' e.g. make DEBUG=y CROSS=ARM32'
	@echo '-----------------------------------------------------------------------------------'
	@echo ' '

# Check makefile configuration.
#---------------------------------------------------------------------
check:
	@echo '-----------------------------------------------------------------------------------'
	@echo '----------- ################# Makefile configuration ################# ------------'
	@echo '-----------------------------------------------------------------------------------'
	@echo 'TARGET    = $(TARGET)'
	@echo '-----------------------------------------------------------------------------------'
	@echo 'DIR SRC   = $(DIR_SRC)'
	@echo 'DIR OBJ   = $(DIR_OBJ)'
	@echo 'DIR CXX   = $(DIR_CXX)'
	@echo '-----------------------------------------------------------------------------------'
	@echo 'SRC C     = $(SRCS_C)'
	@echo 'SRC CPP   = $(SRCS_CPP)'
	@echo '-----------------------------------------------------------------------------------'
	@echo 'OBJ C     = $(OBJS_C)'
	@echo 'OBJ CPP   = $(OBJS_CPP)'
	@echo '-----------------------------------------------------------------------------------'
	@echo 'ALL OBJ   = $(OBJS)'
	@echo '-----------------------------------------------------------------------------------'
	@echo 'DEPS      = $(DEPS)'
	@echo '-----------------------------------------------------------------------------------'
	@echo 'G++       = $(CPP)'
	@echo 'GCC       = $(CC)'
	@echo 'CFLAGS    = $(CFLAGS)'
	@echo 'DFLAGS    = $(DFLAGS)'
	@echo 'LFLAGS    = $(LFLAGS)'
	@echo '-----------------------------------------------------------------------------------'
	@echo 'LIB_INCS  = $(LIB_INCS)'
	@echo 'LIB_OBJS  = $(LIB_OBJS)'
	@echo 'LIB_PATHS = $(LIB_PATHS)'
	@echo ' '

# Remove any previously build executable - to force build.
#---------------------------------------------------------------------
rm_exe:
	@echo 'Removing executable.'
	-$(RM) $(TARGET) $(MAP_FILE)
	@echo 'Removed.'
	@echo ' '

# build rule external module attributes
#---------------------------------------------------------------------
build: $(OBJS_CPP) $(OBJS_C)

# Create directory - Build_Debug
#---------------------------------------------------------------------
dir_creation:
	@echo -n 'Directory' $$PWD"/"$(DIR_OBJ)
	@if test -d $(DIR_OBJ); then echo " exists"; else mkdir -p $(DIR_OBJ); echo " created";  fi
	@echo ' '

# Build target
#---------------------------------------------------------------------
$(TARGET): build
	@echo 'Building target: $@'
	@echo 'Invoking: GCC Linker'
	-$(CPP) -o $(TARGET) $(OBJS) $(LFLAGS) $(LIB_PATHS) -Wl,--start-group $(LIB_OBJS) $(SYS_OBJS) -Wl,--end-group $(EFLAGS) -Wl,-Map=$(MAP_FILE)
	@echo 'Finished building target: $@'
ifeq ($(DEBUG),y)
ifeq ($(CROSS),WIN32)
	-$(STRIP) -o $(STRIPPED_FILE) -s $(TARGET).exe
else ifeq ($(CROSS),WIN64)
	-$(STRIP) -o $(STRIPPED_FILE) -s $(TARGET).exe
else
	-$(STRIP) -o $(STRIPPED_FILE) -s $(TARGET)
endif
	@echo 'Finished stripping target: $@'
endif

# Clean external module attributes
#---------------------------------------------------------------------
cleanall: clean clean_dependents

# Clean all - called from eclipse
#---------------------------------------------------------------------
clean:
	@echo 'Removing Object Files'
	-$(RM) $(OBJS) $(TARGET) $(MAP_FILE) $(STRIPPED_FILE)
	@echo 'Removing Temporary Directories'
	-$(RM) $(DIR_OBJ)
	-@echo ' '

# Clean all dependents
#---------------------------------------------------------------------
checkall:

clean_dependents:

build_dependants:

# Phony command definitions
#---------------------------------------------------------------------
#Phony
.PHONY: dir_creation clean build check checkall rm_exe help

.SECONDARY:

