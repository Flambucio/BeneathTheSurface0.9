#pragma once
namespace BenTheSur
{
	enum States{playing,inmenu,level_selection,pausing,losing,winning};

	static class StateWrapper
	{
	private:
		static States state;
	public:
		static States GetState();
		static void SetState(States state);
	};

}