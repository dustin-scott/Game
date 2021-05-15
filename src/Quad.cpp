/*
 * Quad.cpp
 *
 *  Created on: Jan 12, 2013
 *      Author: Dustin Scott
 */

#include "Quad.h"
#include "GL/gl.h"
namespace game
{
	Quad::Quad(game_float x, game_float y, game_float z, game_float width, game_float height, game_float depth, game_float rotx, game_float roty, game_float rotz):GameDrawable(x, y, z, width, height, depth, rotx, roty, rotz)
	{
		this->vertex_count = 4;

		this->vertex_data[0][0] = 0.0f;
		this->vertex_data[0][1] = 0.0f;
		this->vertex_data[0][2] = 0.0f;

		this->vertex_data[1][0] = 0.0f;
		this->vertex_data[1][1] = this->get_height();
		this->vertex_data[1][2] = 0.0f;

		this->vertex_data[2][0] = this->get_width();
		this->vertex_data[2][1] = this->get_height();
		this->vertex_data[2][2] = 0.0f;

		this->vertex_data[3][0] = this->get_width();
		this->vertex_data[3][1] =  0.0f;
		this->vertex_data[3][2] = 0.0f;

		this->image_path = 0;
		this->texture_id = 0;
	}

	Quad::Quad():GameDrawable()
	{
		//this->vertex_data = 0;
		this->vertex_count = 0;
		this->set_color(0.0f, 0.0f, 0.0f);

		this->image_path = 0;
		this->texture_id = 0;
	}
	void Quad::set_texture_path(const char* image_path)
	{
		this->image_path = (game_char*)image_path;
	}

	void Quad::draw(void)
	{
		glMultMatrixf(this->coordinate_system.data);

		int i = 0;

		glBegin(GL_QUADS);
		glColor3fv(this->get_color());
		for(i = 0; i < this->vertex_count; i++)
		{
			glVertex3fv(this->vertex_data[i]);
		}
		glEnd();
	}
	Quad::~Quad()
	{

	}

} /* namespace game */
