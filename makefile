
RM := rm -rf

OBJ_DIR := obj

BIN_DIR := bin

SRC_DIR := # src/

DIRS := $(OBJ_DIR) $(BIN_DIR)

EXECUTABLES := KnightMovesRefactored

# All Target
all: $(DIRS) $(EXECUTABLES)

# Add inputs and outputs from these tool invocations to the build variables 
OBJS += $(OBJ_DIR)/KMBoardLocation.o $(OBJ_DIR)/KMMove.o $(OBJ_DIR)/KMMoveFilters.o \
$(OBJ_DIR)/KMOutputData.o $(OBJ_DIR)/KMPath.o $(OBJ_DIR)/KnightMoves.o \
$(OBJ_DIR)/KnightMovesImplementation.o 

obj/%.o: $(SRC_DIR)%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -D__cplusplus=201103L -O3 -Wall -c -o "$@" "$<" # Production
#	g++ -std=c++0x -D__cplusplus=201103L -O0 -g3 -Wall -c -o "$@" "$<" # Debug
	@echo 'Finished building: $<'
	@echo ' '

obj/KMBoardLocation.o: $(SRC_DIR)KMBoardLocation.cpp $(SRC_DIR)KnightMoves.h \
 $(SRC_DIR)KMMethodLimitations.h $(SRC_DIR)KMBaseData.h \
 $(SRC_DIR)KMBoardLocation.h $(SRC_DIR)KMBoardDimensionConstants.h

obj/KMMove.o: $(SRC_DIR)KMMove.cpp $(SRC_DIR)KMMove.h $(SRC_DIR)KMBoardLocation.h \
 $(SRC_DIR)KMBoardDimensionConstants.h

obj/KMMoveFilters.o: $(SRC_DIR)KMMoveFilters.cpp \
 $(SRC_DIR)KMBoardDimensionConstants.h $(SRC_DIR)KMMoveFilters.h \
 $(SRC_DIR)KnightMoves.h $(SRC_DIR)KMMethodLimitations.h $(SRC_DIR)KMBaseData.h \
 $(SRC_DIR)KMMove.h $(SRC_DIR)KMBoardLocation.h

obj/KMOutputData.o: $(SRC_DIR)KMOutputData.cpp $(SRC_DIR)KMOutputData.h \
 $(SRC_DIR)KMPath.h $(SRC_DIR)KMBoardLocation.h $(SRC_DIR)KMMove.h \
 $(SRC_DIR)KnightMoves.h $(SRC_DIR)KMMethodLimitations.h $(SRC_DIR)KMBaseData.h

obj/KMPath.o: $(SRC_DIR)KMPath.cpp $(SRC_DIR)KMPath.h $(SRC_DIR)KMBoardLocation.h \
 $(SRC_DIR)KMMove.h $(SRC_DIR)KnightMoves.h $(SRC_DIR)KMMethodLimitations.h \
 $(SRC_DIR)KMBaseData.h $(SRC_DIR)KMBoardDimensionConstants.h

obj/KnightMoves.o: $(SRC_DIR)KnightMoves.cpp $(SRC_DIR)KnightMoves.h \
 $(SRC_DIR)KMMethodLimitations.h $(SRC_DIR)KMBaseData.h \
 $(SRC_DIR)KnightMovesImplementation.h $(SRC_DIR)KMPath.h \
 $(SRC_DIR)KMBoardLocation.h $(SRC_DIR)KMMove.h $(SRC_DIR)KMOutputData.h \
 $(SRC_DIR)KMMoveFilters.h $(SRC_DIR)KMBoardDimensionConstants.h

obj/KnightMovesImplementation.o: $(SRC_DIR)KnightMovesImplementation.cpp \
 $(SRC_DIR)KnightMoves.h $(SRC_DIR)KMMethodLimitations.h $(SRC_DIR)KMBaseData.h \
 $(SRC_DIR)KnightMovesImplementation.h $(SRC_DIR)KMPath.h \
 $(SRC_DIR)KMBoardLocation.h $(SRC_DIR)KMMove.h $(SRC_DIR)KMOutputData.h \
 $(SRC_DIR)KMMoveFilters.h $(SRC_DIR)KMBoardDimensionConstants.h

$(SRC_DIR)KnightMoves.h:

$(SRC_DIR)KMMethodLimitations.h:

$(SRC_DIR)KMBaseData.h:

$(SRC_DIR)KnightMovesImplementation.h:

$(SRC_DIR)KMPath.h:

$(SRC_DIR)KMBoardLocation.h:

$(SRC_DIR)KMMove.h:

$(SRC_DIR)KMOutputData.h:

$(SRC_DIR)KMMoveFilters.h:

$(SRC_DIR)KMBoardDimensionConstants.h:

# Add inputs and outputs from these tool invocations to the build variables 

# Tool invocations
KnightMovesRefactored: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o "$(BIN_DIR)/KnightMovesRefactored" $(OBJS)
	ln -s bin/KnightMovesRefactored .
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(DIRS) $(EXECUTABLES)
	-@echo ' '

MKDIR_P := mkdir -p

${OBJ_DIR}:
	${MKDIR_P} ${OBJ_DIR}

${BIN_DIR}:
	${MKDIR_P} ${BIN_DIR}

.PHONY: all clean $(DIRS)
.SECONDARY:

