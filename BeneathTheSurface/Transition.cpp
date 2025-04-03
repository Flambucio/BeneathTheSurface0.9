#include "headers/Transition.h"

using Tr = BenTheSur::Transition;

bool Tr::is_transitioning = false;
bool Tr::fading_out = false;
int Tr::alpha = 0;

void Tr::StartTransition()
{
	is_transitioning = true;
	fading_out = true;
}

void Tr::Update()
{
	if (is_transitioning)
	{
		DrawRectangle(0, 0, WIDTH, WIDTH, { 0,0,0,(unsigned char)alpha });
		if (fading_out)
		{
			alpha += 50;
			if (alpha >= 255)
			{
				fading_out = false;
				alpha = 255;
			}
		}
		else
		{
			alpha -= 50;
			if (alpha <= 0)
			{
				is_transitioning = false;
				alpha = 0;
			}
		}
	}
}