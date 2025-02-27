#pragma once
#include "Core.h"
#include "Textures.h"

//1=dirt , 2=stone, 3= rock, 4=grass , 5=breakable dirt, 6 = breakable stone, 7 = breakable rock
// 8=bg dirt, 9=bg stone, 10=bg rock  5=spike 6=lava

enum BlockTypes{dirt=1,stone,rock,grass,breakable_dirt,breakable_stone,breakable_rock,bg_dirt,bg_stone,bg_rock};

enum BreakableBy {unbreakable,shovel,pick,drill};

enum InteractiveObjs {gold=1,shovelobj,pickaxe,drillobj,spike,lava};

namespace BenTheSur
{
	class TestGameObject
	{
	public:
		bool collide = false;
		int type = 0;
		int x = 0;
		int y = 0;
		Rectangle hitbox;
		//test constructor
		TestGameObject(int x, int y, bool collide) : x(x), y(y), collide(collide)
		{
			this->hitbox = { (float)x,(float)y,TILESIZE,TILESIZE };
		}
		//GameObject(int x,int y,int type) : x(x), y(y), type(type) {}
		virtual void Render()
		{

		}

	};

	class GameObject
	{
	public:
		bool collide = false;
		bool broken = false;
		BreakableBy breakable_by = unbreakable;
		int type = 0;
		int x = 0;
		int y = 0;
		int offset_texture_x = 0;
		int offset_texture_y = 0;
		Rectangle hitbox;
		//test constructor
		GameObject(int x, int y, int type,BreakableBy breakable_by) : x(x), y(y), type(type), breakable_by(breakable_by)
		{
			this->hitbox = { (float)x,(float)y,TILESIZE,TILESIZE };
		}
		//GameObject(int x,int y,int type) : x(x), y(y), type(type) {}
		virtual void Render()
		{

		}

	};

	class TestBG : public TestGameObject
	{
	public:
		TestBG(int x, int y, bool collide) : TestGameObject(x, y, collide) {}
		void Render()
		{
			DrawRectangle(x, y, TILESIZE, TILESIZE, BLUE);
		}
	};

	class TestBlock : public TestGameObject
	{
	public:
		TestBlock(int x, int y, bool collide) : TestGameObject(x, y, collide) {}
		void Render()
		{
			DrawRectangle(x, y, TILESIZE, TILESIZE, BLACK);
		}
	};

	class SolidBlock : public GameObject
	{
	public:
		SolidBlock(int x,int y,int type) : GameObject(x,y,type,unbreakable) 
		{
			this->collide = true;
			switch (type)
			{
			case dirt:
				offset_texture_x = 0;
				offset_texture_y = 0;
				break;
			case stone:
				this->offset_texture_y = 1;
				break;

			case rock:
				this->offset_texture_y = 2;
				break;
			case grass :
				this->offset_texture_x = 1;
			}
		}

		void Render()
		{
			Rectangle source = { (float)(TEXTURE_SIZE_BLOCKS * offset_texture_x,(float)(TEXTURE_SIZE_BLOCKS * offset_texture_y),
				TEXTURE_SIZE_BLOCKS,TEXTURE_SIZE_BLOCKS) };
			Rectangle dest = { (float)x,(float)y,TILESIZE,TILESIZE };
			Vector2 origin = { 0,0 };
			float rotation = 0.0f;
			Color tint = WHITE;
			DrawTexturePro(Textures::blocks_tile_map, source, dest, origin, rotation, tint);
		}
	};

	class BreakableBlock : public GameObject
	{
	public:
		BreakableBlock(int x, int y, int type) : GameObject(x, y, type,unbreakable) 
		{
			this->collide = true;
			switch (type)
			{
				case breakable_dirt:
					this->breakable_by = shovel;
					break;
				case breakable_stone:
					this->breakable_by = pick;
					break;
				case breakable_rock:
					this->breakable_by = drill;
					break;
			}

		
		}

		void Render()
		{
			if (collide)
			{
				switch (type)
				{
				case breakable_dirt:
					offset_texture_x = 2;
					break;
				case breakable_stone:
					offset_texture_x = 1;
					offset_texture_y = 1;
					break;
				case breakable_rock:
					offset_texture_x = 1;
					offset_texture_y = 2;
					break;
				}
			}
			else
			{
				offset_texture_y = 0;
				switch (type)
				{
				case breakable_dirt:
					offset_texture_x = 0;
					break;
				case breakable_stone:
					offset_texture_x = 1;
					break;
				case breakable_rock:
					offset_texture_x = 2;
					break;
				}
			}
			Rectangle source = { (float)(TEXTURE_SIZE_BLOCKS * offset_texture_x,(float)(TEXTURE_SIZE_BLOCKS * offset_texture_y),
	  TEXTURE_SIZE_BLOCKS,TEXTURE_SIZE_BLOCKS) };
			Rectangle dest = { (float)x,(float)y,TILESIZE,TILESIZE };
			Vector2 origin = { 0,0 };
			float rotation = 0.0f;
			Color tint = WHITE;
			DrawTexturePro(Textures::blocks_tile_map, source, dest, origin, rotation, tint);
		}

	};



	class BGBlock : public GameObject
	{
	public:
		BGBlock(int x, int y, int type) : GameObject(x, y, type, unbreakable)
		{
			this->collide = false;
			this->offset_texture_y = 3;
			switch (type)
			{
			case bg_dirt:
				offset_texture_x = 0;
				break;
			case bg_stone:
				this->offset_texture_x = 1;
				break;
			case bg_rock:
				this->offset_texture_x = 2;
				break;
			}
			

		}


		void Render()
		{
			Rectangle source = { (float)(TEXTURE_SIZE_BLOCKS * offset_texture_x,(float)(TEXTURE_SIZE_BLOCKS * offset_texture_y),
	  TEXTURE_SIZE_BLOCKS,TEXTURE_SIZE_BLOCKS) };
			Rectangle dest = { (float)x,(float)y,TILESIZE,TILESIZE };
			Vector2 origin = { 0,0 };
			float rotation = 0.0f;
			Color tint = WHITE;
			DrawTexturePro(Textures::blocks_tile_map, source, dest, origin, rotation, tint);
		}
	};


	class Spike : public GameObject
	{
	public:
		Spike(int x, int y) : GameObject(x, y, spike, unbreakable)
		{
			collide = true;
			offset_texture_x = 2;
			offset_texture_y = 1;
		}

		void Render()
		{
			Rectangle source = { (float)(TEXTURE_SIZE_BLOCKS * offset_texture_x,(float)(TEXTURE_SIZE_BLOCKS * offset_texture_y),
TEXTURE_SIZE_BLOCKS,TEXTURE_SIZE_BLOCKS) };
			Rectangle dest = { (float)x,(float)y,TILESIZE,TILESIZE };
			Vector2 origin = { 0,0 };
			float rotation = 0.0f;
			Color tint = WHITE;
			DrawTexturePro(Textures::blocks_tile_map, source, dest, origin, rotation, tint);
		}
	};


	class Lava : public GameObject
	{
	public:
		Lava(int x,int y) : GameObject(x,y,lava,unbreakable) 
		{
			this->collide = true;
			this->offset_texture_x = 2;
			this->offset_texture_y = 2;
		}


		void Render()
		{
			Rectangle source = { (float)(TEXTURE_SIZE_BLOCKS * offset_texture_x,(float)(TEXTURE_SIZE_BLOCKS * offset_texture_y),
TEXTURE_SIZE_BLOCKS,TEXTURE_SIZE_BLOCKS) };
			Rectangle dest = { (float)x,(float)y,TILESIZE,TILESIZE };
			Vector2 origin = { 0,0 };
			float rotation = 0.0f;
			Color tint = WHITE;
			DrawTexturePro(Textures::blocks_tile_map, source, dest, origin, rotation, tint);
		}
	};

	class Item : public GameObject
	{
		Item(int x, int y, int type) : GameObject(x,y,type,unbreakable)
		{
			collide = true;
			switch (type)
			{
			case gold:
				offset_texture_x = 0;
				offset_texture_y = 1;
				break;
			case shovelobj:
				offset_texture_x = 1;
				offset_texture_y = 0;
				break;
			case pickaxe:
				offset_texture_x = 0;
				offset_texture_y = 0;
				break;
			case drillobj:
				offset_texture_x = 1;
				offset_texture_y = 1;
			}
		}

		void Render()
		{
			Rectangle source = { (float)(TEXTURE_SIZE_ITEMS * offset_texture_x,(float)(TEXTURE_SIZE_ITEMS * offset_texture_y),
TEXTURE_SIZE_ITEMS,TEXTURE_SIZE_ITEMS) };
			Rectangle dest = { (float)x,(float)y,TILESIZE,TILESIZE };
			Vector2 origin = { 0,0 };
			float rotation = 0.0f;
			Color tint = WHITE;
			DrawTexturePro(Textures::items_tile_map, source, dest, origin, rotation, tint);
		}
	};
	





}
