#pragma once
#include "Core.h"
#include "State.h"
#include "Textures.h"
#include "Button.h"
#include "Level.h"
namespace BenTheSur
{

	template<typename Main>
	class MainMenu
	{
	public:
		Main& main;
		
		Button play{ WIDTH / 2 - 100, HEIGHT / 2 - 32, 200, 64, Textures::play_texture,
		[this]() {this->PlayFunc();} };
		Button exit{ WIDTH / 2 - 100, HEIGHT / 2 + 64, 200, 64 , Textures::exit_texture,
		[this]() {this->ExitFunc();} };
		Button menu{ 0,0,200,64,Textures::menu_texture,
		[this]() {this->MenuFunc();} };
		std::array<Button, 6> level_nums_buttons{
		  Button(WIDTH / 2 - 50 - 150, HEIGHT / 2 - 50 - 50, 100, 100, Textures::level_numbers[0], [this]() { this->Load1(); }),
		  Button(WIDTH / 2 - 50, HEIGHT / 2 - 50 - 50, 100, 100, Textures::level_numbers[1], [this]() { this->Load2(); }),
		  Button(WIDTH / 2 - 50 + 150, HEIGHT / 2 - 50-50, 100, 100, Textures::level_numbers[2], [this]() { this->Load3(); }),
		  Button(WIDTH / 2 - 50 - 150, HEIGHT / 2 + 50, 100, 100, Textures::level_numbers[3], [this]() { this->Load4(); }),
		  Button(WIDTH / 2 - 50, HEIGHT / 2 + 50, 100, 100, Textures::level_numbers[4], [this]() { this->Load5(); }),
		  Button(WIDTH / 2 - 50 + 150, HEIGHT / 2 + 50, 100, 100, Textures::level_numbers[5], [this]() { this->Load6(); })
		};

		MainMenu(Main& main) :  main(main)
		{
		}
		void Update()
		{
			
			if (StateWrapper::GetState()==inmenu)
			{
				DrawTexture(Textures::background, 0, 0, WHITE);
				DrawTextPro(Textures::daydream, "Beneath  The  Surface", { 60, 100 }, { 0,0 }, 0.0f, 80.0f, 1.0f, ORANGE);
				exit.Update();
				play.Update();
			}
			else if (StateWrapper::GetState()==level_selection)
			{
				DrawTexture(Textures::background, 0, 0, WHITE);
				menu.Update();
				for (int i = 0;i < level_nums_buttons.size();i++)
				{
					if (i + 1 <= LevelInfo::max_level_unlocked)
					{
						level_nums_buttons[i].Update();
					}
					else
					{
						DrawRectangleRec(level_nums_buttons[i].dest, BLACK);
					}

				}
			}
		}
		void ExitFunc()
		{
			main.shouldClose = true;
		}
		void MenuFunc()
		{
			StateWrapper::SetState(inmenu);
			Transition::StartTransition();
		}
		void LevelButtonsFunc()
		{
			main.world.Unload();
			main.world.Load();
			Transition::StartTransition();
		}
		void PlayFunc()
		{
			StateWrapper::SetState(level_selection);
			Transition::StartTransition();
		}
		void Load1()
		{
			LevelInfo::level_selected = 1;
			LevelButtonsFunc();
		}
		void Load2()
		{
			LevelInfo::level_selected = 2;
			LevelButtonsFunc();
		}
		void Load3()
		{
			LevelInfo::level_selected = 3;
			LevelButtonsFunc();
		}
		void Load4()
		{
			LevelInfo::level_selected = 4;
			LevelButtonsFunc();
		}
		void Load5()
		{
			LevelInfo::level_selected = 5;
			LevelButtonsFunc();
		}
		void Load6()
		{
			LevelInfo::level_selected = 6;
			LevelButtonsFunc();
		}
	};


}
