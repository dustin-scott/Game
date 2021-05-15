/*
 * Quad.h
 *
 *  Created on: Jan 12, 2013
 *      Author: Dustin Scott
 */

#ifndef QUAD_H_
#define QUAD_H_

#include "GameDrawable.h"

namespace game
{
	
	class Quad: public game::GameDrawable
	{
		private:
			game_float vertex_data[4][3];
			int vertex_count;
		public:
			game_char* image_path;
			game_unsigned_int texture_id;
			virtual void draw();
			void set_texture_path(const char* image_path);
			Quad(game_float x, game_float y, game_float z, game_float width, game_float height, game_float depth, game_float rotx, game_float roty, game_float rotz);
			Quad();
			virtual ~Quad();
	};

} /* namespace game */
#endif /* QUAD_H_ */
