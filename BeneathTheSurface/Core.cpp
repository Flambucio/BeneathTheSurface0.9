#include "headers/Core.h"

using namespace BenTheSur;

std::chrono::high_resolution_clock::time_point DeltaTime::lastTime = std::chrono::high_resolution_clock::now();
double DeltaTime::deltaTime = 0.0;

void DeltaTime::Update()
{
    auto now = std::chrono::high_resolution_clock::now();
    deltaTime = std::chrono::duration<double>(now - lastTime).count();
    lastTime = now;
}

double DeltaTime::Get()
{
    return deltaTime;
}