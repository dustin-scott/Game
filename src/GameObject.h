/*
 * GameObject.h
 *
 *  Created on: Dec 23, 2012
 *      Author: dustin
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include "GameTypes.h"
#include "Math/GLTransformationMatrix.h"
namespace game {
class GameObject {
private:
	game_float width;
	game_float height;
	game_float depth;
public:
	GLTransformationMatrix coordinate_system;

	void set_width(game_float width);
	void set_height(game_float height);
	void set_depth(game_float depth);

	game_float get_width();
	game_float get_height();
	game_float get_depth();

	GameObject(game_float x, game_float y, game_float z, game_float width, game_float height,
			game_float depth, game_float rotx, game_float roty, game_float rotz);
	GameObject();
	virtual ~GameObject();
};
}
#endif /* GAMEOBJECT_H_ */
