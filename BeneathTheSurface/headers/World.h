	#pragma once
    #include "maps.h"
	#include "State.h"
	#include "Level.h"
	#include "Audio.h"
	namespace BenTheSur
	{

		template<typename Main>
		class World
		{
		public:
			Main& main;
			World(Main& main) : main(main) {}
			int level_selected = 1;
			std::vector<std::unique_ptr<GameObject>> loadedBlocks;
			std::vector<std::unique_ptr<GameObject>> loadedInteractiveObjects;
			TileMap loaded_map = Maps::map_test_blocks;
			TileMap loaded_map_interactive = Maps::map_test_interactive_objects;
			void Load()
			{

				PRINTLN("loading");
				loaded_map = Maps::map_blocks_list[LevelInfo::level_selected - 1];
				loaded_map_interactive = Maps::map_interactive_obj_list[LevelInfo::level_selected - 1];

				for (int i = 0;i < NUM_TILES_VER;i++)
				{
					for (int j = 0;j < NUM_TILES_HOR;j++)
					{
						int map_num = loaded_map[i][j];
						SpawnStaticObj(i,j,map_num);
						int obj_num = loaded_map_interactive[i][j];
						SpawnInteractiveObj(i, j, obj_num);
					}
				}
				main.player.Spawn(Maps::spawn_points[LevelInfo::level_selected-1].x * TILESIZE, 
					Maps::spawn_points[LevelInfo::level_selected - 1].y * TILESIZE);
				main.player.inventory.ResetInventory();
				StateWrapper::SetState(playing);
			}

			void Unload()
			{
				loadedBlocks.clear();
				loadedInteractiveObjects.clear();
			}

			void Update()
			{
				if (StateWrapper::GetState() != playing && StateWrapper::GetState() != losing && StateWrapper::GetState() != winning && StateWrapper::GetState() != pausing)
				{
					return;
				}
				if (IsKeyPressed(KEY_P) && StateWrapper::GetState()==playing )
				{
					StateWrapper::SetState(pausing);
				}
				for (int i = 0;i < loadedBlocks.size();i++)
				{
					loadedBlocks[i]->Render();
				}
				for (int i = 0;i < loadedInteractiveObjects.size();i++)
				{
					loadedInteractiveObjects[i]->Render();
				}
				LevelInfo::TutorialTextsRender();
			}


			void PhysicsUpdate()
			{
				//PRINTLN("update");
				if (StateWrapper::GetState() != playing && StateWrapper::GetState() != losing && StateWrapper::GetState() != winning)
				{
					return;
				}
				if ( main.player.dy > 5)
				{
					main.player.dy = 5;
				}
				bool collides_hor = false;
				bool collides_ver = false;
				Rectangle future_rec_x = { (float)main.player.x + main.player.dx + TILESIZE/4.0f, (float)main.player.y, TILESIZE/2.0f, TILESIZE };
				Rectangle future_rec_y = { (float)main.player.x + TILESIZE/4.0f, (float)main.player.y + main.player.dy, TILESIZE/2.0f, TILESIZE };
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


						if (CheckCollisionRecs(future_rec_x, loadedBlocks[i]->hitbox) ||
							CheckCollisionRecs(future_rec_y, loadedBlocks[i]->hitbox))
						{
							if (loadedBlocks[i]->type==breakable_dirt || 
								loadedBlocks[i]->type == breakable_stone ||
									loadedBlocks[i]->type == breakable_rock)
							{
								if (loadedBlocks[i]->type == breakable_dirt && main.player.inventory.shovel_count>0)
								{
									loadedBlocks[i]->collide = false;
									main.player.inventory.shovel_count--;
									Audio::PlayBreakSound();
								}
								else if (loadedBlocks[i]->type == breakable_stone && main.player.inventory.pickaxe_count > 0)
								{
									loadedBlocks[i]->collide = false;
									main.player.inventory.pickaxe_count--;
									Audio::PlayBreakSound();
								}
								else if (loadedBlocks[i]->type == breakable_rock && main.player.inventory.drill_count > 0)
								{
									loadedBlocks[i]->collide = false;
									main.player.inventory.drill_count--;
									Audio::PlayBreakSound();
								}
								
								
							}
						}
					}
				}


				for (int i = 0;i < loadedInteractiveObjects.size();)
				{
					
					bool obj_deleted = false;
					if (CheckCollisionRecs(future_rec_x, loadedInteractiveObjects[i]->hitbox) ||
						CheckCollisionRecs(future_rec_y, loadedInteractiveObjects[i]->hitbox))
					{
						if (loadedInteractiveObjects[i]->type == lava || loadedInteractiveObjects[i]->type == spike)
						{
							if (StateWrapper::GetState() != losing)
							{
								StateWrapper::SetState(losing);
								Audio::PlayDieSound();
							}
						}
						else
						{
							if (loadedInteractiveObjects[i]->type == shovelobj)
							{
								main.player.inventory.shovel_count++;
							}
							else if (loadedInteractiveObjects[i]->type == pickaxe)
							{
								main.player.inventory.pickaxe_count++;
							}
							else if (loadedInteractiveObjects[i]->type == drillobj)
							{
								main.player.inventory.drill_count++;
							}
							else
							{
								StateWrapper::SetState(winning);
								LevelInfo::LevelFinished();
							}
							loadedInteractiveObjects.erase(loadedInteractiveObjects.begin() + i);
							obj_deleted = true;
							Audio::PlayCollectSound();
						}
					}

					if (!obj_deleted)
					{
						i++;
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
					if (main.player.dy > 0)
					{
						main.player.can_jump = true;
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

			void SpawnInteractiveObj(int i, int j, int value)
			{
				int y = i * TILESIZE;
				int x = j * TILESIZE;
				if (value == gold || value == pickaxe || value == shovelobj || value == drillobj)
				{
					loadedInteractiveObjects.push_back(std::make_unique<Item>(x, y, value));
				}
				else if (value == spike)
				{
					loadedInteractiveObjects.push_back(std::make_unique<Spike>(x, y));
				}
				else if (value == lava)
				{
					loadedInteractiveObjects.push_back(std::make_unique<Lava>(x, y));
				}

			}

			~World()
			{
				loadedBlocks.clear();
				loadedInteractiveObjects.clear();
			}



		};


	}
