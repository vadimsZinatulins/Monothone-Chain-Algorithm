#include "Cronometer.h"

#include <SDL2/SDL.h>

void Cronometer::start()
{
	if(!m_isRunning)
{
		m_isRunning = true;
		m_stopTime = 0;

		m_startTime = SDL_GetTicks();
	}
}

void Cronometer::stop()
{
	if(m_isRunning)
{
		m_stopTime = SDL_GetTicks();

		m_isRunning = false;
	}
}

void Cronometer::resume()
{
	if(!m_isRunning)
{
		m_startTime += SDL_GetTicks() - m_stopTime;
		m_stopTime = 0;

		m_isRunning = true;
	}
}

unsigned int Cronometer::getSeconds() const
{
	return ((m_isRunning ? SDL_GetTicks() : m_stopTime) - m_startTime) / 1000;
}

unsigned int Cronometer::getMilliseconds() const
{
	return (m_isRunning ? SDL_GetTicks() : m_stopTime) - m_startTime;
}

bool Cronometer::isRunning() const
{
	return m_isRunning;
}

