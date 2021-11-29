#include "InputManager.h"

void InputManager::update()
{
	for (auto& i : keyMap)
	{
		prevKeyMap[i.first] = i.second;
	}
}

void InputManager::pressKey(unsigned int keyID)
{
	keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID)
{
	keyMap[keyID] = false;
}

void InputManager::setMouseCoords(float x, float y)
{
	mouseCoords.x = x;
	mouseCoords.y = y;
}

bool InputManager::isKeyDown(unsigned int keyID)
{
	auto i = keyMap.find(keyID);
	if (i != keyMap.end())
		return i->second;
	return false;
}

bool InputManager::isKeyPressed(unsigned int keyID)
{
	if (isKeyDown(keyID) && !wasKeyDown(keyID))
		return true;
	return false;
}


bool InputManager::wasKeyDown(unsigned int keyID)
{
	auto i = prevKeyMap.find(keyID);
	if (i != prevKeyMap.end())
		return i->second;
	return false;
}
