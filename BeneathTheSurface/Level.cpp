#include "headers/Level.h"

using Lvl = BenTheSur::LevelInfo;

int Lvl::level_selected = 1;
int Lvl::max_level_unlocked = 6;


void Lvl::WriteLevelData()
{
	std::ofstream file("data/leveldata.txt");

	if (!file) {
		return;
	}

	file << max_level_unlocked; 
	file.close();
}

void Lvl::LoadLevelData()
{
	std::ifstream file("data/leveldata.txt");

	if (!file)
	{
		max_level_unlocked = 1;
		return;
	}

	std::string content;
	std::getline(file, content);
	file.close();
	int num;

	std::istringstream t(content);

	if (!(t >> num)) {
		max_level_unlocked = 1;
		return;
	}

	if (num >= 1 && num <= 6)
	{
		max_level_unlocked = num;
	}
	else
	{
		max_level_unlocked = 1;
	}

}

void Lvl::LevelFinished()
{
	if (level_selected == max_level_unlocked && max_level_unlocked<6)
	{
		max_level_unlocked++;
	}
}


void Lvl::TutorialTextsRender()
{
	if (StateWrapper::GetState() == playing)
	{
		if (level_selected == 1)
		{
			DrawTextPro(Textures::daydream, "press a,d to move, space to jump,p to pause", { 30,100 }, { 0,0 }, 0.0f, 40.0f, 2.0f, ORANGE);
			DrawTextPro(Textures::daydream, "collect the gold", { 400,200 }, { 0,0 }, 0.0f, 40.0f, 2.0f, ORANGE);
		}
		else if (level_selected == 2)
		{
			DrawTextPro(Textures::daydream, "collect a shovel to break dirt", { 200,100 }, { 0,0 }, 0.0f, 40.0f, 2.0f, ORANGE);
		}
		else if (level_selected == 3)
		{
			DrawTextPro(Textures::daydream, "different things break different blocks", { 50,100 }, { 0,0 }, 0.0f, 40.0f, 2.0f, ORANGE);
		}
	}
}
