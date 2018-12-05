
# credits makes credits, all will make all the things eventually.
# ALL src comes from /src/, all compiled programs go to /bin/
# run with 'run' on windows, or './run' on unix-like systems
# valid makes:
#	'make' : makes all
#	'make credits' : compiles just credits.cpp, can probably be removed eventually
#	'make os' : handy little thing, outputs the current OS for troubleshooting purposes
# goal is run "make" in root and it spits out an executable in bin,
# and works regardless of OS with conditionals checking $(OS)

# $< == first dependency, $^ == all dependencies, $@ == target

# declaring paths for source files
OUT = ./bandcamp
SRC = $(wildcard src/*.cpp wildcard AI/*.cpp)
DEP = $(wildcard src/include/*.h wildcard AI/include/*.h)
OBJ = $(patsubst src/%.cpp, obj/%.o, $(SRC))
#OBJ = $(src:.c=.o) saw this syntax somewhere, threw it in for reference purposes

# set appropriate flags for windows. will likely need more work for unix-like systems
# once I know more about team member dev environments. include paths are specified,
# but do not appear to cause problems if all includes are thrown into the base MinGW
# install. this is true even if the specified directories do not exist. with luck,
# it's the same in unix. 'twould mean our installs can be different and still coexist.
 
ifeq ($(OS), Windows_NT)
	DETECTED_OS = $(OS) -ggdb
	CC = g++ -std=c++11
	CFLAGS = -c -IC:/mingwdev/include/SDL2
	INCLUDE = -IC:/mingwdev/include/SDL2
	LFLAGS = -LC:/mingwdev/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o $(OUT)
	LFLAGScr = -LC:/mingwdev/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
else ifeq ($(shell uname -s), Darwin)
	DETECTED_OS := $(shell uname -s)
	CC = g++ -std=c++11
	CFLAGS = -c -I/Library/Frameworks/SDL2.framework/Headers  -I/Library/Frameworks/SDL2_image.framework/Headers -I/Library/Frameworks/SDL2_ttf.framework/Headers -I/Library/Frameworks/SDL2_mixer.framework/Headers -F/Library/Frameworks/
	INCLUDE = -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_image.framework/Headers -I/Library/Frameworks/SDL2_ttf.framework/Headers -I/Library/Frameworks/SDL2_mixer.framework/Headers -F/Library/Frameworks/
	LFLAGS = -framework SDL2 -framework SDL2_image -framework SDL2_ttf -framework SDL2_mixer -o $(OUT) 
	LFLAGScr = -framework SDL2 -framework SDL2_image -framework SDL2_ttf -framework SDL2_mixer
else
	DETECTED_OS := $(shell uname -s)
	CC = g++ -std=c++11 -ggdb
	CFLAGS = -c -I/usr/include/SDL2
	INCLUDE = -I/usr/include/SDL2 -lSDL2_ttf -lSDL2_mixer
	LFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o $(OUT)
	LFLAGScr = -lSDL2 -lSDL2_image 
endif

.PHONY: all #credits

all: $(OUT) #credits

# target : dependencies
# 	recipe
$(OUT): $(OBJ)
	$(CC) $^ $(INCLUDE) $(LFLAGS) 

# compile source files to /obj/ (no linking)
# if a header changes, src will recompile
obj/%.o: src/%.cpp $(DEP)
	$(CC) $< $(CFLAGS) -o $@

# additional features for small tests
credits: src/credits.cpp
	$(CC) $< $(INCLUDE) $(LFLAGScr) -o bin/credits

os:
	@echo $(DETECTED_OS)

clean:
	rm obj/*.o
	rm bandcamp
	rm bandcamp.exe