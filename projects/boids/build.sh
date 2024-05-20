# g++ src/*.cpp -std=c++17 -I/usr/include/SDL2/ -I. -Iinclude/ -lSDL2main -lSDL2 -lSDL2_ttf -o bin/dronesim
# g++ src/*.cpp -lSDL2 -o bin/boids

# emcc -O2 -c src/main.cpp -o obj/main.o
# emcc -O2 -c src/AnimatedSprite.cpp -o obj/AnimatedSprite.o
# emcc -O2 -c src/ResourceManager.cpp -o obj/ResourceManager.o
# emcc -O2 -c src/TexturedRectangle.cpp -o obj/TexturedRectangle.o
# emcc -O2 -c src/UI.cpp -o obj/UI.o
# emcc -O2 -c src/cargo_drone.cpp -o obj/cargo_drone.o
# emcc -O2 -c src/cargo_drone_dynamics.cpp -o obj/cargo_drone_dynamics.o
# emcc -O2 -c src/controller.cpp -o obj/controller.o
# emcc -O2 -c src/drone.cpp -o obj/drone.o
# emcc -O2 -c src/drone_dynamics.cpp -o obj/drone_dynamics.o

# program
# g++ obj/*.o -I/usr/include/SDL2/ -I. -Iinclude/ -lSDL2main -lSDL2 -g -o bin/game
# emcc obj/*.o -s WASM=1 -s USE_SDL=2 -O2 -o renderingC.js
# emcc obj/*.o -s WASM=1 -s USE_SDL=2 -s SDL2_IMAGE_FORMATS='["bmp"]' -s USE_SDL_TTF=2 --preload-file resources -O2 -o dronesim.js
emcc src/*.cpp -s WASM=1 -s USE_SDL=2 -s SDL2_IMAGE_FORMATS='["bmp"]' -s USE_SDL_TTF=2 --preload-file resources -O2 -o boids.js
