/*
 * GameScreen.h
 *
 *  Created on: Dec 9, 2012
 *      Author: Dustin Scott
 *
 * @purpose generic object representing Screen specific logic. title_screen, loading_screen, etc.
 */

#ifndef GAMESCREEN_H_
#define GAMESCREEN_H_
#include <list>
#include "GameDrawable.h"
#include "GameAudio.h"
#include "GameObject.h"
namespace game
{
	
	class GameScreen
	{
		public:
			GameScreen();
			virtual void key_down(unsigned char key, int x, int y) = 0;
			virtual void key_up(unsigned char key, int x, int y) = 0;
			virtual void special_key_down(int key, int x, int y) = 0;
			virtual void special_key_up(int key, int x , int y) = 0;
			virtual void process_keys(void) = 0;
			virtual void tick(void) = 0;
			std::list<GameDrawable*> drawable_list;
			GameObject* camera;
			virtual ~GameScreen();
	};

} /* namespace game */
#endif /* GAMESCREEN_H_ */