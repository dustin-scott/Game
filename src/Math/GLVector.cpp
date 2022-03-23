/*
 * GLVector.cpp
 *
 *  Created on: Dec 29, 2012
 *      Author: Dustin Scott
 */

#include "GLVector.h"

namespace game
{
	
	GLVector::GLVector(): GLMatrix(3,1)
	{

	}
	GLfloat GLVector::get_x()
	{
		return this->get_element(0, 0);
	}
	GLfloat GLVector::get_y()
	{
		return this->get_element(0, 1);
	}
	GLfloat GLVector::get_z()
	{
		return this->get_element(0, 2);
	}
	void GLVector::set_x(GLfloat x)
	{
		this->set_element(0, 0, x);
	}
	void GLVector::set_y(GLfloat y)
	{
		this->set_element(0, 1, y);
	}
	void GLVector::set_z(GLfloat z)
	{
		this->set_element(0, 2, z);
	}
	GLVector* GLVector::cross(GLVector* b)
	{

	}
	GLVector::~GLVector()
	{
		// TODO Auto-generated destructor stub
	}

} /* namespace game */
