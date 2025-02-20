#pragma once
#include "Core.h"
namespace BenTheSur
{



	class GameObject
	{
	public:
		bool collide = false;
		int type = 0;
		int x = 0;
		int y = 0;
		Rectangle hitbox;
		GameObject(int x, int y, bool collide) : x(x), y(y), collide(collide)
		{
			this->hitbox = { (float)x,(float)y,TILESIZE,TILESIZE };
		}
		virtual void Render()
		{

		}

	};

	class TestBG : public GameObject
	{
	public:
		TestBG(int x, int y, bool collide) : GameObject(x, y, collide) {}
		void Render()
		{
			DrawRectangle(x, y, TILESIZE, TILESIZE, BLUE);
		}
	};

	class TestBlock : public GameObject
	{
	public:
		TestBlock(int x, int y, bool collide) : GameObject(x, y, collide) {}
		void Render()
		{
			DrawRectangle(x, y, TILESIZE, TILESIZE, BLACK);
		}
	};




	template<typename Main>
	class World
	{
	public:
		Main& main;
		World(Main& main) : main(main) {}
		std::vector<std::unique_ptr<GameObject>> loadedBlocks;

		std::array<std::array<int, NUM_TILES_HOR>, NUM_TILES_VER> map = { {
			{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0}},
			{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0}},
			{{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}
		} };


		void Load()
		{
			for (int i = 0;i < NUM_TILES_VER;i++)
			{
				for (int j = 0;j < NUM_TILES_HOR;j++)
				{
					int map_num = map[i][j];
					switch (map_num)
					{
					case 0:
						loadedBlocks.push_back(std::make_unique<TestBG>(j * TILESIZE, i * TILESIZE, false));
						break;
					case 1:
						loadedBlocks.push_back(std::make_unique<TestBlock>(j * TILESIZE, i * TILESIZE, true));
						break;
					}
				}
			}
		}

		void Update()
		{
			for (int i = 0;i < loadedBlocks.size();i++)
			{
				loadedBlocks[i]->Render();
			}
		}



	};


}
