#include "headers/Player.h"

using Pl = BenTheSur::Player;

void Pl::Jump()
{
	if (is_jumping)
	{
		float t = 1.0f - jump_progress; // Crea un parametro temporale inverso
		dy -= (JUMP_HEIGHT * (1 - cos(t * PI / 2)));  // Usa una curva sinusoidale
		jump_progress *= JUMP_FACTOR;  // Riduci progressivamente

		if (jump_progress < 0.04)
		{
			is_jumping = false;
		}
	}
}

void Pl::Fall()
{
	    if (!is_jumping)
    {
        gravity_speed += GRAVITY_STRENGTH; // Aggiungi accelerazione costante
        if (gravity_speed > MAX_FALL_SPEED) gravity_speed = MAX_FALL_SPEED; // Limita la velocità di caduta
        dy += gravity_speed;
    }
    else
    {
        gravity_speed = 1; // Reset quando il player salta
    }
}

void Pl::Render()
{
	DrawRectangleRec(hitbox, WHITE);
}


void Pl::UpdateHitbox()
{
	hitbox = { (float)x,(float)y,TILESIZE,TILESIZE };
}

void Pl::CalculateMovement()
{
	if (IsKeyDown(KEY_A))
	{
		dx -= 3;
	}
	if (IsKeyDown(KEY_D))
	{
		dx += 3;
	}
	if (IsKeyPressed(KEY_SPACE) && can_jump)
	{
		jump_progress = JUMP_SPEED;
		is_jumping = true;
		can_jump = false;
	}
	Jump();
	Fall();

}

void Pl::Spawn(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Pl::ResetMovement()
{
	dx = 0;
}

void Pl::ApplyMovementX() { x += dx; }

void Pl::ApplyMovementY() { y += dy; }

void Pl::PoolEvents() 
{ 
	ResetMovement(); 
	CalculateMovement(); 
}

void Pl::PhysicsUpdate() { UpdateHitbox(); }

