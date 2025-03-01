	#pragma once
    #include "maps.h"
	namespace BenTheSur
	{

		template<typename Main>
		class World
		{
		public:
			Main& main;
			World(Main& main) : main(main) {}
			std::vector<std::unique_ptr<GameObject>> loadedBlocks;
			int level_selected = 1;
			std::array<std::array<int, NUM_TILES_HOR>, NUM_TILES_VER> loaded_map = Maps::map_test_blocks;
	/*		std::array<std::array<int, NUM_TILES_HOR>, NUM_TILES_VER> map = {{
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
				{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
				{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0}},
				{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0}},
				{{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}
			} };*/


			void Load()
			{
				for (int i = 0;i < NUM_TILES_VER;i++)
				{
					for (int j = 0;j < NUM_TILES_HOR;j++)
					{
						int map_num = loaded_map[i][j];
						SpawnStaticObj(i,j,map_num);
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
							if (main.player.dy > 0)
							{
								main.player.can_jump = true;
							}
						}
						else if (main.player.dy > 0)
						{
							main.player.can_jump = false;
						}
					}
				}
				ApplyMovement(collides_hor, collides_ver);
				//std::cout << "Player: x=" << main.player.x << ", y=" << main.player.y << ", dx=" << main.player.dx << ", dy=" << main.player.dy << std::endl;
				//std::cout << "Collides? Horizontal: " << collides_hor << ", Vertical: " << collides_ver << std::endl;
			}


			void ApplyMovement(bool coll_hor,bool coll_ver)
			{
				//PRINT("apply:");
				//PRINTLN(main.player.dy);
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
						main.player.y = ((main.player.y + TILESIZE - 1) / TILESIZE) * TILESIZE;

						main.player.dy = 0;
						main.player.gravity_speed = 0;
					}
					else
					{
						main.player.dy = 0;
						main.player.can_jump = false;
					}
				}
			}

			void SpawnStaticObj(int i, int j,int value)
			{
				int y = i * TILESIZE;
				int x = j * TILESIZE;
				if (value == dirt || value == stone || value == rock || value==grass)
				{
					loadedBlocks.push_back(std::make_unique<SolidBlock>(x, y, value));
				}
				else if (value == breakable_dirt || value == breakable_stone || value == breakable_rock)
				{
					loadedBlocks.push_back(std::make_unique<BreakableBlock>(x, y, value));
				}
				else if (value == bg_dirt || value == bg_stone || value == bg_rock)
				{
					loadedBlocks.push_back(std::make_unique<BGBlock>(x, y, value));
				}
			}



		};


	}
