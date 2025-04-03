#pragma once
#include "Core.h"
namespace BenTheSur
{


	static class Audio
	{
		static Sound die;
		static Sound break_block;
		static Sound collect;
		static Sound jump;
	public:
		static void Initialize();
		static void Disable();
		static void PlayDieSound();
		static void PlayBreakSound();
		static void PlayJumpSound();
		static void PlayCollectSound();


	};

}
