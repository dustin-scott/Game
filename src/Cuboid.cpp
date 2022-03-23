/*
 * Cuboid.cpp
 *
 *  Created on: May 5, 2013
 *      Author: Dustin Scott
 */

#include "Cuboid.h"

namespace game
{
	Cuboid::Cuboid(game_float x, game_float y, game_float z, game_float width, game_float height, game_float depth, game_float rotx, game_float roty, game_float rotz):GameDrawable(x, y, z, width, height, depth, rotx, roty, rotz)
	{
		this->vertex_count = 4*6;

		this->vertex_data[0][0] = this->get_width(); this->vertex_data[0][1]= this->get_height(); this->vertex_data[0][2] = 0.0f;		// Top Right Of The Quad (Top)
		this->vertex_data[1][0] = 0.0f; this->vertex_data[1][1] = this->get_height(); this->vertex_data[1][2] = 0.0f;		// Top Left Of The Quad (Top)
		this->vertex_data[2][0] = 0.0f; this->vertex_data[2][1] = this->get_height(); this->vertex_data[2][2] = this->get_depth();		// Bottom Left Of The Quad (Top)
		this->vertex_data[3][0] = this->get_width(); this->vertex_data[3][1] = this->get_height(); this->vertex_data[3][2] = this->get_depth();		// Bottom Right Of The Quad (Top)

		// bottom of cube
		this->vertex_data[4][0] = this->get_width(); this->vertex_data[4][1] = 0.0f; this->vertex_data[4][2] = this->get_depth();		// Top Right Of The Quad (Bottom)
		this->vertex_data[5][0] = 0.0f; this->vertex_data[5][1] = 0.0f; this->vertex_data[5][2] = this->get_depth();		// Top Left Of The Quad (Bottom)
		this->vertex_data[6][0] = 0.0f; this->vertex_data[6][1] = 0.0f; this->vertex_data[6][2] = 0.0f;		// Bottom Left Of The Quad (Bottom)
		this->vertex_data[7][0] = this->get_width(); this->vertex_data[7][1] = 0.0f; this->vertex_data[7][2] = 0.0f;		// Bottom Right Of The Quad (Bottom)

		// front of cube
		this->vertex_data[8][0] = this->get_width(); this->vertex_data[8][1] = this->get_height(); this->vertex_data[8][2] = this->get_depth();		// Top Right Of The Quad (Front)
		this->vertex_data[9][0] = 0.0f; this->vertex_data[9][1] = this->get_height(); this->vertex_data[9][2] = this->get_depth();		// Top Left Of The Quad (Front)
		this->vertex_data[10][0] = 0.0f; this->vertex_data[10][1] = 0.0f; this->vertex_data[10][2] = this->get_depth();		// Bottom Left Of The Quad (Front)
		this->vertex_data[11][0] = this->get_width(); this->vertex_data[11][1] = 0.0f; this->vertex_data[11][2] = this->get_depth();		// Bottom Right Of The Quad (Front)

		// back of cube.
		this->vertex_data[12][0] = this->get_width(); this->vertex_data[12][1] = 0.0f; this->vertex_data[12][2] = 0.0f;		// Top Right Of The Quad (Back)
		this->vertex_data[13][0] = 0.0f; this->vertex_data[13][1] = 0.0f; this->vertex_data[13][2] = 0.0f;		// Top Left Of The Quad (Back)
		this->vertex_data[14][0] = 0.0f; this->vertex_data[14][1] = this->get_height(); this->vertex_data[14][2] = 0.0f;		// Bottom Left Of The Quad (Back)
		this->vertex_data[15][0] = this->get_width(); this->vertex_data[15][1] = this->get_height(); this->vertex_data[15][2] = 0.0f;		// Bottom Right Of The Quad (Back)

		// left of cube
		this->vertex_data[16][0] = 0.0f; this->vertex_data[16][1] = this->get_height(); this->vertex_data[16][2] = this->get_depth();		// Top Right Of The Quad (Left)
		this->vertex_data[17][0] = 0.0f; this->vertex_data[17][1] = this->get_height(); this->vertex_data[17][2] = 0.0f;		// Top Left Of The Quad (Left)
		this->vertex_data[18][0] = 0.0f; this->vertex_data[18][1] = 0.0f; this->vertex_data[18][2] = 0.0f;		// Bottom Left Of The Quad (Left)
		this->vertex_data[19][0] = 0.0f; this->vertex_data[19][1] = 0.0f; this->vertex_data[19][2] = this->get_depth();		// Bottom Right Of The Quad (Left)

		// Right of cube
		this->vertex_data[20][0] = this->get_width(); this->vertex_data[20][1] = this->get_height(); this->vertex_data[20][2] = 0.0f;	        // Top Right Of The Quad (Right)
		this->vertex_data[21][0] = this->get_width(); this->vertex_data[21][1] = this->get_height(); this->vertex_data[21][2] = this->get_depth();		// Top Left Of The Quad (Right)
		this->vertex_data[22][0] = this->get_width(); this->vertex_data[22][1] = 0.0f; this->vertex_data[22][2] = this->get_depth();		// Bottom Left Of The Quad (Right)
		this->vertex_data[23][0] = this->get_width(); this->vertex_data[23][1] = 0.0f; this->vertex_data[23][2] = 0.0f;		// Bottom Right Of The Quad (Right)
	}

	void Cuboid::draw(void)
	{
		glMultMatrixf(this->coordinate_system.data);

		int i = 0;

		glBegin(GL_QUADS);
		glColor3fv((float*)this->get_color());
		for(i = 0; i < this->vertex_count; i++)
		{
			glVertex3fv(this->vertex_data[i]);
		}
		glEnd();
	}

	Cuboid::~Cuboid()
	{
		// TODO Auto-generated destructor stub
	}

} /* namespace game */
