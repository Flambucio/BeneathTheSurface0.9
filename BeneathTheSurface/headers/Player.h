#pragma once
#include  "Core.h"
#include "Textures.h"
#include "Inventory.h"
#include "State.h"
#include "Audio.h"

namespace BenTheSur
{

	class Player
	{
	public:
		Inventory inventory;
		int x = 0;
		int y = 0;
		int dx = 0;
		int dy = 0;
		double gravity_speed = 0.1;
		bool can_jump = true;
		int offset_texture = 1;
		Rectangle hitbox = { 0+TILESIZE/4.0f,0,TILESIZE/2.0,TILESIZE };
		void ResetMovement();
		void Fall();//
		void CalculateMovement();//
		void Spawn(int x, int y);//
		void Render();//
		void PhysicsUpdate();//
		void UpdateHitbox();//
		void ApplyMovementX();//
		void ApplyMovementY();//
		void PoolEvents();//
		void SpriteSelector();

	};

}
