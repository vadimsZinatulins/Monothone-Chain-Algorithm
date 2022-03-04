#pragma once

#include "Game.h"
#include "Cronometer.h"

#include <vector>

struct Point
{
	int x { 0 };
	int y { 0 };
};

enum class Stage { LeftToRight, RightToLeft, Done };

class MonothoneChain final : public Game
{
public:
	MonothoneChain() = default;
	~MonothoneChain() = default;

	void initialize() override;
	void shutdown() override;
	void update() override;
	void render(SDL_Renderer *renderer) override;

private:
	void setup();
	void stageStep();

	std::vector<Point> m_points { };
	std::vector<Point> m_hullPoints { };

	std::size_t m_k { 0 };
	std::size_t m_i { 0 };
	std::size_t m_t { 0 };

	Stage m_stage { Stage::LeftToRight };

	Cronometer m_crono;
};
