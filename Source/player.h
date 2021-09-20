/* Created Day 1 */
#pragma once

#include <algorithm>
#include <vector>

#include "entity.h"
#include "bullet.h"
#include "falling.h"

class EntityPlayer : public EntityBase
{
	public:
	Rectangle collisionBox;
	Texture sprite;

	Sound destroy;
	Sound gun;
	Sound jump;

	int hp;
	int score;
	int bulletCount;

	bool onGround;
	bool isAlive;

	std::vector<EntityBullet> bullets;
	std::vector<EntityFalling> obstacles;

	EntityPlayer();
	void ResetPlayer();

	void LoadTex();

	void Update();
	void Draw();

	void AddScore( int amount );
	void SetHighScore();
};