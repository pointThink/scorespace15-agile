/* Created Day 2 */

#pragma once

#include "entity.h"

enum Type
{
	AMMO = 0,
	HEALTH = 1,
	OBSTACLE = 2,
	BONUS = 3,
};

class EntityFalling : public EntityBase
{
	public:
	Rectangle collisionBox;

	Type type;

	EntityFalling( int x, Type _type );

	void Draw();
	void Update();
};