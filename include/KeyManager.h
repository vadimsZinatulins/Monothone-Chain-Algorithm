#pragma once

using Key = unsigned int;

class KeyManager
{
public:
	static KeyManager &getInstance();

	bool isKeyPressed(Key key) const;
	bool isKeyDown(Key key) const;
	bool isKeyReleased(Key key) const;
private:
	friend class Game;

	class KeyMap
	{
	public:
		static constexpr int CacheLineSize { 64 };
		static constexpr int ArraySize { (CacheLineSize - sizeof(unsigned char)) / sizeof(Key) / 2 };

		void operator=(const KeyMap &other);

		void insert(Key key);
		bool contains(Key key) const;
		void remove(Key key);

	private:
		Key m_keys[ArraySize];
		unsigned char m_size { 0 };
	};

	KeyManager() = default;
	~KeyManager() = default;

	void update();

	void keyPressed(Key key);
	void keyReleased(Key key);

	static KeyManager m_instance;

	KeyMap m_currFrameKeys;
	KeyMap m_oldFrameKeys;
};
