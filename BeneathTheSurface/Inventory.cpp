#include "headers/Inventory.h"

void BenTheSur::Inventory::RenderHUD()
{
    Rectangle pickaxe_hud = {
    (float)(TEXTURE_SIZE_ITEMS * 0),
    (float)(TEXTURE_SIZE_ITEMS * 0),
    TEXTURE_SIZE_ITEMS,
    TEXTURE_SIZE_ITEMS
    };
    Rectangle shovel_hud = {
    (float)(TEXTURE_SIZE_ITEMS * 1),
    (float)(TEXTURE_SIZE_ITEMS * 0),
    TEXTURE_SIZE_ITEMS,
    TEXTURE_SIZE_ITEMS
    };
    Rectangle drill_hud = {
    (float)(TEXTURE_SIZE_ITEMS * 1),
    (float)(TEXTURE_SIZE_ITEMS * 1),
    TEXTURE_SIZE_ITEMS,
    TEXTURE_SIZE_ITEMS
    };
    Rectangle pickaxe_dest = { 0, 0, TILESIZE+TILESIZE/2.0f, TILESIZE+TILESIZE/2.0f };
    Rectangle shovel_dest = { 0, TILESIZE + TILESIZE / 2.0f, TILESIZE + TILESIZE / 2.0f, TILESIZE + TILESIZE / 2.0f };
    Rectangle drill_dest = { 0 , 2 * (TILESIZE + TILESIZE / 2.0f), TILESIZE + TILESIZE / 2.0f, TILESIZE + TILESIZE / 2.0f };
    Rectangle transparent_dest = { 0,0,2 * (TILESIZE + TILESIZE / 2.0f),3 * (TILESIZE + TILESIZE / 2.0f) };
    Vector2 origin = { 0, 0 };
    float rotation = 0.0f;
    Color tint = WHITE;
    Color transparent_black = { 0,0,0,100 };
    DrawRectangleRec(transparent_dest, transparent_black);
    DrawTexturePro(Textures::items_tile_map, pickaxe_hud, pickaxe_dest, origin, rotation, tint);
    DrawTexturePro(Textures::items_tile_map, shovel_hud, shovel_dest, origin, rotation, tint);
    DrawTexturePro(Textures::items_tile_map, drill_hud, drill_dest, origin, rotation, tint);
    std::string pickaxe_count_str = std::to_string(pickaxe_count);
    std::string shovel_count_str = std::to_string(shovel_count);
    std::string drill_count_str = std::to_string(drill_count);
    DrawText(pickaxe_count_str.c_str(), TILESIZE+TILESIZE/2.0+TILESIZE/4.0, TILESIZE/3.0, 40, WHITE);
    DrawText(shovel_count_str.c_str(), TILESIZE + TILESIZE / 2.0 + TILESIZE / 4.0, (TILESIZE / 3.0 + TILESIZE + TILESIZE / 2.0),
        40, WHITE);
    DrawText(drill_count_str.c_str(), TILESIZE + TILESIZE / 2.0 + TILESIZE / 4.0, 2*(TILESIZE / 3.0+TILESIZE+TILESIZE/3)
        , 40, WHITE);
}


void BenTheSur::Inventory::ResetInventory()
{
    pickaxe_count = 0;
    shovel_count = 0;
    drill_count = 0;
}