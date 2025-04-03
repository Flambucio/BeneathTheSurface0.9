#include "headers/Textures.h"

using	Txt = BenTheSur::Textures;

void Txt::LoadBlocks()
{
	blocks_tile_map=LoadTexture("resources/tiles.png");
	PRINT("BLOCK TEXTURE ID:");
	TraceLog(LOG_INFO, "Texture ID: %d", Textures::blocks_tile_map.id);
}


void Txt::LoadItems()
{
	items_tile_map=LoadTexture("resources/Items.png");
}

void Txt::Load()
{
	LoadBlocks();
	LoadItems();
	LoadPlayer();
	LoadButtons();
	LoadLevelNumbers();
	LoadCustomFont();
	LoadBG();
}

void Txt::Unload()
{
	UnloadTexture(blocks_tile_map);
	UnloadTexture(items_tile_map);
	UnloadTexture(play_texture);
	UnloadTexture(exit_texture);
	UnloadTexture(menu_texture);
	UnloadTexture(restart_texture);
	UnloadTexture(resume_texture);
	UnloadTexture(background);
	for (int i = 0;i < level_numbers.size(); i++)
	{
		UnloadTexture(level_numbers[i]);
	}
}

void Txt::LoadPlayer()
{
	player_atlas = LoadTexture("resources/stickman_sprites.png");
}

void Txt::LoadLevelNumbers()
{
	for (int i = 0;i < 6; i++)
	{
		std::string path = "resources/" + std::to_string(i+1) + ".png";
		Texture2D texture=LoadTexture(path.c_str());
		level_numbers[i] = texture;
	}
}

void Txt::LoadButtons()
{
	play_texture=LoadTexture("resources/play.png");
	exit_texture = LoadTexture("resources/exit.png");
	menu_texture = LoadTexture("resources/menu.png");
	restart_texture = LoadTexture("resources/restart.png");
	resume_texture = LoadTexture("resources/resume.png");
}

void Txt::LoadCustomFont()
{
	daydream = LoadFont("resources/Daydream.ttf");
}

void Txt::LoadBG()
{
	background = LoadTexture("resources/background.png");
}

Texture2D Txt::blocks_tile_map = { 0 };
Texture2D Txt::items_tile_map = { 0 };
Texture2D Txt::player_atlas = { 0 };
Texture2D Txt::play_texture = { 0 };
Texture2D Txt::exit_texture = { 0 };
Texture2D Txt::restart_texture = { 0 };
Texture2D Txt::resume_texture = { 0 };
Texture2D Txt::menu_texture = { 0 };
Texture2D Txt::background = { 0 };
std::array<Texture2D, 6> Txt::level_numbers = { {} };
Font Txt::daydream = { 0 };

