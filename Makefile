CC=g++

# Warning flags.
WARNINGS=-std=c++11 -pedantic -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wall -Wundef -Werror -Wcast-align -Wpointer-arith -Winit-self

# Additional compilation flags.
FLAGS= 

# Figure out operating system we should be building for.
ifeq ($(OS), Windows_NT)
	FLAGS += -D _WINDOWS
	FLAGS += -D LIB=lib/windows
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		FLAGS += -D _LINUX
		FLAGS += -D LIB=lib/linux
	else
		$(error Makefile does not support your OS)
	endif
endif

# Comilation rules.
maoristone: main.cpp
	$(CC) $(FLAGS) $(WARNINGS) $^ -o $@
