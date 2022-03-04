#pragma once

class Cronometer
{
public:
	Cronometer() = default;
	~Cronometer() = default;

	void start();
	void stop();
	void resume();

	unsigned int getSeconds() const;
	unsigned int getMilliseconds() const;

	bool isRunning() const;
private:
	unsigned int m_startTime { 0 };
	unsigned int m_stopTime { 0 };

	bool m_isRunning { false };
};
