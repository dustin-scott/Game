/*
 * GLTransformationMatrix.h
 *
 *  Created on: Dec 29, 2012
 *      Author: Dustin Scott
 */

#ifndef GLTRANSFORMATIONMATRIX_H_
#define GLTRANSFORMATIONMATRIX_H_

#include "GLMatrix.h"
#include "Math.h"

namespace game
{
	class GLTransformationMatrix: public game::GLMatrix
	{
		public:
			void multiply(GLTransformationMatrix* b);
			void translate(GLMatrixNumber x, GLMatrixNumber y, GLMatrixNumber z);
			void rotate(GLMatrixNumber yaw, GLMatrixNumber pitch, GLMatrixNumber roll);
			void rotate_x(GLMatrixNumber angle);
			void rotate_y(GLMatrixNumber angle);
			void rotate_z(GLMatrixNumber angle);
			void load_identity();
			GLTransformationMatrix* inverse();
			GLTransformationMatrix();
			virtual ~GLTransformationMatrix();
	};

} /* namespace game */
#endif /* GLTRANSFORMATIONMATRIX_H_ */
