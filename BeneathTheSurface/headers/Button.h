#pragma once
#include "Core.h"
namespace BenTheSur
{


	class Button
	{
	public:
		Rectangle dest = {0,0,0,0};
		Texture2D& texture;
		std::function<void()> action;
		Button(int x,int y,int width,int height,Texture2D& texture,std::function<void()> action);
		void Render();
		void OnClick();
		void OnHover();
		bool IsHover();
		void Update();

	};

}

