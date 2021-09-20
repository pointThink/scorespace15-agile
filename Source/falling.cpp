/* Created Day 2 */
#include "falling.h"

EntityFalling :: EntityFalling( int x, Type _type )
{
	motion.y = 300;
	motion.x = 0;

	pos.x = x;
	pos.y = -10;

	collisionBox.width = 40;
	collisionBox.height = 40;

	type = _type;
}

/* ------------------------------------- */

void EntityFalling :: Update()
{
	// Update the position
	pos.x = pos.x + ( motion.x * GetFrameTime() );
	pos.y = pos.y + ( motion.y * GetFrameTime() );

	// Update hitbox
	collisionBox.x = pos.x;
	collisionBox.y = pos.y;
}

void EntityFalling :: Draw()
{
	Color color;

	if ( type == AMMO )
	{
		color = YELLOW;
	}
	else if ( type == HEALTH )
	{
		color = GREEN;
	}
	else if ( type == BONUS )
	{
		color = BLUE;
	}
	else
	{
		color = RED;
	}

	DrawRectangle( pos.x, pos.y, 40, 40, BLACK );
	DrawRectangleGradientV( pos.x + 5, pos.y + 5, 30, 30, WHITE, color );
}