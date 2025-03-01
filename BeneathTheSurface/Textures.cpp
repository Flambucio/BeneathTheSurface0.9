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
}

void Txt::Unload()
{
	UnloadTexture(blocks_tile_map);
	UnloadTexture(items_tile_map);
}

Texture2D Txt::blocks_tile_map = { 0 };
Texture2D Txt::items_tile_map = { 0 };