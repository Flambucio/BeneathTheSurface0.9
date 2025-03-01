#include "headers/Player.h"

using Pl = BenTheSur::Player;

void Pl::Jump()
{

}

void Pl::Fall()
{
	//PRINTLN("fall chiamata");	
	//PRINT("Prima di aggiornare: ");
	//PRINTLN(gravity_speed);
	if (dy == 0)
	{
		dy = 3; // Imposta una velocità di caduta iniziale
	}

	
	dy += gravity_speed;
	gravity_speed += 0.05;
	//PRINT("Dopo aggiornamento: ");
	//PRINTLN(gravity_speed);

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
	if (IsKeyPressed(KEY_SPACE) && can_jump)  //&&can_jump
	{
		can_jump = false;
		dy = -8;
		//PRINTLN("jump chiamato");
	}
	Jump();
	Fall();
	//PRINT("calculation:");
	//PRINTLN(dy);

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

void Pl::ApplyMovementX() 
{
	x += dx; 

}

void Pl::ApplyMovementY() 
{
	y += dy;
}

void Pl::PoolEvents() 
{ 
	ResetMovement(); 
	CalculateMovement(); 
}

void Pl::PhysicsUpdate() { UpdateHitbox(); }

