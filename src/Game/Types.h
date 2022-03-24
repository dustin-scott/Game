#ifndef GAMETYPES_H_
#define GAMETYPES_H_
#define ILUT_USE_OPENGL
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
namespace game
{
	typedef long unsigned int game_unsigned_int;
	typedef GLfloat game_float;
	typedef GLboolean game_bool;
	typedef GLvoid game_void;
	typedef unsigned char game_char;
}
#endif /* GAMETYPES_H_ */
