#pragma once

#include "Core.h"
namespace BenTheSur
{
	static class Textures
	{
	public:
		static Texture2D blocks_tile_map;
		static Texture2D items_tile_map;
		static Texture2D player_atlas;
		static std::array<Texture2D,6> level_numbers;
		static Texture2D play_texture;
		static Texture2D restart_texture;
		static Texture2D resume_texture;
		static Texture2D exit_texture;
		static Texture2D menu_texture;
		static Texture2D background;
		static Font daydream;
		static void Load();
		static void Unload();

	private:
		static void LoadBlocks();
		static void LoadItems();
		static void LoadPlayer();
		static void LoadLevelNumbers();
		static void LoadButtons();
		static void LoadCustomFont();
		static void LoadBG();
		//void LoadMenu();
	};
}

