#pragma once
#include "World.h"
#include "Player.h"
#include "Textures.h"

namespace BenTheSur
{
	class Main
	{
	public:
		bool shouldClose = false;
		double fpsAccumulator = 0.0;
		World<Main> world;
		Player player;
		Main() : world(*this)
		{
			InitWindow(WIDTH,HEIGHT,CAPTION);
			SetTargetFPS(FPS_COUNT);
			Textures::Load();
			
		}
		void Run()
		{
			world.Load();
			player.Spawn(2 * TILESIZE, 15 * TILESIZE);
			while (!WindowShouldClose() && !shouldClose)
			{
				BeginDrawing();
				DeltaTime::Update();
				fpsAccumulator += DeltaTime::Get();
				while (fpsAccumulator > FIXED_TIMESTEP)
				{
					fpsAccumulator -= FIXED_TIMESTEP;
					//PRINTLN(player.gravity_speed);
					FixedUpdate();
				}
				Update();
				EndDrawing();
			}
		}

		void Update()
		{
			player.PoolEvents();
			world.Update();
			player.Render();

			
		}

		void FixedUpdate()
		{
			player.PhysicsUpdate();
			world.PhysicsUpdate();
		}
	};
}
