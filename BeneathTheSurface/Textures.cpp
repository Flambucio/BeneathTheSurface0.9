#include "headers/Textures.h"

using	Txt = BenTheSur::Textures;

void Txt::LoadBlocks()
{
	Image image = LoadImage("resources/tiles.png");
	blocks_tile_map = LoadTextureFromImage(image);
	UnloadImage(image);
}


void Txt::LoadItems()
{
	Image image = LoadImage("resources/Items.png");
	items_tile_map= LoadTextureFromImage(image);
	UnloadImage(image);
}

void Txt::Load()
{
	LoadBlocks();
	LoadItems();
}

void Txt::Unload()
{
	UnloadTexture(blocks_tile_map);
	UnloadTexture(items_tile_map);
}

Texture2D Txt::blocks_tile_map = { 0 };
Texture2D Txt::items_tile_map = { 0 };