#pragma once
#include "World.h"
#include "Player.h"
#include "Textures.h"
#include "PauseMenu.h"
#include "State.h"
#include "MainMenu.h"
#include "Transition.h"
#include "Audio.h"

namespace BenTheSur
{
	class Main
	{
	public:
		bool shouldClose = false;
		double fpsAccumulator = 0.0;
		World<Main> world;
		Player player;
		PauseMenu<Main> pause_menu;
		MainMenu<Main> menu;
		Main() : world(*this), pause_menu(*this),menu(*this)
		{
			InitWindow(WIDTH,HEIGHT,CAPTION);
			SetTargetFPS(FPS_COUNT);
			Textures::Load();
			LevelInfo::LoadLevelData();
			Audio::Initialize();
			
		}
		void Run()
		{
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
				ClearBackground(BLACK);
				Update();
				EndDrawing();
			}
		}

		void Update()
		{
			
			player.PoolEvents();
			world.Update();
			player.Render();
			pause_menu.Update();
			menu.Update();
			Transition::Update();
			

			
		}

		void FixedUpdate()
		{
			player.PhysicsUpdate();
			world.PhysicsUpdate();
		}


		~Main()
		{
			Textures::Unload();
			LevelInfo::WriteLevelData();
		}
	};
}
