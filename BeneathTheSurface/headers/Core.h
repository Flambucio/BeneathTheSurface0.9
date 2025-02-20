#pragma once
#include "raylib/include/raylib.h"

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>
#include <array>

#ifdef GAME_DEBUG
#define PRINT(x) std::cout << x << " "
#define PRINTLN(x) std::cout << x << '\n'
#define ERROR(x) std::cerr << x << std::endl
#else
#define PRINT(x)
#define PRINTLN(x)
#define ERROR(x)
#endif



#define WIDTH 1280
#define HEIGHT 720
#define CAPTION "Beneath The Surface"
#define TILESIZE 40
#define FIXED_TIMESTEP 1.0/144.0
#define NUM_TILES_HOR WIDTH/TILESIZE
#define NUM_TILES_VER HEIGHT/TILESIZE

namespace BenTheSur
{
	static class DeltaTime
	{
	private:
		static std::chrono::high_resolution_clock::time_point lastTime;
		static double deltaTime;
	public:
		static void Update()
		{
			auto now = std::chrono::high_resolution_clock::now();
			deltaTime = std::chrono::duration<double>(now - lastTime).count();
			lastTime = now;
		}
		static double Get()
		{
			return deltaTime;
		}
	};

	std::chrono::high_resolution_clock::time_point DeltaTime::lastTime = std::chrono::high_resolution_clock::now();
	double DeltaTime::deltaTime = 0.0;
}