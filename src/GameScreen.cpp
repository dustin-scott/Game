/*
 * GameScreen.cpp
 *
 *  Created on: Dec 9, 2012
 *      Author: Dustin Scott
 */

#include "GameScreen.h"

namespace game
{
	GameScreen::GameScreen()
	{
		this->camera = new game::GameObject();
	}
	GameScreen::~GameScreen()
	{
		delete this->camera;
		while(!this->drawable_list.empty())
		{
			delete this->drawable_list.front();
			this->drawable_list.pop_front();
		}
	}

} /* namespace game */
