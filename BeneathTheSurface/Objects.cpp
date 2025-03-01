#include "headers/Objects.h"

namespace BenTheSur
{
    // TestGameObject Constructor
    TestGameObject::TestGameObject(int x, int y, bool collide) : x(x), y(y), collide(collide)
    {
        this->hitbox = { (float)x, (float)y, TILESIZE, TILESIZE };
    }

    void TestGameObject::Render()
    {
        // Default render, override in subclasses
    }

    // GameObject Constructor
    GameObject::GameObject(int x, int y, int type, BreakableBy breakable_by)
        : x(x), y(y), type(type), breakable_by(breakable_by)
    {
        this->hitbox = { (float)x, (float)y, TILESIZE, TILESIZE };
    }

    void GameObject::Render()
    {
        // Default render, override in subclasses
    }

    // TestBG Constructor
    TestBG::TestBG(int x, int y, bool collide) : TestGameObject(x, y, collide) {}

    void TestBG::Render()
    {
        DrawRectangle(x, y, TILESIZE, TILESIZE, BLUE);
    }

    // TestBlock Constructor
    TestBlock::TestBlock(int x, int y, bool collide) : TestGameObject(x, y, collide) {}

    void TestBlock::Render()
    {
        DrawRectangle(x, y, TILESIZE, TILESIZE, BLACK);
    }

    // SolidBlock Constructor
    SolidBlock::SolidBlock(int x, int y, int type) : GameObject(x, y, type, unbreakable)
    {
        this->collide = true;
        switch (type)
        {
        case dirt:
            offset_texture_x = 0;
            offset_texture_y = 0;
            break;
        case stone:
            offset_texture_y = 1;
            break;
        case rock:
            offset_texture_y = 2;
            break;
        case grass:
            offset_texture_x = 1;
            break;
        }
    }

    void SolidBlock::Render()
    {
        Rectangle source = {
            (float)(TEXTURE_SIZE_BLOCKS * offset_texture_x),
            (float)(TEXTURE_SIZE_BLOCKS * offset_texture_y),
            TEXTURE_SIZE_BLOCKS,
            TEXTURE_SIZE_BLOCKS
        };
        Rectangle dest = { (float)x, (float)y, TILESIZE, TILESIZE };
        Vector2 origin = { 0, 0 };
        float rotation = 0.0f;
        Color tint = WHITE;
        DrawTexturePro(Textures::blocks_tile_map, source, dest, origin, rotation, tint);
    }

    // BreakableBlock Constructor
    BreakableBlock::BreakableBlock(int x, int y, int type) : GameObject(x, y, type, unbreakable)
    {
        this->collide = true;
        switch (type)
        {
        case breakable_dirt:
            this->breakable_by = shovel;
            break;
        case breakable_stone:
            this->breakable_by = pick;
            break;
        case breakable_rock:
            this->breakable_by = drill;
            break;
        }
    }

    void BreakableBlock::Render()
    {
        if (collide)
        {
            switch (type)
            {
            case breakable_dirt:
                offset_texture_x = 2;
                break;
            case breakable_stone:
                offset_texture_x = 1;
                offset_texture_y = 1;
                break;
            case breakable_rock:
                offset_texture_x = 1;
                offset_texture_y = 2;
                break;
            }
        }
        else
        {
            offset_texture_y = 0;
            switch (type)
            {
            case breakable_dirt:
                offset_texture_x = 0;
                break;
            case breakable_stone:
                offset_texture_x = 1;
                break;
            case breakable_rock:
                offset_texture_x = 2;
                break;
            }
        }

        Rectangle source = {
            (float)(TEXTURE_SIZE_BLOCKS * offset_texture_x),
            (float)(TEXTURE_SIZE_BLOCKS * offset_texture_y),
            TEXTURE_SIZE_BLOCKS,
            TEXTURE_SIZE_BLOCKS
        };
        Rectangle dest = { (float)x, (float)y, TILESIZE, TILESIZE };
        Vector2 origin = { 0, 0 };
        float rotation = 0.0f;
        Color tint = WHITE;
        DrawTexturePro(Textures::blocks_tile_map, source, dest, origin, rotation, tint);
    }

    // BGBlock Constructor
    BGBlock::BGBlock(int x, int y, int type) : GameObject(x, y, type, unbreakable)
    {
        this->collide = false;
        this->offset_texture_y = 3;
        switch (type)
        {
        case bg_dirt:
            offset_texture_x = 0;
            break;
        case bg_stone:
            offset_texture_x = 1;
            break;
        case bg_rock:
            offset_texture_x = 2;
            break;
        }
    }

    void BGBlock::Render()
    {
        Rectangle source = {
            (float)(TEXTURE_SIZE_BLOCKS * offset_texture_x),
            (float)(TEXTURE_SIZE_BLOCKS * offset_texture_y),
            TEXTURE_SIZE_BLOCKS,
            TEXTURE_SIZE_BLOCKS
        };
        Rectangle dest = { (float)x, (float)y, TILESIZE, TILESIZE };
        Vector2 origin = { 0, 0 };
        float rotation = 0.0f;
        Color tint = WHITE;
        DrawTexturePro(Textures::blocks_tile_map, source, dest, origin, rotation, tint);
    }

    // Spike Constructor
    Spike::Spike(int x, int y) : GameObject(x, y, spike, unbreakable)
    {
        collide = true;
        offset_texture_x = 2;
        offset_texture_y = 1;
    }

    void Spike::Render()
    {
        Rectangle source = {
            (float)(TEXTURE_SIZE_BLOCKS * offset_texture_x),
            (float)(TEXTURE_SIZE_BLOCKS * offset_texture_y),
            TEXTURE_SIZE_BLOCKS,
            TEXTURE_SIZE_BLOCKS
        };
        Rectangle dest = { (float)x, (float)y, TILESIZE, TILESIZE };
        Vector2 origin = { 0, 0 };
        float rotation = 0.0f;
        Color tint = WHITE;
        DrawTexturePro(Textures::blocks_tile_map, source, dest, origin, rotation, tint);
    }

    // Lava Constructor
    Lava::Lava(int x, int y) : GameObject(x, y, lava, unbreakable)
    {
        collide = true;
        offset_texture_x = 2;
        offset_texture_y = 2;
    }

    void Lava::Render()
    {
        Rectangle source = {
            (float)(TEXTURE_SIZE_BLOCKS * offset_texture_x),
            (float)(TEXTURE_SIZE_BLOCKS * offset_texture_y),
            TEXTURE_SIZE_BLOCKS,
            TEXTURE_SIZE_BLOCKS
        };
        Rectangle dest = { (float)x, (float)y, TILESIZE, TILESIZE };
        Vector2 origin = { 0, 0 };
        float rotation = 0.0f;
        Color tint = WHITE;
        DrawTexturePro(Textures::blocks_tile_map, source, dest, origin, rotation, tint);
    }

    // Item Constructor
    Item::Item(int x, int y, int type) : GameObject(x, y, type, unbreakable)
    {
        collide = true;
        switch (type)
        {
        case gold:
            offset_texture_x = 0;
            offset_texture_y = 1;
            break;
        case shovelobj:
            offset_texture_x = 1;
            offset_texture_y = 0;
            break;
        case pickaxe:
            offset_texture_x = 0;
            offset_texture_y = 0;
            break;
        case drillobj:
            offset_texture_x = 1;
            offset_texture_y = 1;
            break;
        }
    }

    void Item::Render()
    {
        Rectangle source = {
            (float)(TEXTURE_SIZE_ITEMS * offset_texture_x),
            (float)(TEXTURE_SIZE_ITEMS * offset_texture_y),
            TEXTURE_SIZE_ITEMS,
            TEXTURE_SIZE_ITEMS
        };
        Rectangle dest = { (float)x, (float)y, TILESIZE, TILESIZE };
        Vector2 origin = { 0, 0 };
        float rotation = 0.0f;
        Color tint = WHITE;
        DrawTexturePro(Textures::items_tile_map, source, dest, origin, rotation, tint);
    }
}