#pragma once
#include "Core.h"
#include "Textures.h"
namespace BenTheSur
{


	class Inventory
	{
	public:
		uint8_t pickaxe_count = 0;
		uint8_t shovel_count = 0;
		uint8_t drill_count = 0;
		void RenderHUD();
		void ResetInventory(); 


	};

}
