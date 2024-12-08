#!/bin/bash

# g++ src/*.cpp -std=c++17 -I/usr/include/SDL2/ -I. -Iinclude/ -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -o bin/raycasting

#g++ -g -std=c++17 ./src/*.cpp -I./include -o ./bin/raycasting -lSDL2 -ldl



# obj
# gcc -c src/main.cpp -o obj/main.o
# gcc -c src/UI.cpp -o obj/UI.o
# gcc -c src/entity.cpp -o obj/entity.o
# gcc -c src/eventChecks.cpp -o obj/eventChecks.o
# gcc -c src/raycaster.cpp -o obj/raycaster.o
# gcc -c src/rectangle.cpp -o obj/rectangle.o
# gcc -c src/wall.cpp -o obj/wall.o
# gcc -c src/world_utils.cpp -o obj/world_utils.o

# program
# g++ obj/*.o -I/usr/include/SDL2/ -I. -Iinclude/ -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -o bin/raycasting # works
# g++ obj/*.o -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -o bin/raycasting # works
# g++ obj/*.o -lSDL2 -lSDL2_ttf -lSDL2_image -o bin/raycasting # works

#obj
emcc -O2 -c src/main.cpp -o obj/main.o
emcc -O2 -c src/UI.cpp -o obj/UI.o
emcc -O2 -c src/entity.cpp -o obj/entity.o
emcc -O2 -c src/eventChecks.cpp -o obj/eventChecks.o
emcc -O2 -c src/raycaster.cpp -o obj/raycaster.o
emcc -O2 -c src/rectangle.cpp -o obj/rectangle.o
emcc -O2 -c src/wall.cpp -o obj/wall.o
emcc -O2 -c src/world_utils.cpp -o obj/world_utils.o

# program
# g++ obj/*.o -I/usr/include/SDL2/ -I. -Iinclude/ -lSDL2main -lSDL2 -g -o bin/game
# emcc obj/*.o -s WASM=1 -s USE_SDL=2 -O2 -o renderingC.js
# emcc obj/*.o -s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_TTF=2 --preload-file resources --preload-file textures -O2 -o raycasting.js
emcc obj/*.o -s WASM=1 -s USE_SDL=2 -s INITIAL_MEMORY=128MB -s MAXIMUM_MEMORY=512MB -s ALLOW_MEMORY_GROWTH=1 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_TTF=2 --preload-file resources --preload-file textures -O2 -o raycasting.js
# emcc main.cpp -s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_TTF=2 --preload-file res -o index.js
