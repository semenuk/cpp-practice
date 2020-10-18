//============================================================================
// Name        : cpp_practice_2.cpp
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

constexpr int WIDTH = 800, HEIGHT = 600;


SDL_Renderer* createWindow() {

	auto win = std::shared_ptr<SDL_Window>(
			SDL_CreateWindow(
						"Окно нашего графического приложения",
						SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
						WIDTH, HEIGHT,
						SDL_WINDOW_SHOWN),
			SDL_DestroyWindow);
	if (win == nullptr) {
		std::cerr << "При создании окна произошла ошибка: " << SDL_GetError() << std::endl;
	}

	auto ren = std::shared_ptr<SDL_Renderer>(
			SDL_CreateRenderer(win.get(), -1,
					SDL_RENDERER_ACCELERATED |
					SDL_RENDERER_PRESENTVSYNC),
			SDL_DestroyRenderer);

	if (ren == nullptr) {
		std::cerr << "При создании renderer-а произошла ошибка: " << SDL_GetError() << std::endl;
	}

	return ren.get();
}

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
	}

	auto ren = std::shared_ptr<SDL_Renderer>(
			SDL_CreateRenderer(win.get(), -1,
					SDL_RENDERER_ACCELERATED |
					SDL_RENDERER_PRESENTVSYNC),
			SDL_DestroyRenderer);

	if (ren == nullptr) {
		std::cerr << "При создании renderer-а произошла ошибка: " << SDL_GetError() << std::endl;
	}

	SDL_Renderer* renRef = ren.get();

	SDL_Event event;

	SDL_Rect wall;
	wall.x = 100;
	wall.y = 200;
	wall.w = 600;
	wall.h = 300;

	SDL_Rect window;
	window.x = 400;
	window.y = 275;
	window.w = 200;
	window.h = 150;

	SDL_Rect door;
	door.x = 200;
	door.y = 275;
	door.w = 100;
	door.h = 225;

	SDL_Rect doorhandle;
	doorhandle.x = door.x + door.w - 20;
	doorhandle.y = door.y + door.h / 2;
	doorhandle.w = 10;
	doorhandle.h = 5;

	for (;;) {

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) return 0;
		}

		SDL_SetRenderDrawColor(renRef, 0, 48, 64, 255);
		SDL_RenderClear(renRef);

		SDL_SetRenderDrawColor(renRef, 255, 255, 255, 255);

		// Стены
		SDL_RenderDrawRect(renRef, &wall);

		// Крыша
		SDL_RenderDrawLine(renRef, wall.x, wall.y, wall.x + wall.w / 2, 100);
		SDL_RenderDrawLine(renRef, wall.x + wall.w, wall.y, wall.x + wall.w / 2, 100);

		// Окно
		SDL_RenderDrawRect(renRef, &window);
		SDL_RenderDrawLine(renRef, window.x, window.y + window.h / 2, window.x + window.w, window.y + window.h / 2);
		SDL_RenderDrawLine(renRef, window.x + window.w / 2, window.y, window.x + window.w / 2, window.y + window.h);

		// Труба
		SDL_RenderDrawLine(renRef, wall.x + 120, wall.y - 40, wall.x + 120, 100);
		SDL_RenderDrawLine(renRef, wall.x + 120, 100, wall.x + 140, 100);
		SDL_RenderDrawLine(renRef, wall.x + 140, 100, wall.x + 140, wall.y - 46);

		// Дверь
		SDL_RenderDrawRect(renRef, &door);
		SDL_RenderDrawRect(renRef, &doorhandle);

		SDL_RenderPresent(renRef);

	}

	return 0;
}
