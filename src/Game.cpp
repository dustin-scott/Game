//============================================================================
// Name        : Game.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "GameTypes.h"
#include <iostream>
#include "GameWindow.h"
#include "TitleScreen.h"
#include "Math/GLMatrix.h"
#include "Math/GLTransformationMatrix.h"
#include "Math/Math.h"
#include "Quad.h"
#include "ObjModel.h"
#include <AL/al.h>
#include <AL/alut.h>
#include <GL/gl.h>

using namespace std;
#include <unistd.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv)
{
	game::GameWindow window(argc, argv);
	window.set_title("My spiffy game title");
	window.width = 800;
	window.height = 600;


	game::GameAudio audio(argc, argv);

	window.open();

	game::TitleScreen title_screen;
	window.set_screen(&title_screen);

	std::cout   << "Use arrow keys to adjust camera" << std::endl
                << "Use WASD to move first person view" << std::endl
                << "Press p to start and stop music" << std::endl
                << "Press ESC to exit" << std::endl;
	window.main_loop();
	alutExit();

	return 0;
}



