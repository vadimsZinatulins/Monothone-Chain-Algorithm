#pragma once

class Time
{
public:
	static inline unsigned int getTicks() { return m_ticks; }

	static inline float getDeltaTime() { return m_deltaTime; }
private:
	friend class Game;

	Time();
	~Time();

	static unsigned int m_ticks;
	static float m_deltaTime;
};
