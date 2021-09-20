/* Created Day 1 */
#pragma once

#include "raylib.h"

class EntityBase // Base class for all game objects (duh)
{
	public:
	Vector2 pos;
	Vector2 motion;

	virtual void Update() {}
	virtual void Draw() {}
};