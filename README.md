# Personal website

## Start local server
```
python3 -m http.server 8080
```

## Visit locally hosted site
localhost:8080

## Emscripten (web assembly compiler)
Source environment with
```
source ~/Software/emsdk/emsdk_env.sh
```
Easiest to make header only file system - compiling multifile (.cpp) projects should be investigated. Very likely to be possible.\
\
Necessary imports:
```c++
#include <emscripten.h>
#include <cstdlib> // actually not sure about this one
```
Game loop must be called in a specific way:
```c++
class SimLoop{ // example class to be instantiated in main()
public:
    void run() { // example run method to call from main()
        emscripten_set_main_loop_arg(mainloop, &ctx, -1, 1);
    }
private:
    static void mainloop(void *arg) {
        context *ctx = static_cast<context *>(arg);
        ...
    }
};
```
The context is a struct wrapping the variables used in the loop.
```c
struct context {
    ...
};
```
Example compile commands:
```sh
emcc src/main.cpp -s WASM=1 -s USE_SDL=2 -O3 -o robotarm.js
emcc src/main.cpp -s WASM=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_TTF=2 --preload-file resources -o robotarm.js
```
Optimization compile flags (take longer to compile)
```
-O1 -O2 -O3
```
