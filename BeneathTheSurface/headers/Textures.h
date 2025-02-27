#pragma once

#include "Core.h"
namespace BenTheSur
{
	static class Textures
	{
	public:
		static Texture2D blocks_tile_map;
		static Texture2D items_tile_map;
		static void Load();
		static void Unload();
	private:
		static void LoadBlocks();
		static void LoadItems();
		//void LoadPlayer();
		//void LoadMenu();
	};
}

