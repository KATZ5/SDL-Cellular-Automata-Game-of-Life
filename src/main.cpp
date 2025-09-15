#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <iostream>

constexpr int window_w = 700, window_h = 700;
bool kill = false;
constexpr float cellSize = 10.0;
int cell_color = 2;
bool erase = false;
constexpr int arraySizew = window_w / cellSize;
constexpr int arraySizeh = window_h / cellSize;

int gridArray[arraySizew][arraySizeh];
int newGridArray[arraySizew][arraySizeh];

void drawCells(SDL_Renderer *renderer) {
  for (float i = 0; i < window_w; i += cellSize) {
    for (float j = 0; j < window_h; j += cellSize) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
      SDL_FRect cell = {i, j, cellSize, cellSize};
      SDL_RenderRect(renderer, &cell);
    }
  }
}

void fillGrid(int gridArray[arraySizew][arraySizeh]) {
  for (int i = 0; i < arraySizew; i++) {
    for (int j = 0; j < arraySizeh; j++) {
      gridArray[i][j] = 0;
      newGridArray[i][j] = 0;
    }
  }
}

void printGridArray(int gridArray[arraySizew][arraySizeh]) {
  for (int i = 0; i < arraySizew; i++) {
    for (int j = 0; j < arraySizeh; j++) {
      std::cout << gridArray[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void updateGridArray(int gridArray[arraySizew][arraySizeh]) {
  float mouseX, mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);
  int i_mouseX = mouseX / cellSize, i_mouseY = mouseY / cellSize;
  // std::cout << "Filling cell: " << i_mouseX << " " << i_mouseY << std::endl;
  if (!erase) {
    gridArray[i_mouseY][i_mouseX] = 1;

  } else {
    gridArray[i_mouseY][i_mouseX] = 0;
  }
}

void sandRules(int gridArray[arraySizew][arraySizeh]) {
  for (int i = 0; i < arraySizew; i++) {
    for (int j = 0; j < arraySizeh; j++) {
      int neigbhourCount = (gridArray[i][j + 1] + gridArray[i][j - 1] +
                            gridArray[i + 1][j] + gridArray[i - 1][j] +
                            gridArray[i + 1][j + 1] + gridArray[i + 1][j - 1] +
                            gridArray[i - 1][j - 1] + gridArray[i - 1][j + 1]);
      if (gridArray[i][j] == 1) {
        if (neigbhourCount < 2) {
          newGridArray[i][j] = 0;
        } else if (neigbhourCount == 2 || neigbhourCount == 3) {
          newGridArray[i][j] = 1;
        } else if (neigbhourCount > 3) {
          newGridArray[i][j] = 0;
        }
      } else if (gridArray[i][j] == 0) {
        if (neigbhourCount == 3) {
          newGridArray[i][j] = 1;
        }
      }
    }
  }

  for (int i = 0; i < arraySizew; i++) {
    for (int j = 0; j < arraySizeh; j++) {
      gridArray[i][j] = newGridArray[i][j];
    }
  }
}

void fillCell(SDL_Renderer *renderer, int gridArray[arraySizew][arraySizeh]) {
  for (int i = 0; i < arraySizew; i++) {
    for (int j = 0; j < arraySizeh; j++) {
      if (gridArray[i][j] == 1) {
        if (cell_color == 1) {
          SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0);

        } else if (cell_color == 2) {
          SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        }
        SDL_FRect cell = {j * cellSize, i * cellSize, cellSize, cellSize};
        SDL_RenderFillRect(renderer, &cell);
      }
    }
  }
}

void highlightCell(SDL_Renderer *renderer) {
  float mouseX, mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);
  int i_mouseX = mouseX / cellSize, i_mouseY = mouseY / cellSize;

  // std::cout << i_mouseX << " " << i_mouseY << std::endl;
  SDL_SetRenderDrawColor(renderer, 250, 50, 100, 0);
  SDL_FRect cell = {i_mouseX * cellSize, i_mouseY * cellSize, cellSize,
                    cellSize};
  SDL_RenderFillRect(renderer, &cell);
}

int main() {

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::cerr << "SDL Failed to initialize the video submodule"
              << SDL_GetError() << std::endl;
    return 1;
  }

  std::cout << "Video driver: " << SDL_GetCurrentVideoDriver() << std::endl;

  SDL_Window *window =
      SDL_CreateWindow("FallingSand", window_w, window_h, SDL_WINDOW_RESIZABLE);
  if (window == NULL) {
    std::cerr << "Failed to create SDL window" << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
  if (renderer == nullptr) {
    std::cerr << "Failed to create Renderer: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  Uint32 lastUpdate = SDL_GetTicks();
  Uint32 startTime = SDL_GetTicks();
  int frameCount = 0;
  float fps = 0.0f;
  const Uint32 tickInterval = 30;

  fillGrid(gridArray);
  bool play = false;
  bool draw = false;
  while (!kill) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {

      case SDL_EVENT_QUIT:
        kill = true;

      case SDL_EVENT_MOUSE_BUTTON_DOWN:

        updateGridArray(gridArray);
        //       printGridArray(gridArray);
        play = false;

      case SDL_EVENT_KEY_DOWN:
        if (event.key.key == SDLK_SPACE) {
          play = true;

          std::cout << "Keyboard presses" << std::endl;
        } else if (event.key.key == SDLK_UP) {
          draw = !draw;
        } else if (event.key.key == SDLK_LEFT) {
          cell_color = 1;
        } else if (event.key.key == SDLK_RIGHT) {
          cell_color = 2;
        } else if (event.key.key == SDLK_E) {
          erase = !erase;
        } else if (event.key.key == SDLK_C) {
          fillGrid(gridArray);
        }
      }
    }
    Uint32 currentUpdate = SDL_GetTicks();
    if (currentUpdate - lastUpdate > tickInterval) {
      if (play == true) {

        sandRules(gridArray);
      }
      lastUpdate = currentUpdate;
    }
    if (draw == true) {
      updateGridArray(gridArray);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    //   drawCells(renderer);
    highlightCell(renderer);
    fillCell(renderer, gridArray);
    SDL_RenderPresent(renderer);

    frameCount++;
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - startTime >= 1000) {
      fps = frameCount * 1000.0 / (currentTime - startTime);
      std::cout << "FPS: " << fps << std::endl;

      startTime = currentTime;
      frameCount = 0;
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
