/* Created Day 1 */
#include "player.h"

// Key codes
#define KEY_ESC 27
#define KEY_SPACE 32

#define KEY_W 87
#define KEY_A 65
#define KEY_D 68

EntityPlayer :: EntityPlayer()
{
	ResetPlayer();
}

void EntityPlayer :: ResetPlayer()
{
	hp = 5;
	score = 0;

	isAlive = true;

	pos.x = 400;
	pos.y = 500;

	motion.x = 0;
	motion.y = 0;

	collisionBox.x = 400;
	collisionBox.y = 500;

	collisionBox.height = 50;
	collisionBox.width = 40;

	bulletCount = 1;

	obstacles.clear();
}

/*-------------------------------------------------*/

void EntityPlayer :: LoadTex()
{
	sprite = LoadTexture( "images/player.png" );

	jump = LoadSound( "sound/jump.wav" );
	destroy = LoadSound( "sound/destroy.wav" );
	gun = LoadSound ( "sound/gun.wav" );
}

void EntityPlayer :: Update()
{
	// Check player health
	if ( hp <= 0 )
	{
		isAlive = false;
	}

	// Update the position
	pos.x = pos.x + ( motion.x * GetFrameTime() );
	pos.y = pos.y + ( motion.y * GetFrameTime() );

	// Update collisioBox
	collisionBox.x = pos.x;
	collisionBox.y = pos.y;

	// Lock position in bounds
	if ( pos.x > 760 )
		pos.x = 760;
	else if ( pos.x < 0 )
		pos.x = 0;

	// Cap bullets at 50
	if ( bulletCount > 50 )
		bulletCount = 50;

	// Update onGround
	if ( pos.y >= 550 - 50 )
	{
		onGround = true;
		pos.y = 550 - 50;
		motion.y = 0;
	}
	else
	{
		onGround = false;
	}

	// Reset motion
	motion.x = 0;

	// Gravity
	if ( !onGround )
		motion.y = motion.y + 20;

	// Action keys
	if ( IsKeyPressed( KEY_SPACE ) )
	{
		if ( bulletCount != 0 )
		{
			PlaySound( gun );

			bullets.push_back( EntityBullet( pos.x + 20, pos.y ) );
			bulletCount--;
		}
	}


	// Movement keys
	if ( IsKeyPressed( KEY_W ) )
	{	
		if ( onGround )
		{
			motion.y = -600;
			PlaySound( jump );
		}
		
	}

	if ( IsKeyDown( KEY_A ))
	{
		motion.x = -300;
	}

	if ( IsKeyDown( KEY_D ))
	{
		motion.x = 300;
	}

	int value = GetRandomValue( 1, 60 );

	if ( value == 1 )
	{
		// Spawn obstacle
		Type type;

		int typeChoice = GetRandomValue(1, 20);

		switch ( typeChoice )
		{
			case 1:
				type = AMMO;
				break;

			case 2:
				type = HEALTH;
				break;

			case 3:
				type = BONUS;
				break;
			
			default:
				type = OBSTACLE;
		}

		obstacles.push_back( EntityFalling( GetRandomValue( 0, 800 ) , type) );
	}

	// Update all players bullets
	int bi = 0;
	for ( EntityBullet& b : bullets )
	{
		b.Update();

		if ( b.pos.x <= 0)
			bullets.erase(bullets.begin() + bi);

		bi++;
	}

	int oi = 0;
	for ( EntityFalling& o : obstacles )
	{
		o.Update();

		if ( CheckCollisionRecs( o.collisionBox, collisionBox ) ) // remove on hit or when out of bounds
		{
			switch ( o.type )
			{
				case AMMO:
					bulletCount++;
					break;

				case HEALTH:
					hp++;
					break;

				case BONUS:
					AddScore( 300 );
					break;

				case OBSTACLE:
					hp--;
			}

			obstacles.erase( obstacles.begin() + oi );
			PlaySound( destroy );
		}

		if ( o.pos.y > 800 )
			obstacles.erase( obstacles.begin() + oi );

		for ( EntityBullet& b : bullets )
		{
			if ( CheckCollisionRecs( b.collisionBox, o.collisionBox ) )
			{
				bulletCount++;
				AddScore( 100 );
				obstacles.erase( obstacles.begin() + oi );
				PlaySound( destroy );
			}
		}

		oi++;
	}
}

void EntityPlayer :: Draw()
{
	DrawTexture( sprite, pos.x, pos.y, WHITE );

	// Draw bullets
	for ( EntityBullet& b : bullets )
	{
		b.Draw();
	}

	for ( EntityFalling& o : obstacles )
	{
		o.Draw();
	}
}

/*-------------------------------------------------*/

void EntityPlayer :: AddScore( int amount )
{
	score = score + amount;
}

void EntityPlayer :: SetHighScore()
{
	// Unfinished score saving
}