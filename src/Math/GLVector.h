#ifndef GLVECTOR_H_
#define GLVECTOR_H_

#include "GLMatrix.h"

namespace game
{
	
	class GLVector: public game::GLMatrix
	{
		public:
			GLfloat get_x();
			GLfloat get_y();
			GLfloat get_z();
			void set_x(GLfloat x);
			void set_y(GLfloat y);
			void set_z(GLfloat z);
			GLVector* cross(GLVector* b);
			GLVector();
			virtual ~GLVector();
	};

} /* namespace game */
#endif /* GLVECTOR_H_ */
