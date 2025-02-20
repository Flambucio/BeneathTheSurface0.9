#pragma once
#include "World.h"

namespace BenTheSur
{
	class Main
	{
	public:
		bool shouldClose = false;
		double fpsAccumulator = 0.0;
		World<Main> world;
		Main() : world(*this)
		{
			InitWindow(WIDTH,HEIGHT,CAPTION);
			
		}
		void Run()
		{
			world.Load();
			while (!WindowShouldClose() && !shouldClose)
			{
				BeginDrawing();
				DeltaTime::Update();
				fpsAccumulator += DeltaTime::Get();
				while (fpsAccumulator > FIXED_TIMESTEP)
				{
					fpsAccumulator -= FIXED_TIMESTEP;
					FixedUpdate();
				}
				Update();
				EndDrawing();
			}
		}

		void Update()
		{
			world.Update();

		}

		void FixedUpdate()
		{

		}
	};
}
