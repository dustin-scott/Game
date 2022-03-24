#include "GameWindow.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
namespace game
{
	int GameWindow::glut_window;
	/* ASCII code for the escape key. */
	#define ESCAPE 27

	/* rotation angle for the triangle. */
	float rtri = 0.0f;

	/* rotation angle for the quadrilateral. */
	float rquad = 0.0f;
// nehe example above

	char* GameWindow::title;
	Screen* screen = 0;
	char title_buffer[255];
	int frame = 0, time, timebase = 0;
//-----------------------------------------------------------------------------
// Name: glEnable2D
// Desc: Enabled 2D primitive rendering by setting up the appropriate orthographic
//               perspectives and matrices.
//-----------------------------------------------------------------------------
	/*
	void glEnable2D(void)
	{
		GLint iViewport[4];

		// Get a copy of the viewport
		glGetIntegerv(GL_VIEWPORT, iViewport);

		// Save a copy of the projection matrix so that we can restore it
		// when it's time to do 3D rendering again.
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		// Set up the orthographic projection
		glOrtho(iViewport[0], iViewport[0] + iViewport[2], iViewport[1] + iViewport[3], iViewport[1], -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		// Make sure depth testing and lighting are disabled for 2D rendering until
		// we are finished rendering in 2D
		glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
	}
*/
//-----------------------------------------------------------------------------
// Name: glDisable2D
// Desc: Disables 2D rendering and restores the previous matrix and render states
//               before they were modified.
//-----------------------------------------------------------------------------
	/*
	void glDisable2D(void)
	{
		glPopAttrib();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}
*/
	void GameWindow::reshape(int width, int height)
	{
		/*
		glViewport(0, 0, (GLsizei) width, (GLsizei) height); // Set our viewport to the size of our window
		glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
		glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
		gluPerspective(60, (GLfloat) width / (GLfloat) height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes
		glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly*/
		if (height==0)
		{
			height=1;
		}

		glViewport(0, 0, width, height);		// Reset The Current Viewport And Perspective Transformation

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
		glMatrixMode(GL_MODELVIEW);
	}

	void GameWindow::keyboard_down(unsigned char key, int x, int y)
	{
	    /* avoid thrashing this call */
		usleep(100);

		/* If escape is pressed, kill everything. */
		if (key == ESCAPE)
		{
			/* shut down our window */
			glutDestroyWindow(GameWindow::glut_window);
		}

		screen->key_down(key,x,y);
	}

	void GameWindow::keyboard_up(unsigned char key, int x, int y)
	{
		/* avoid thrashing this procedure */
		usleep(100);
		screen->key_up(key,x,y);
	}

	void process_keys()
	{
		screen->process_keys();
	}
	void load_textures(void)
	{

		GLuint* textures = new GLuint[screen->drawable_list.size()];
		glEnable(GL_TEXTURE_2D);
		/*
		 glGenTextures( 1, &g_textureID );
		 glBindTexture( GL_TEXTURE_2D, g_textureID );

		 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		 glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

		 glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height,
		 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data );
		 //glTexImage2D( GL_TEXTURE_RECTANGLE_NV, 0, GL_RGBA, pTexture_RGB->sizeX, pTexture_RGB->sizeY,
		 //                          0, GL_RGBA, GL_UNSIGNED_BYTE, pTexture_RGBA );
		 printf("Height: %i, Width: %i\n",image.height, image.width);*/

		//TODO: this && bitmap loader may not support alpha, will need to fix
		glGenTextures(screen->drawable_list.size(), textures);

		GameDrawable* current;
		int i = 0;

		for (std::list<GameDrawable*>::iterator it = screen->drawable_list.begin();
		        it != screen->drawable_list.end(); it++)
		{
			current = (*it);
			GLBitmap image;
			//image.loadBMP(current->image_path);
			//printf("image_path: %s\n", current->image_path);
			if (current->get_width() == 0 || current->get_height() == 0)
			{
				current->set_width(image.width);
				current->set_width(image.height);
			}
			glBindTexture(GL_TEXTURE_2D, textures[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, 3, image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.data);
			//glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data );
			//current->texture_id = textures[i];
			i++;
		}
	}

	void init(int width, int height)
	{/*
		// Disable lighting
		glDisable(GL_LIGHTING);

		// Disable dithering
		glDisable(GL_DITHER);

		// Disable blending (for now)
		glDisable(GL_BLEND);

		// Disable depth testing
		glDisable(GL_DEPTH_TEST);
		load_textures();*/
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
		glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
		glDepthFunc(GL_LESS);			        // The Type Of Depth Test To Do
		glEnable(GL_DEPTH_TEST);		        // Enables Depth Testing
		glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();				// Reset The Projection Matrix

		gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window

		glMatrixMode(GL_MODELVIEW);
		//glEnable(GL_LIGHTING);
//random lighting code to be figured out later		
//GLfloat light_position[] = {5.0f,5.0f,5.0f};
	//	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	//	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		//glEnable(GL_LIGHTING);
		//glEnable(GL_LIGHT0);
		//glEnable(GL_DEPTH_TEST);
	}

	void apply_camera(GameObject* camera)
	{
		GLTransformationMatrix* inverse_camera = camera->coordinate_system.inverse();
		glLoadMatrixf(inverse_camera->data);
		delete inverse_camera;
		/*
		gluLookAt(camera->x, camera->y, camera->z,
				camera->x+camera->posx, camera->y+camera->posy,  camera->z+camera->posz,
				0.0, 1.0, 0.0);*/
/*
		//lighting code ripped from elsewhere
		float lightv[4]; // populated with (0.6, 0.6, 0.6, 1)
		float positionv[4]; // populated with (0, 10, 0, 1)
		int lightID = GL_LIGHT0;
		int attenuationType = GL_LINEAR_ATTENUATION;
		float attenuationValue = 1;
		glLightf(lightID, attenuationType, attenuationValue);
		glLightfv(lightID, GL_DIFFUSE, lightv);
		glLightfv(lightID, GL_POSITION, positionv);
		glEnable(lightID);*/
	}

	void draw_object(GameDrawable* drawable)
	{
		glPushMatrix();
		//draw everything with respect to the camera
		//GameObject* camera = screen->camera;
		//apply_camera(camera);

		drawable->draw();
		glPopMatrix();
	}

	void GameWindow::idle()
	{
		time = glutGet(GLUT_ELAPSED_TIME);
		//int conversion = 1000/60;
		if (time - timebase > 1000)
		{
			sprintf(title_buffer, "%s (FPS:%4.2f)", GameWindow::title, (double) (frame * 1000.0 / (time - timebase)));
			timebase = time;
			frame = 0;
			glutSetWindowTitle(title_buffer);
		}
		if ((time - timebase) >= (1000 / 60) * frame)
		{
			frame++;
			glutPostRedisplay();
		}
	}

	void GameWindow::draw()
	{
		process_keys();
		screen->tick();
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);	// Clear The Screen And The Depth Buffer

		//apply camera rotation / remove old matrix from stack
		GameObject* camera = screen->camera;
		apply_camera(camera);

		std::for_each(screen->drawable_list.rbegin(), screen->drawable_list.rend(), draw_object);

		glTranslatef(1.5f,0.0f,-7.0f);		// Move Right 3 Units, and back into the screen 7

		//glRotatef(rquad,1.0f,1.0f,1.0f);		// Rotate The Cube On X, Y, and Z

		// draw a cube (6 quadrilaterals)
		glBegin(GL_QUADS);				// start drawing the cube.

		// top of cube
		glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Blue
		glVertex3f( 1.0f, 1.0f,-1.0f);		// Top Right Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f,-1.0f);		// Top Left Of The Quad (Top)
		glVertex3f(-1.0f, 1.0f, 1.0f);		// Bottom Left Of The Quad (Top)
		glVertex3f( 1.0f, 1.0f, 1.0f);		// Bottom Right Of The Quad (Top)

		// bottom of cube
		glColor3f(1.0f,0.5f,0.0f);			// Set The Color To Orange
		glVertex3f( 1.0f,-1.0f, 1.0f);		// Top Right Of The Quad (Bottom)
		glVertex3f(-1.0f,-1.0f, 1.0f);		// Top Left Of The Quad (Bottom)
		glVertex3f(-1.0f,-1.0f,-1.0f);		// Bottom Left Of The Quad (Bottom)
		glVertex3f( 1.0f,-1.0f,-1.0f);		// Bottom Right Of The Quad (Bottom)

		// front of cube
		glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Red
		glVertex3f( 1.0f, 1.0f, 1.0f);		// Top Right Of The Quad (Front)
		glVertex3f(-1.0f, 1.0f, 1.0f);		// Top Left Of The Quad (Front)
		glVertex3f(-1.0f,-1.0f, 1.0f);		// Bottom Left Of The Quad (Front)
		glVertex3f( 1.0f,-1.0f, 1.0f);		// Bottom Right Of The Quad (Front)

		// back of cube.
		glColor3f(1.0f,1.0f,0.0f);			// Set The Color To Yellow
		glVertex3f( 1.0f,-1.0f,-1.0f);		// Top Right Of The Quad (Back)
		glVertex3f(-1.0f,-1.0f,-1.0f);		// Top Left Of The Quad (Back)
		glVertex3f(-1.0f, 1.0f,-1.0f);		// Bottom Left Of The Quad (Back)
		glVertex3f( 1.0f, 1.0f,-1.0f);		// Bottom Right Of The Quad (Back)

		// left of cube
		glColor3f(0.0f,0.0f,1.0f);			// Blue
		glVertex3f(-1.0f, 1.0f, 1.0f);		// Top Right Of The Quad (Left)
		glVertex3f(-1.0f, 1.0f,-1.0f);		// Top Left Of The Quad (Left)
		glVertex3f(-1.0f,-1.0f,-1.0f);		// Bottom Left Of The Quad (Left)
		glVertex3f(-1.0f,-1.0f, 1.0f);		// Bottom Right Of The Quad (Left)

		// Right of cube
		glColor3f(1.0f,0.0f,1.0f);			// Set The Color To Violet
		glVertex3f( 1.0f, 1.0f,-1.0f);	        // Top Right Of The Quad (Right)
		glVertex3f( 1.0f, 1.0f, 1.0f);		// Top Left Of The Quad (Right)
		glVertex3f( 1.0f,-1.0f, 1.0f);		// Bottom Left Of The Quad (Right)
		glVertex3f( 1.0f,-1.0f,-1.0f);		// Bottom Right Of The Quad (Right)
		glEnd();					// Done Drawing The Cube

		rtri+=15.0f;					// Increase The Rotation Variable For The Pyramid
		rquad-=15.0f;					// Decrease The Rotation Variable For The Cube

		// swap the buffers to display, since double buffering is used.
		glutSwapBuffers();
	}

	GameWindow::GameWindow(int argc, char** argv)
	{
		glutInit(&argc, argv);
		char default_title[] = "The title";
		GameWindow::title = &default_title[0];
		this->height = 500;
		this->width = 500;
		GameWindow::glut_window = 0;
		glEnable(GL_TEXTURE_2D);
		 //  ----- Initialise DevIL -----
		ilutRenderer(ILUT_OPENGL);
		ilInit();
		iluInit();
		ilutInit();
		ilutRenderer(ILUT_OPENGL);
	}
	void GameWindow::set_title(const char* title)
	{
		GameWindow::title = (char*)title;
	}

	void GameWindow::set_screen(Screen* assign_screen)
	{
		screen = assign_screen;
	}

	char* GameWindow::get_title()
	{
		return GameWindow::title;
	}
	void GameWindow::main_loop()
	{
		glutMainLoop();
	}
	void GameWindow::open()
	{

		int screen_width = glutGet(GLUT_SCREEN_WIDTH);
		int screen_height = glutGet(GLUT_SCREEN_HEIGHT);

		int position_x = (screen_width - this->width) / 2;
		int position_y = (screen_height - this->height) / 2;
		/*
		unsigned int displayMode = GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL | GLUT_RGBA;

		glutInitDisplayMode(displayMode);
		//glutInitContextVersion (3, 3);
		//glutInitContextProfile(GLUT_CORE_PROFILE);

		glutInitWindowSize(this->width, this->height);
		glutInitWindowPosition(position_x, position_y);

		this->glut_window = glutCreateWindow(this->title);

		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

		init();

		glutDisplayFunc(this->draw);
		glutIdleFunc(this->idle);

		glutReshapeFunc(this->reshape);
		glutKeyboardFunc(this->keyboard_down);
		glutKeyboardUpFunc(this->keyboard_up);*/

		 /* Initialize GLUT state - glut will take any command line arguments that pertain to it or
		     X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */
		 // glutInit(&argc, argv);

		  /* Select type of Display mode:
		     Double buffer
		     RGBA color
		     Alpha components supported
		     Depth buffered for automatic clipping */
		unsigned int displayMode = GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL | GLUT_RGBA;

		glutInitDisplayMode(displayMode);

		glutInitWindowSize(this->width, this->height);

		glutInitWindowPosition(position_x, position_y);

		GameWindow::glut_window = glutCreateWindow(this->title);
		GLenum err = glewInit();

		if (GLEW_OK != err)
		{
		  /* Problem: glewInit failed, something is seriously wrong. */
		  fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		}
		fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

		glutDisplayFunc(this->draw);
		glutIdleFunc(this->idle);
		/* Register the function called when our window is resized. */
		glutReshapeFunc(this->reshape);

		/* Register the function called when the keyboard is pressed. */
		glutKeyboardFunc(this->keyboard_down);
		glutKeyboardUpFunc(this->keyboard_up);

		glutSpecialFunc(this->keyboard_specials_down);

		glutSpecialUpFunc(this->keyboard_specials_up);
	    glutIgnoreKeyRepeat(true);

		init(this->width, this->height);
	}
	void GameWindow::keyboard_specials_down(int key, int x, int y)
	{
		screen->special_key_down(key,x,y);
	}
	void GameWindow::keyboard_specials_up(int key, int x, int y)
	{
		screen->special_key_up(key,x,y);
	}
	void GameWindow::close()
	{
		glutDestroyWindow(GameWindow::glut_window);
	}
	GameWindow::~GameWindow()
	{
		//glutLeaveMainLoop();
	}

} /* namespace game */

