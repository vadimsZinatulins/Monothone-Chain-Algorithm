#include "Game.h"
#include "Time.h"
#include "KeyManager.h"
#include "config.h"

#include <SDL2/SDL.h>

void Game::run()
{
	init();
	loop();
	close();
}

void Game::init()
{
	SDL_Init(SDL_INIT_VIDEO);

	m_window = SDL_CreateWindow(SCREEN_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(m_renderer, 0x00f, 0x00f, 0x00f, 0xff);

	initialize();
}

void Game::loop()
{
	auto &keys = KeyManager::getInstance();
	bool isRunning = true;
	SDL_Event e;

	Uint32 startFrame = SDL_GetTicks();
	Uint32 startPreviousFrame = SDL_GetTicks();

	while(isRunning)
	{
		Time frameTimer;

		keys.update();

		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				keys.keyPressed(e.key.keysym.sym);
				break;
			case SDL_KEYUP:
				keys.keyReleased(e.key.keysym.sym);
				break;
			}
		}

		update();

		SDL_RenderClear(m_renderer);
		render(m_renderer);
		SDL_RenderPresent(m_renderer);

	}
}

void Game::close()
{
	shutdown();

	if(m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}

	if(m_window)
	{
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}

	SDL_Quit();
}

