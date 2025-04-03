#include "headers/Button.h"
#include "headers/Textures.h"

using Bu = BenTheSur::Button;

Bu::Button(int x, int y, int width, int height, Texture2D& texture, std::function<void()> action) : texture(texture)
{
	dest = { (float)x,(float)y,(float)width,(float)height };
	this->action = action;
}

void Bu::OnHover()
{
	if (IsHover())
	{
		DrawRectangleRec(dest, { 255,255,255,100 });
	}
}

bool Bu::IsHover()
{
	return CheckCollisionPointRec(GetMousePosition(), dest);
}

void Bu::OnClick()
{
	if (IsHover() && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
	{
		action();
	}
}

void Bu::Render()
{
	if (texture.id == 0)
	{
		PRINTLN("invalid texture");
		return;
	}
	Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
	Vector2 origin = { 0,0};
	DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
}

void Bu::Update()
{
	Render();
	OnHover();
	OnClick();
}


