//============================================================================
// Name        : cpp_practice.cpp
// Author      : Maxim Semenyuk
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <memory>
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>

constexpr int WIDTH = 800, HEIGHT = 600, STEP = 50;
constexpr double PI = acos(-1.);

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

	double cx, cy, x, y;

	cx = WIDTH / 2;
	cy = HEIGHT / 2;

	for (;;) {

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) return 0;
		}

		SDL_SetRenderDrawColor(renRef, 0, 48, 64, 255);
		SDL_RenderClear(ren.get());

		SDL_SetRenderDrawColor(renRef, 255, 255, 255, 255);

		// Оси координат
		SDL_RenderDrawLine(renRef, 0, cy, WIDTH, cy);
		SDL_RenderDrawLine(renRef, cx, 0, cx, HEIGHT);
		for (x = 0; x <= WIDTH; x += STEP) {
			SDL_RenderDrawLine(renRef, x, cy, x, cy - 5);
		}

		for (y = 0; y <= HEIGHT; y += STEP) {
			SDL_RenderDrawLine(renRef, cx, y, cx + 5, y);
		}

		// y = sin(x)
		for (x = 0; x <= WIDTH; x += 0.5) {
			double phi = (x - cx) / (double)STEP * PI;
			if (phi == 0) {
				y = 1;
			} else {
				y = sin(phi)/phi;
			}
			SDL_RenderDrawPoint(renRef, x, cy - (y * 200));
		}


		SDL_RenderPresent(renRef);
	}

	return 0;
}
