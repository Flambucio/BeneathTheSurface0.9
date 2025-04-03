#include "headers/Player.h"

using Pl = BenTheSur::Player;


void Pl::Fall()
{
	//PRINTLN("fall chiamata");	
	//PRINT("Prima di aggiornare: ");
	//PRINTLN(gravity_speed);
	if (dy == 0)
	{
		dy = 3;
	}

	
	dy += gravity_speed;
	gravity_speed += 0.05;
	//PRINT("Dopo aggiornamento: ");
	//PRINTLN(gravity_speed);

}

void Pl::Render()
{
	if (StateWrapper::GetState() == playing && !(StateWrapper::GetState() == winning ||
		StateWrapper::GetState() == losing))
	{
		SpriteSelector();
		Rectangle source = {
		(float)(TEXTURE_SIZE_ITEMS * offset_texture),
		(float)(0),
		TEXTURE_SIZE_ITEMS,
		TEXTURE_SIZE_ITEMS
		};
		Rectangle dest = { (float)x, (float)y, TILESIZE, TILESIZE };
		Vector2 origin = { 0, 0 };
		float rotation = 0.0f;
		Color tint = WHITE;

		DrawTexturePro(Textures::player_atlas, source, dest, origin, rotation, tint);
		//DrawRectangleRec(hitbox, RED);
		inventory.RenderHUD();
	}

}


void Pl::UpdateHitbox()
{
	hitbox = { (float)x+(float)TILESIZE/4.0f,(float)y,TILESIZE/2.0f,TILESIZE };
}

void Pl::CalculateMovement()
{
	if (StateWrapper::GetState() == playing && !(StateWrapper::GetState() == winning ||
		StateWrapper::GetState() == losing))
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
			Audio::PlayJumpSound();
			can_jump = false;
			dy = -8;
			
			//PRINTLN("jump chiamato");
		}
		Fall();
		//PRINT("calculation:");
		//PRINTLN(dy);

	}

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


void Pl::SpriteSelector()
{
	if (dx != 0)
	{
		if (dx > 0)
		{
			offset_texture = 0;
		}
		else
		{
			offset_texture = 2;
		}
	}
	else
	{
		offset_texture = 1;
	}
}

