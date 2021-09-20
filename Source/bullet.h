/* Created day 1 */
#pragma once

#include "entity.h"

#include <vector>
using namespace std;

class EntityBullet : public EntityBase
{
	public:
	Rectangle collisionBox;

	EntityBullet( int x, int y );

	void Draw();
	void Update();
};
