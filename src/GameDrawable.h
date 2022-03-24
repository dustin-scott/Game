#ifndef GAMEDRAWABLE_H_
#define GAMEDRAWABLE_H_
#include "GameObject.h"
#include "GameTypes.h"

namespace game {

class GameDrawable: public GameObject {
private:
	game_float color[3];
public:
	virtual void draw(void) = 0;
	void set_color(game_float r, game_float g, game_float b);
	game_float* get_color();

	GameDrawable(game_float x, game_float y, game_float z, game_float width, game_float height, game_float depth, game_float rotx, game_float roty, game_float rotz);
	GameDrawable();
	virtual ~GameDrawable();
};

} /* namespace game */
#endif /* GLDRAWABLE_H_ */
