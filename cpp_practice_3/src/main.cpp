//============================================================================
// Name        : cpp_practice_3.cpp
// Author      : Maxim Semenyuk
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>

constexpr int WIDTH = 800, HEIGHT = 600, RADIUS = 250;

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	auto win = std::shared_ptr<SDL_Window>(
			SDL_CreateWindow(
						"Окно нашего графического приложения",
						SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
						WIDTH, HEIGHT,
						SDL_WINDOW_SHOWN),
			SDL_DestroyWindow);
	if (win == nullptr) {
		std::cerr << "При создании окна произошла ошибка: " << SDL_GetError() << std::endl;
		return 1;
	}

	auto ren = std::shared_ptr<SDL_Renderer>(
			SDL_CreateRenderer(win.get(), -1,
					SDL_RENDERER_ACCELERATED |
					SDL_RENDERER_PRESENTVSYNC),
			SDL_DestroyRenderer);

	if (ren == nullptr) {
		std::cerr << "При создании renderer-а произошла ошибка: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Renderer* renRef = ren.get();
	SDL_Event event;

	for (;;) {

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) return 0;
		}

		SDL_SetRenderDrawColor(renRef, 0, 48, 64, 255);
		SDL_RenderClear(ren.get());

		SDL_SetRenderDrawColor(renRef, 255, 255, 255, 255);

        int x = 0,
			y = RADIUS,
			cx = WIDTH / 2,
			cy = HEIGHT / 2,
			gap = 0,
			delta = (2 - 2 * RADIUS);

          while (y >= 0)
          {
        	  SDL_RenderDrawPoint(renRef, cx + x, cy + y);
        	  SDL_RenderDrawPoint(renRef, cx + x, cy - y);
        	  SDL_RenderDrawPoint(renRef, cx - x, cy - y);
        	  SDL_RenderDrawPoint(renRef, cx - x, cy + y);
              gap = 2 * (delta + y) - 1;
              if (delta < 0 && gap <= 0)
              {
                  x++;
                  delta += 2 * x + 1;
                  continue;
              }
              if (delta > 0 && gap > 0)
              {
                  y--;
                  delta -= 2 * y + 1;
                  continue;
              }
              x++;
              delta += 2 * (x - y);
              y--;
          }


		SDL_RenderPresent(renRef);
	}

	return 0;
}
