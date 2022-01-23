# Name of the project
PROJ_NAME=2DGame

# Source directory
SOURCE_DIR=./src

# Object directory
OBJ_DIR=./objects

# .c files
CPP_SOURCE=$(wildcard $(SOURCE_DIR)/*.cpp $(SOURCE_DIR)/**/*.cpp)
 
# .h files
HPP_SOURCE=$(wildcard $(SOURCE_DIR)/*.hpp $(SOURCE_DIR)/**/*.hpp)

# Object files
OBJ=$(subst .cpp,.o,$(subst src,objects,$(CPP_SOURCE)))

# Compiler and linker
CC=g++
 
# Flags for compiler
CC_FLAGS=-c         \
         -W         \
         -Wall      \
         -ansi      \
         -pedantic  \
		 -std=c++17  \

LFLAGS = -lGLU -lGL -lglut -lm

# Command used at clean target
RM = rm -rf

#
# Compilation and linking
#
all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo 'Building binary using GCC linker: $@'
	$(CC) $^ -o $@ $(LFLAGS)
	@ echo 'Finished building binary: $@'
	@ echo ' '

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(SOURCE_DIR)/%.hpp
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@ $(LFLAGS)
	@ echo ' '

$(OBJ_DIR)/ext/%.o: $(SOURCE_DIR)/%.cpp $(SOURCE_DIR)/%.hpp
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@ $(LFLAGS)
	@ echo ' '

$(OBJ_DIR)/game/%.o: $(SOURCE_DIR)/%.cpp $(SOURCE_DIR)/%.hpp
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@ $(LFLAGS)
	@ echo ' '

$(OBJ_DIR)/graphics/%.o: $(SOURCE_DIR)/%.cpp $(SOURCE_DIR)/%.hpp
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@ $(LFLAGS)
	@ echo ' '

$(OBJ_DIR)/graphics/color/%.o: $(SOURCE_DIR)/%.cpp $(SOURCE_DIR)/%.hpp
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@ $(LFLAGS)
	@ echo ' '

$(OBJ_DIR)/graphics/elements/%.o: $(SOURCE_DIR)/%.cpp $(SOURCE_DIR)/%.hpp
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@ $(LFLAGS)
	@ echo ' '

$(OBJ_DIR)/graphics/shapes/%.o: $(SOURCE_DIR)/%.cpp $(SOURCE_DIR)/%.hpp
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@ $(LFLAGS)
	@ echo ' '

$(OBJ_DIR)/math/%.o: $(SOURCE_DIR)/%.cpp $(SOURCE_DIR)/%.hpp
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@ $(LFLAGS)
	@ echo ' '

$(OBJ_DIR)/physics/%.o: $(SOURCE_DIR)/%.cpp $(SOURCE_DIR)/%.hpp
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@ $(LFLAGS)
	@ echo ' '

$(OBJ_DIR)/main.o: $(SOURCE_DIR)/main.cpp $(HPP_SOURCE)
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@ $(LFLAGS)
	@ echo ' '

objFolder:
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)/ext $(OBJ_DIR)/game $(OBJ_DIR)/math $(OBJ_DIR)/graphics $(OBJ_DIR)/graphics/color $(OBJ_DIR)/graphics/shapes $(OBJ_DIR)/graphics/elements $(OBJ_DIR)/physics

clean:
	@ $(RM) $(OBJ_DIR) $(PROJ_NAME) *~
 
.PHONY: all clean