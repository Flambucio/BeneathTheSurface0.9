#pragma once
#include "Core.h"
#include "Textures.h"

enum BlockTypes { dirt = 1, stone, rock, grass, breakable_dirt, breakable_stone, breakable_rock, bg_dirt, bg_stone, bg_rock };

enum BreakableBy { unbreakable, shovel, pick, drill };

enum InteractiveObjs { gold = 1, shovelobj, pickaxe, drillobj, spike, lava };

namespace BenTheSur
{
    class TestGameObject
    {
    public:
        bool collide = false;
        int type = 0;
        int x = 0;
        int y = 0;
        Rectangle hitbox;

        TestGameObject(int x, int y, bool collide);
        virtual void Render();
    };

    class GameObject
    {
    public:
        bool collide = false;
        BreakableBy breakable_by = unbreakable;
        int type = 0;
        int x = 0;
        int y = 0;
        int offset_texture_x = 0;
        int offset_texture_y = 0;
        Rectangle hitbox;

        GameObject(int x, int y, int type, BreakableBy breakable_by);
        virtual void Render();
    };

    class TestBG : public TestGameObject
    {
    public:
        TestBG(int x, int y, bool collide);
        void Render() override;
    };

    class TestBlock : public TestGameObject
    {
    public:
        TestBlock(int x, int y, bool collide);
        void Render() override;
    };

    class SolidBlock : public GameObject
    {
    public:
        SolidBlock(int x, int y, int type);
        void Render() override;
    };

    class BreakableBlock : public GameObject
    {
    public:
        BreakableBlock(int x, int y, int type);
        void Render() override;
    };

    class BGBlock : public GameObject
    {
    public:
        BGBlock(int x, int y, int type);
        void Render() override;
    };

    class Spike : public GameObject
    {
    public:
        Spike(int x, int y);
        void Render() override;
    };

    class Lava : public GameObject
    {
    public:
        Lava(int x, int y);
        void Render() override;
    };

    class Item : public GameObject
    {
    public:
        Item(int x, int y, int type);
        void Render() override;
    };
}