#pragma once
#include  "Core.h"

namespace BenTheSur
{



	class Player
	{
	public:
		int x = 0;
		int y = 0;
		int dx = 0;
		int dy = 0;
		double jump_progress = 0;
		bool is_jumping = false;
		double gravity_speed = 1;
		bool can_jump = true;
		Rectangle hitbox = { 0,0,TILESIZE,TILESIZE };
		void ResetMovement();
		void Jump();//
		void Fall();//
		void CalculateMovement();//
		void Spawn(int x, int y);//
		void Render();//
		void PhysicsUpdate();//
		void UpdateHitbox();//
		void ApplyMovementX();//
		void ApplyMovementY();//
		void PoolEvents();//

	};

}
