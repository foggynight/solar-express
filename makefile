# Copyright (C) 2020 Robert Coffey
# Licensed under the GNU GPLv2

CC=g++
CFLAGS=-lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:%.cpp=%.o)
PROG=solar-express

all: $(OBJS)
	$(CC) $(OBJS) -o $(PROG) $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

.SILENT: import
import:
	[ ! -d "olcPixelGameEngine" ] &&\
		git clone https://github.com/OneLoneCoder/olcPixelGameEngine;\
	[ ! -f "src/olcPixelGameEngine.h" ] &&\
		cp olcPixelGameEngine/olcPixelGameEngine.h src;\
	[ ! -f "src/Extensions/olcPGEX_Graphics2D.h" ] &&\
		cp olcPixelGameEngine/Extensions/olcPGEX_Graphics2D.h src;\

.PHONY: clean
clean:
	rm -rf src/*.o

.PHONY: uninstall
uninstall:
	rm -rf olcPixelGameEngine src/olc*.h src/*.o $(PROG)
