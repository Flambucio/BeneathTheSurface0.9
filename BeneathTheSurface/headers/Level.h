#pragma once
#include "Button.h"
#include "State.h"
#include "Textures.h"
#include "Core.h"
namespace BenTheSur
{


	static class LevelInfo
	{
	public:
		static int level_selected;
		static int max_level_unlocked;
		static void LevelFinished();
		static void LoadLevelData();
		static void WriteLevelData();
		static void	TutorialTextsRender();
	};

}

