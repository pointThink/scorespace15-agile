/* Created day 1 */
#include "bullet.h"

EntityBullet :: EntityBullet( int x, int y )
{
	pos.x = x;
	pos.y = y;

	motion.y = -500;
	motion.x = 0;

	collisionBox.x = pos.x;
	collisionBox.y = pos.y;

	collisionBox.height = 10;
	collisionBox.width = 5;
}

/* ---------------------------------------- */

void EntityBullet :: Update()
{
	// Update the position
	pos.x = pos.x + ( motion.x * GetFrameTime() );
	pos.y = pos.y + ( motion.y * GetFrameTime() );

	// Update hitbox
	collisionBox.x = pos.x;
	collisionBox.y = pos.y;
}

void EntityBullet :: Draw()
{
	DrawRectangleGradientH( pos.x, pos.y, 5, 10, YELLOW, ORANGE);
}

/* ---------------------------------------- */
