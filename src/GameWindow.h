#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_
#include "Game/Types.h"
#include <stdio.h>
#include <algorithm>
#include <unistd.h>

#include <list>
#include "GLBitmap.h"
#include "GameDrawable.h"
#include "Game/Screen.h"
namespace game
{

class GameWindow
{
private:
	static int glut_window;
	static char* title;
	//static Screen* screen;
	static void draw(void);
	static void idle(void);
	static void reshape(int width, int height);
	static void keyboard_down(unsigned char key, int x, int y);
	static void keyboard_up(unsigned char key, int x, int y);
	static void keyboard_specials_down(int key, int x, int y);
	static void keyboard_specials_up(int key, int x, int y);
public:
	int width;
	int height;
	void open(void);
	void close(void);
	void main_loop(void);
	void set_title(const char* title);
	void set_screen(Screen* screen);
	char* get_title();
	GameWindow(int argc, char** argv);
	virtual ~GameWindow();
};

} /* namespace game */
#endif /* GAMEWINDOW_H_ */
