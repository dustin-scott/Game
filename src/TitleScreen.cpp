#include "TitleScreen.h"
#include "stdio.h"
#include "Quad.h"
#include "Cuboid.h"
namespace game
{
	GameDrawable* moving_cube;
	TitleScreen::TitleScreen() :
			GameScreen()
	{
		//game::GLDrawable* drawable1 = new game::GLDrawable("Images/title_screen.bmp");
		game::Quad* drawable2 = new game::Quad(-0.5, 0.0, -2.0f, 0.0f, 0.0f, 0.0f, 0.0f,0.0f,0.0f);

		int argc = 0;
		const char* argv = "";
		this->audio = new GameAudio(argc,(char**)&argv);

		//this->drawable_list.push_front(drawable1);
		drawable2->set_color(1.0f, 0.0f, 0.0f);
		this->drawable_list.push_front(drawable2);

		int i = 0;
		int j = 0;

		for(i = 0; i < 256; i++)
		{
			this->keys[i] = 0;
			this->specials[i] = 0;
		}

		for(i = 0; i < 20; i++)
		{
			for(j = 0; j < 20; j++)
			{
				game::Quad* temp2 = new game::Quad(i,-1.0,j,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f);
				temp2->set_color(0.0f,0.0f,1.0f);
				this->drawable_list.push_front(temp2);
			}
		}

		game::Cuboid* temp = new game::Cuboid(5.0f, -1.0f, 25.0f, 2.0f, 5.0f, 2.0f, 0.0f, 0.0f, 0.0f);
		temp->set_color(0.0f, 1.0f, 0.0f);

		this->drawable_list.push_front(temp);
		moving_cube = temp;
	}

	int direction = 1;
	game_float speed = 0.05f;
	void TitleScreen::tick(void)
	{
		if(direction > 0 && (moving_cube->coordinate_system.get_element(0,3) - direction*20.0f >= 0.0001f))
		{
			direction *= -1;
		}
		else if (direction < 0 && (moving_cube->coordinate_system.get_element(0,3) <= 0.0001f))
		{
			direction *= -1;
		}
		moving_cube->coordinate_system.translate(direction*speed,0.0f,0.0f);
	}

	void TitleScreen::key_up(unsigned char key, int x, int y)
	{
		this->keys[key] = 0;
	}

	void TitleScreen::key_down(unsigned char key, int x, int y)
	{
		this->keys[key] = 1;
		if(this->keys['p'])
		{
			if(this->audio->isPlaying())
			{
				this->audio->pause();
			}
			else
			{
				printf("play");
				this->audio->play();
			}
		}
		if(this->keys['P'])
		{
			if(this->audio->isPlaying())
			{
				this->audio->stop();
			}
			else
			{
				this->audio->play();
			}
		}
	}

	void TitleScreen::special_key_down(int key, int x, int y)
	{
		this->specials[key] = 1;
	}
	void TitleScreen::special_key_up(int key, int x, int y)
	{
		this->specials[key] = 0;
	}
	void TitleScreen::process_keys()
	{
		GameObject* camera = this->camera;
		GLfloat speed = .05;

		//GLDrawable* drawable = this->drawable_list.front();
		if (this->keys['a'] || this->keys['A'])
		{
			camera->coordinate_system.translate(-speed, 0, 0);
		}
		if (this->keys['d'] || this->keys['D'])
		{
			camera->coordinate_system.translate(speed, 0 , 0);
		}
		if (this->keys['w'] || this->keys['W'])
		{
			camera->coordinate_system.translate(0, 0, -speed);
		}
		if (this->keys['s'] || this->keys['S'])
		{
			camera->coordinate_system.translate(0,0, speed);
		}
		if(this->specials[GLUT_KEY_UP])
		{
			camera->coordinate_system.rotate_x(speed);
		}
		if(this->specials[GLUT_KEY_DOWN])
		{
			camera->coordinate_system.rotate_x(-speed);
		}
		if(this->specials[GLUT_KEY_LEFT])
		{
			camera->coordinate_system.rotate_y(-speed);
		}
		if(this->specials[GLUT_KEY_RIGHT])
		{
			camera->coordinate_system.rotate_y(speed);
		}
	}
	TitleScreen::~TitleScreen()
	{
		delete this->audio;
	}

} /* namespace game */
