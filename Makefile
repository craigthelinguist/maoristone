CC=g++

STD=-std=c++11

# Warning flags.
WARNINGS=
LINKING= -lSDL2 -lws2_32 -lSDL2_image -lSDL2_ttf

# Additional compilation flags.
FLAGS=

# Figure out operating system we should be building for.
ifeq ($(OS), Windows_NT)
	FLAGS += -D _WINDOWS
	FLAGS += -D LIB=lib/windows
    FLAGS += -w -Wl,-subsystem,windows
    FLAGS += -IC:/MinGW/include/SDL2
    FLAGS += -LC:/MinGW/lib
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		FLAGS += -D _LINUX
		FLAGS += -D LIB=lib/linux
	else ifeq ($(UNAME_S),CYGWIN_NT)
		FLAGS += -D _WINDOWS
		FLAGS += -D LIB=lib/windows
	else
		$(error Makefile does not support your OS)
	endif
endif

SRC=Main.cpp MainGame.cpp Socket.cpp Address.cpp Text.cpp

# Comilation rules.
maoristone:
	$(CC) $(STD) $(SRC) $(WARNINGS) $(FLAGS) $(LINKING) $^ -o $@
