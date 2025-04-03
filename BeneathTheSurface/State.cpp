#include "headers/State.h"

BenTheSur::States BenTheSur::StateWrapper::state = BenTheSur::inmenu;

BenTheSur::States BenTheSur::StateWrapper::GetState()
{
	return state;
}

void BenTheSur::StateWrapper::SetState(BenTheSur::States new_state)
{
	state = new_state;
}