/*
 * Cuboid.h
 *
 *  Created on: May 5, 2013
 *      Author: Dustin Scott
 */

#ifndef CUBOID_H_
#define CUBOID_H_

#include "GameDrawable.h"
#include "Quad.h"

namespace game
{
	
	class Cuboid: public game::GameDrawable
	{
		private:
			game_float vertex_data[6*4][3];
			int vertex_count;
		public:
			Cuboid(game_float x, game_float y, game_float z, game_float width, game_float height, game_float depth, game_float rotx, game_float roty, game_float rotz);
			virtual void draw();
			virtual ~Cuboid();
	};

} /* namespace game */
#endif /* CUBOID_H_ */
