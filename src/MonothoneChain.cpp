#include "MonothoneChain.h"
#include "KeyManager.h"
#include "Random.h"
#include "SDL_keycode.h"
#include "SDL_render.h"
#include "config.h"

#include <SDL2/SDL.h>
#include <algorithm>

int cross(Point a, Point b, Point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

void MonothoneChain::initialize()
{
	setup();
}

void MonothoneChain::shutdown()
{

}

void MonothoneChain::update()
{
	if(KeyManager::getInstance().isKeyPressed(SDLK_SPACE)) setup();

	if(m_crono.getSeconds() > 2 || KeyManager::getInstance().isKeyPressed(SDLK_RETURN)) stageStep();
}

void MonothoneChain::render(SDL_Renderer *renderer)
{
	if(m_k > 1)
	{
		// Render hull lines
		SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);
		for(std::size_t i = 0; i < m_k - 1; i++)
			SDL_RenderDrawLine(
				renderer,
				m_hullPoints[i].x, m_hullPoints[i].y,			// Origin point
				m_hullPoints[i + 1].x, m_hullPoints[i + 1].y	// Target point
			);
	}

	if(m_k > 0 && m_stage != Stage::Done)
	{
		// Render hull point to test
		SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
		SDL_RenderDrawLine(
			renderer,
			m_hullPoints[m_k - 1].x, m_hullPoints[m_k - 1].y,	// Origin point
			m_points[m_i].x, m_points[m_i].y					// Target point
		);
	}
	
	// Render points
	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderDrawPoints(renderer, (SDL_Point*)m_points.data(), m_points.size());
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
}

void MonothoneChain::setup()
{
	Random random;

	m_k = m_i = m_t = 0;

	m_points.clear();
	m_hullPoints.clear();

	for(int i = 0, num = random.nextInt(20, 40); i < num; ++i)
	{
		int x = random.nextInt(100, SCREEN_WIDTH - 100);
		int y = random.nextInt(100, SCREEN_HEIGHT - 100);

		m_points.push_back({ x, y });
	}

	std::sort(m_points.begin(), m_points.end(), [](Point a, Point b){ return a.x < b.x; });
	m_hullPoints = std::vector<Point>(m_points.size() * 2);

	m_stage = Stage::LeftToRight;

	m_crono.stop();
	m_crono.start();
}

void MonothoneChain::stageStep()
{
	switch(m_stage)
	{
	case Stage::LeftToRight:
		if(m_k >= 2 && cross(m_hullPoints[m_k - 2], m_hullPoints[m_k - 1], m_points[m_i]) <= 0) m_k--;
		else m_hullPoints[m_k++] = m_points[m_i++];

		if(m_i >= m_points.size())
		{
			m_stage = Stage::RightToLeft;
			m_i = m_points.size() - 1;
			m_t = m_k + 1;
		}
		break;
	case Stage::RightToLeft:
		if(m_k >= m_t && cross(m_hullPoints[m_k - 2], m_hullPoints[m_k - 1], m_points[m_i - 1]) <= 0) m_k--;
		else m_hullPoints[m_k++] = m_points[(m_i--) - 1];

		if(m_i <= 0)
		{
			m_hullPoints.resize(m_k - 1);

			m_stage = Stage::Done;
		}
		break;
	case Stage::Done:
		break;
	}

	m_crono.stop();
	m_crono.start();
}
