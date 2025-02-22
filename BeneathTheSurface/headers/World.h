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


			void PhysicsUpdate()
			{

				if (main.player.dy < -5)
				{
					main.player.dy = -5;
				}
				if ( main.player.dy > 5)
				{
					main.player.dy = 5;
				}
				bool collides_hor = false;
				bool collides_ver = false;
				Rectangle future_rec_x = { (float)main.player.x + main.player.dx, (float)main.player.y, TILESIZE, TILESIZE };
				Rectangle future_rec_y = { (float)main.player.x, (float)main.player.y + main.player.dy, TILESIZE, TILESIZE };
				for (int i = 0;i < loadedBlocks.size();i++)
				{
					if (loadedBlocks[i]->collide)
					{
						if (CheckCollisionRecs(future_rec_x, loadedBlocks[i]->hitbox))
						{
							collides_hor = true;
						}
						if (CheckCollisionRecs(future_rec_y, loadedBlocks[i]->hitbox))
						{
							collides_ver = true;
						}
					}
				}
				ApplyMovement(collides_hor, collides_ver);
				//std::cout << "Player: x=" << main.player.x << ", y=" << main.player.y << ", dx=" << main.player.dx << ", dy=" << main.player.dy << std::endl;
				//std::cout << "Collides? Horizontal: " << collides_hor << ", Vertical: " << collides_ver << std::endl;
			}


			void ApplyMovement(bool coll_hor,bool coll_ver)
			{
				if (!coll_hor)
				{
					main.player.ApplyMovementX();
				}

				if (!coll_ver)
				{
					main.player.ApplyMovementY();
				}
				else
				{
					if (main.player.dy > 0) // Se sta cadendo
					{
						main.player.can_jump = true;

						// Posiziona esattamente sopra il blocco
						main.player.y = (main.player.y / TILESIZE) * TILESIZE;
						main.player.dy = 0;
					}
					else
					{
						main.player.can_jump = false;
					}
					if (main.player.dy < 0)
					{
						main.player.is_jumping = false;
					}
				}
			}



		};


	}
