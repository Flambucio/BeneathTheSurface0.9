#pragma once
#include "Button.h"
#include "State.h"
#include "Textures.h"
#include "Transition.h"
namespace BenTheSur {

	template<typename Main>
	class PauseMenu
	{
	public:
		Main& main;
		Button resume;
		Button menu;
		Button restart;
		PauseMenu(Main& main) : main(main), resume(WIDTH / 2 - 100, HEIGHT / 2 + 64, 200, 64, Textures::resume_texture,
			[this]() {this->ResumeFunc();}),
			menu(WIDTH / 2 - 100, HEIGHT / 2 - 32, 200, 64, Textures::menu_texture,
				[this]() {this->MenuFunc();}),
			restart(WIDTH / 2 - 100, HEIGHT / 2 - 128, 200, 64, Textures::restart_texture,
				[this]() {this->RestartFunc();})
		{}
		void Update()
		{
			if (StateWrapper::GetState() == pausing)
			{
				DrawTextPro(Textures::daydream, "Pause", { 420,100 }, { 0,0 }, 0.0f, 100, 5, ORANGE);
				DrawRectangle(0, 0, WIDTH, HEIGHT, { 0,0,0,100 });
				resume.Update();
				menu.Update();
				restart.Update();
			}
			else if (StateWrapper::GetState() == losing)
			{
				DrawTextPro(Textures::daydream, "You Died", { 350,100 }, { 0,0 }, 0.0f, 100, 5, RED);
				restart.Update();
				menu.Update();
			}
			else if (StateWrapper::GetState() == winning)
			{
				DrawTextPro(Textures::daydream, "level completed", { WIDTH / 4-70 ,HEIGHT / 2 - 100 }, { 0,0 }, 0.0f, 70.0f, 3.0f, GREEN);
				DrawTextPro(Textures::daydream, "press space to exit", { WIDTH / 4+40,HEIGHT / 2 }, { 0,0 }, 0.0f, 40.0f, 2.0f, GREEN);
				if (IsKeyPressed(KEY_SPACE))
				{
					Transition::StartTransition();
					StateWrapper::SetState(level_selection);
				}
			}
		}

		void RestartFunc()
		{

				main.world.Unload();
				main.world.Load();
				StateWrapper::SetState(playing);
			
		}

		void MenuFunc()
		{
			main.world.Unload();
			StateWrapper::SetState(inmenu);
			Transition::StartTransition();
		}

		void ResumeFunc()
		{
			StateWrapper::SetState(playing);
		}



	};

}

