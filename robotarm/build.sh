#!/bin/bash

# g++ main.cpp -lSDL2 -o robotarm
# emcc main.cpp -s WASM=1 -s USE_SDL=2 -O3 -o index.js
emcc main.cpp -s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_TTF=2 --preload-file resources -o robotarm.js
