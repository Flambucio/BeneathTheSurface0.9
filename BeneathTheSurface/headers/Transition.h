#pragma once
#include "Core.h"
namespace BenTheSur
{


	static class Transition
	{
	public:
		static bool is_transitioning;
		static bool fading_out;
		static int alpha;
		static void StartTransition();
		static void Update();
	};

}
