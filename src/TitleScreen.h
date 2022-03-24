#ifndef TITLESCREEN_H_
#define TITLESCREEN_H_

#include "Game/Screen.h"
#include <GL/freeglut.h>
#include "Math/Math.h"
#include "ObjModel.h"
namespace game
{
	
	class TitleScreen: public game::Screen
	{
		private:
			bool keys[256];
			bool specials[256];
			GameAudio* audio;
		public:
			void key_up(unsigned char key, int x, int y);
			void key_down(unsigned char key, int x, int y);
			void process_keys(void);
			void special_key_down(int key, int x, int y);
			void special_key_up(int key, int x , int y);
			void tick(void);
			TitleScreen();
			virtual ~TitleScreen();
	};

} /* namespace game */
#endif /* TITLESCREEN_H_ */
