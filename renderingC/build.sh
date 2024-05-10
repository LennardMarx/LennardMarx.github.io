#!/bin/bash

# obj
emcc -O2 -c src/main.c -o obj/main.o
emcc -O2 -c src/interface.c -o obj/interface.o
emcc -O2 -c src/event_handler.c -o obj/event_handler.o
emcc -O2 -c src/cube.c -o obj/cube.o
emcc -O2 -c src/projection_plane.c -o obj/projection_plane.o
emcc -O2 -c src/projector.c -o obj/projector.o
emcc -O2 -c src/matrices.c -o obj/matrices.o
emcc -O2 -c src/player.c -o obj/player.o

# program
emcc obj/*.o -s WASM=1 -s USE_SDL=2 -O2 -o rendering.js
