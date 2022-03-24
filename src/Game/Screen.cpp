#include "Game/Screen.h"

namespace game
{
	Screen::Screen()
	{
		this->camera = new game::GameObject();
	}
	Screen::~Screen()
	{
		delete this->camera;
		while(!this->drawable_list.empty())
		{
			delete this->drawable_list.front();
			this->drawable_list.pop_front();
		}
	}

} /* namespace game */
