#include "KeyManager.h"

KeyManager KeyManager::m_instance;

KeyManager &KeyManager::getInstance() { return m_instance; }

bool KeyManager::isKeyPressed(Key key) const { return m_currFrameKeys.contains(key) && !m_oldFrameKeys.contains(key); }
bool KeyManager::isKeyDown(Key key) const { return m_currFrameKeys.contains(key); }
bool KeyManager::isKeyReleased(Key key) const { return !m_currFrameKeys.contains(key) && m_oldFrameKeys.contains(key); }

void KeyManager::update() { m_oldFrameKeys = m_currFrameKeys; }

void KeyManager::keyPressed(Key key) { m_currFrameKeys.insert(key); }
void KeyManager::keyReleased(Key key) { m_currFrameKeys.remove(key); }

void KeyManager::KeyMap::operator=(const KeyManager::KeyMap &other) 
{
	m_size = other.m_size;
	for(unsigned char i = 0; i < m_size; ++i) m_keys[i] = other.m_keys[i];
}

void KeyManager::KeyMap::insert(Key key)
{
	if(!contains(key) && m_size < KeyManager::KeyMap::ArraySize)
		m_keys[m_size++] = key;
}

void KeyManager::KeyMap::remove(Key key)
{
	for(unsigned char i = 0; i < m_size; ++i)
		if(m_keys[i] == key)
		{
			m_keys[i] = m_keys[--m_size];
			return;
		}
}

bool KeyManager::KeyMap::contains(Key key) const
{
	for(unsigned char i = 0; i < m_size; ++i)
		if(m_keys[i] == key) return true;
	return false;
}

