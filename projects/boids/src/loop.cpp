#include "../include/loop.h"
#include "../include/quadtree.h"
#include <cstdlib>
#include <emscripten.h>

Loop::Loop() {}
Loop::~Loop() {}

struct context {
  UI *ui = new UI(1600, 1600);
  std::unique_ptr<TexturedRectangle> birdTex =
      std::make_unique<TexturedRectangle>(ui->getRenderer(),
                                          "../resources/duck.bmp");
  std::unique_ptr<AnimatedSprite> birdAnimation =
      std::make_unique<AnimatedSprite>(
          ui->getRenderer(), "../resources/ducks_12_flap_outline.bmp");

  // The boids with random position an orientation.
  int boidCount = 600;
  std::vector<std::shared_ptr<Boid>> boids;

  int mouseX, mouseY;

  QuadTree *qt;
  const int FPS = 60;                // set FPS
  const int frameDelay = 1000 / FPS; // delay according to FPS
};

static void mainloop(void *arg) {
  // chdir(SDL_GetBasePath());
  context *ctx = static_cast<context *>(arg);
  // limit framerate (see end of while loop)
  Uint32 frameStart = SDL_GetTicks();

  // Mouse position on screen.
  SDL_GetMouseState(&ctx->mouseX, &ctx->mouseY);
  glm::vec2 mouse = glm::vec2(ctx->mouseX, ctx->mouseY);

  // User input.
  // eventChecks();

  // Clearing the screen.
  ctx->ui->clear();

  std::vector<std::shared_ptr<Boid>> found;
  for (int i = 0; i < ctx->boids.size(); i++) {
    ctx->qt->insert(ctx->boids[i]);
  }
  for (int i = 0; i < ctx->boids.size(); i++) {
    // Looking for close boids.
    found = ctx->qt->query(ctx->boids[i]);
    ctx->boids[i]->getBoidsInVision(found);

    // Applying all the forces calculated by the rules.
    ctx->boids[i]->acc += ctx->boids[i]->separate() * 2.55f;
    ctx->boids[i]->acc += ctx->boids[i]->align() * 1.5f;
    ctx->boids[i]->acc += ctx->boids[i]->fightForPosition() * 1.55f;

    ctx->boids[i]->acc += ctx->boids[i]->avoidMouse(mouse) * 2.0f;
    // boids[i]->acc += boids[i]->chaseMouse(mouse) * 1.5f;

    ctx->boids[i]->acc += ctx->boids[i]->avoidBorder(ctx->ui) * 2.0f;
    // boids[i]->wrapAround(ui);

    // Updating position and velocity.
    ctx->boids[i]->fly();

    // Rendering the boids on screen.
    // boids[i]->draw(ui); // abstract
    // boids[i]->drawTexture(ui, birdTex);    // image
    // TODO: add alpha for images (maybe not possible without SDL_image)
    ctx->boids[i]->drawAnimation(ctx->ui, ctx->birdAnimation); // animation
  }
  // if (pause) {
  // ctx.qt->draw(ctx.ui);
  // }

  // Show everything rendered.
  SDL_RenderPresent(ctx->ui->getRenderer());

  ctx->qt->clear();

  // limit framerate
  int frameTime = SDL_GetTicks() - frameStart;
  if (ctx->frameDelay > frameTime) {
    SDL_Delay(ctx->frameDelay - frameTime);
  }
}

void Loop::run() {
  // Change directory
  if (chdir(SDL_GetBasePath()) != 0) {
    perror("chdir failed");
  }
  srand(time(NULL));

  context ctx;

  for (int i = 0; i < ctx.boidCount; i++) {
    glm::vec2 pos =
        glm::vec2{rand() % (ctx.ui->sizeX + 1), rand() % (ctx.ui->sizeY + 1)};
    glm::vec2 vel =
        glm::normalize(glm::vec2{rand() - RAND_MAX / 2, rand() - RAND_MAX / 2});
    ctx.boids.push_back(std::make_shared<Boid>(pos, vel));
  }

  ctx.qt = new QuadTree(ctx.ui->sizeX / 2, ctx.ui->sizeY / 2, ctx.ui->sizeX,
                        ctx.ui->sizeY);

  emscripten_set_main_loop_arg(mainloop, &ctx, -1, 1);
  while (!quit) {
  }
}

// User input - key presses.
void Loop::eventChecks() {
  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_QUIT) {
      quit = true;
    }
    switch (event.type) {
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
        quit = true;
        break;
      case SDLK_q:
        quit = true;
        break;
      case SDLK_SPACE:
        pause = !pause;
        break;
      default:
        break;
      }
    }
  }
}
