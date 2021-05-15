/*
 * GameObject.cpp
 *
 *  Created on: Dec 23, 2012
 *      Author: dustin
 */

#include "GameObject.h"
namespace game
{
	GameObject::GameObject(GLfloat x, GLfloat y, GLfloat z, GLfloat width,
			GLfloat height, GLfloat depth, GLfloat rotx, GLfloat roty,
			GLfloat rotz)
	{
		this->coordinate_system.translate(x,y,z);
		this->coordinate_system.rotate(rotz,roty, rotx);
		this->width = width;
		this->height = height;
		this->depth = depth;
	}

	void GameObject::set_width(game_float width)
	{
		this->width = width;
	}

	void GameObject::set_height(game_float height)
	{
		this->height = height;
	}

	void GameObject::set_depth(game_float depth)
	{
		this->depth = depth;
	}

	game_float GameObject::get_width()
	{
		return this->width;
	}

	game_float GameObject::get_height()
	{
		return this->height;
	}

	game_float GameObject::get_depth()
	{
		return this->depth;
	}

	GameObject::GameObject()
	{
		this->width = 0.0f;
		this->height = 0.0f;
		this->depth = 0.0f;
	}

	GameObject::~GameObject()
	{
		// TODO Auto-generated destructor stub
	}
}
