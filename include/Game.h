#pragma once

struct SDL_Window;
struct SDL_Renderer;

class Game 
{
public:
	Game() = default;
	virtual ~Game() = default;

	 void run();

protected:
	virtual void initialize() = 0;
	virtual void shutdown() = 0;
	virtual void update() = 0;
	virtual void render(SDL_Renderer *renderer) = 0;
private:
	void init();
	void loop();
	void close();

	SDL_Window *m_window { nullptr };
	SDL_Renderer *m_renderer { nullptr };
};
