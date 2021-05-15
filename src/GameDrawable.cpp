/*
 * GameDrawable.cpp
 *
 *  Created on: Dec 1, 2012
 *      Author: Dustin Scott
 */

#include "GameDrawable.h"

namespace game
{

GameDrawable::GameDrawable(game_float x, game_float y, game_float z, game_float width, game_float height, game_float depth, game_float rotx, game_float roty, game_float rotz):GameObject(x,y,z,width,height,depth, rotx,roty,rotz)
{

}
GameDrawable::GameDrawable():GameObject()
{

}

void GameDrawable::set_color(game_float r, game_float g, game_float b)
{
	this->color[0] = r;
	this->color[1] = g;
	this->color[2] = b;
}

game_float* GameDrawable::get_color()
{
	return this->color;
}

GameDrawable::~GameDrawable()
{

}

} /* namespace game */
