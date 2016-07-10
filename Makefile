CC=g++

STD=-std=c++11

# Warning flags.
WARNINGS=-pedantic -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wall -Wundef -Werror -Wcast-align -Wpointer-arith -Winit-self

LINKING= -lSDL2

# Additional compilation flags.
FLAGS=

# Figure out operating system we should be building for.
ifeq ($(OS), Windows_NT)
	FLAGS += -D _WINDOWS
	FLAGS += -D LIB=lib/windows
    FLAGS += -w -Wl,-subsystem,windows
	LINKING += -lmingw32 
    FLAGS += -IC:/mingw_dev_lib/include/SDL2
    FLAGS += -LC:/mingw_dev_lib/lib
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

SRC=Main.cpp MainGame.cpp

# Comilation rules.
maoristone: 
	$(CC) $(STD) $(SRC) $(WARNINGS) $(FLAGS) $(LINKING) $^ -o $@
