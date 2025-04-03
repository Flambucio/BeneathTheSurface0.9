#include "headers/Audio.h"


using Au = BenTheSur::Audio;

Sound Au::break_block = { 0 };
Sound Au::collect = { 0 };
Sound Au::die = { 0 };
Sound Au::jump = { 0 };

void Au::Initialize()
{
	InitAudioDevice();
	break_block = LoadSound("resources/break.ogg");
	collect = LoadSound("resources/collect.ogg");
	SetSoundVolume(collect, 0.1f);
	die = LoadSound("resources/hit.ogg");
	jump = LoadSound("resources/jump.ogg");
}

void Au::Disable()
{

	UnloadSound(break_block);
	UnloadSound(die);
	UnloadSound(collect);
	UnloadSound(jump);
}

void Au::PlayBreakSound()
{
	PlaySound(break_block);

}

void Au::PlayCollectSound()
{
	PlaySound(collect);
}

void Au::PlayDieSound()
{
	PlaySound(die);
}

void Au::PlayJumpSound()
{
	PlaySound(jump);
}