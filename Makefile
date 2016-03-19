CC=g++
FLAGS=-std=c++11 -pedantic -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wall -Wundef -Werror -Wcast-align -Wpointer-arith -Winit-self

maoristone: main.cpp
	$(CC) $(FLAGS) $^ -o $@
