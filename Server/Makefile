CC=g++

STD=-std=c++11

# Warning flags.
# NOTE: -Werror has been removed from the WARNINGS - "all warnings being treated as errors"
WARNINGS=-pedantic -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wall -Wundef -Wcast-align -Wpointer-arith -Winit-self

LINKING= -lws2_32

# Additional compilation flags.
FLAGS=

# Figure out operating system we should be building for.
ifeq ($(OS), Windows_NT)
	FLAGS += -D _WINDOWS
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		FLAGS += -D _LINUX
	else ifeq ($(UNAME_S),CYGWIN_NT)
		FLAGS += -D _WINDOWS
	else
		$(error Makefile does not support your OS)
	endif
endif

SRC:=Main.cpp Socket.cpp Address.cpp GameManager.cpp

# Comilation rules.
server:
	$(CC) $(STD) $(SRC) $(WARNINGS) $(FLAGS) $(LINKING) $^ -o $@
