/*
 * GLTransformationMatrix.cpp
 *
 *  Created on: Dec 29, 2012
 *      Author: Dustin Scott
 */

#include "GLTransformationMatrix.h"

namespace game
{
	
	GLTransformationMatrix::GLTransformationMatrix():GLMatrix(4,4)
	{
		this->load_identity();
	}
	void GLTransformationMatrix::load_identity()
	{
		this->set_element(0,0, 1.0f);
		this->set_element(0,1, 0.0f);
		this->set_element(0,2, 0.0f);
		this->set_element(0,3, 0.0f);

		this->set_element(1,0, 0.0f);
		this->set_element(1,1, 1.0f);
		this->set_element(1,2, 0.0f);
		this->set_element(1,3, 0.0f);

		this->set_element(2,0, 0.0f);
		this->set_element(2,1, 0.0f);
		this->set_element(2,2, 1.0f);
		this->set_element(2,3, 0.0f);

		this->set_element(3,0, 0.0f);
		this->set_element(3,1, 0.0f);
		this->set_element(3,2, 0.0f);
		this->set_element(3,3, 1.0f);
	}
	GLTransformationMatrix* GLTransformationMatrix::inverse()
	{
		GLTransformationMatrix* return_matrix = new GLTransformationMatrix();
		int i = 0;
		int j = 0;
		for(i = 0; i < 3; i++)
		{
			for(j = 0; j < 3; j++)
			{
				return_matrix->set_element(i, j, this->get_element(j, i));
			}
		}

		GLMatrix translate(4,1);
		translate.set_element(0,0, -this->get_element(0,3));
		translate.set_element(1,0, -this->get_element(1,3));
		translate.set_element(2,0, -this->get_element(2,3));
		translate.set_element(3,0, 1.0f);


		GLMatrix* new_translate = ((GLMatrix*)return_matrix)->multiply(&translate);

		return_matrix->set_element(0,3, new_translate->get_element(0,0));
		return_matrix->set_element(1,3, new_translate->get_element(1,0));
		return_matrix->set_element(2,3, new_translate->get_element(2,0));
		return_matrix->set_element(3,3, new_translate->get_element(3,0));

		delete new_translate;

		return return_matrix;
	}
	void GLTransformationMatrix::multiply(GLTransformationMatrix* b)
	{
		GLTransformationMatrix a;
		a.copy((GLMatrix*)this);

		this->set_element(0,0, a.get_element(0,0)*b->get_element(0,0)+a.get_element(0,1)*b->get_element(1,0)+a.get_element(0,2)*b->get_element(2,0)+a.get_element(0,3)*b->get_element(3,0));
		this->set_element(0,1, a.get_element(0,0)*b->get_element(0,1)+a.get_element(0,1)*b->get_element(1,1)+a.get_element(0,2)*b->get_element(2,1)+a.get_element(0,3)*b->get_element(3,1));
		this->set_element(0,2, a.get_element(0,0)*b->get_element(0,2)+a.get_element(0,1)*b->get_element(1,2)+a.get_element(0,2)*b->get_element(2,2)+a.get_element(0,3)*b->get_element(3,2));
		this->set_element(0,3, a.get_element(0,0)*b->get_element(0,3)+a.get_element(0,1)*b->get_element(1,3)+a.get_element(0,2)*b->get_element(2,3)+a.get_element(0,3)*b->get_element(3,3));

		this->set_element(1,0, a.get_element(1,0)*b->get_element(0,0)+a.get_element(1,1)*b->get_element(1,0)+a.get_element(1,2)*b->get_element(2,0)+a.get_element(1,3)*b->get_element(3,0));
		this->set_element(1,1, a.get_element(1,0)*b->get_element(0,1)+a.get_element(1,1)*b->get_element(1,1)+a.get_element(1,2)*b->get_element(2,1)+a.get_element(1,3)*b->get_element(3,1));
		this->set_element(1,2, a.get_element(1,0)*b->get_element(0,2)+a.get_element(1,1)*b->get_element(1,2)+a.get_element(1,2)*b->get_element(2,2)+a.get_element(1,3)*b->get_element(3,2));
		this->set_element(1,3, a.get_element(1,0)*b->get_element(0,3)+a.get_element(1,1)*b->get_element(1,3)+a.get_element(1,2)*b->get_element(2,3)+a.get_element(1,3)*b->get_element(3,3));

		this->set_element(2,0, a.get_element(2,0)*b->get_element(0,0)+a.get_element(2,1)*b->get_element(1,0)+a.get_element(2,2)*b->get_element(2,0)+a.get_element(2,3)*b->get_element(3,0));
		this->set_element(2,1, a.get_element(2,0)*b->get_element(0,1)+a.get_element(2,1)*b->get_element(1,1)+a.get_element(2,2)*b->get_element(2,1)+a.get_element(2,3)*b->get_element(3,1));
		this->set_element(2,2, a.get_element(2,0)*b->get_element(0,2)+a.get_element(2,1)*b->get_element(1,2)+a.get_element(2,2)*b->get_element(2,2)+a.get_element(2,3)*b->get_element(3,2));
		this->set_element(2,3, a.get_element(2,0)*b->get_element(0,3)+a.get_element(2,1)*b->get_element(1,3)+a.get_element(2,2)*b->get_element(2,3)+a.get_element(2,3)*b->get_element(3,3));

		this->set_element(3,0, a.get_element(3,0)*b->get_element(0,0)+a.get_element(3,1)*b->get_element(1,0)+a.get_element(3,2)*b->get_element(2,0)+a.get_element(3,3)*b->get_element(3,0));
		this->set_element(3,1, a.get_element(3,0)*b->get_element(0,1)+a.get_element(3,1)*b->get_element(1,1)+a.get_element(3,2)*b->get_element(2,1)+a.get_element(3,3)*b->get_element(3,1));
		this->set_element(3,2, a.get_element(3,0)*b->get_element(0,2)+a.get_element(3,1)*b->get_element(1,2)+a.get_element(3,2)*b->get_element(2,2)+a.get_element(3,3)*b->get_element(3,2));
		this->set_element(3,3, a.get_element(3,0)*b->get_element(0,3)+a.get_element(3,1)*b->get_element(1,3)+a.get_element(3,2)*b->get_element(2,3)+a.get_element(3,3)*b->get_element(3,3));
	}
	void GLTransformationMatrix::translate(GLMatrixNumber x, GLMatrixNumber y, GLMatrixNumber z)
	{
		GLMatrix translate_matrix(4,1);

		translate_matrix.set_element(0,0, x);
		translate_matrix.set_element(1,0, y);
		translate_matrix.set_element(2,0, z);
		translate_matrix.set_element(3,0, 1);
		GLMatrix* result_matrix = ((GLMatrix*)this)->multiply(&translate_matrix);

		this->set_element(0,3, result_matrix->get_element(0,0));
		this->set_element(1,3, result_matrix->get_element(1,0));
		this->set_element(2,3, result_matrix->get_element(2,0));
		this->set_element(3,3, result_matrix->get_element(3,0));

		delete result_matrix;
	}
	void GLTransformationMatrix::rotate(GLMatrixNumber yaw, GLMatrixNumber pitch, GLMatrixNumber roll)
	{
		GLTransformationMatrix rotation;
		rotation.set_element(0,0, cos(yaw)*cos(pitch));
		rotation.set_element(0,1, ((sin(yaw)*cos(roll))+(cos(yaw)*sin(pitch)*sin(roll))));
		rotation.set_element(0,2, ((sin(yaw)*sin(roll))-(cos(yaw)*sin(pitch)*cos(roll))));

		rotation.set_element(1,0, ((-sin(yaw)*cos(pitch))));
		rotation.set_element(1,1, ((cos(yaw)*cos(roll))-(sin(yaw)*sin(pitch)*sin(roll))));
		rotation.set_element(1,2, ((cos(yaw)*sin(roll))+(sin(yaw)*sin(pitch)*cos(roll))));

		rotation.set_element(2,0, sin(pitch));
		rotation.set_element(2,1, (-cos(pitch)*sin(roll)));
		rotation.set_element(2,2, cos(pitch)*cos(roll));

		rotation.multiply(this);

		this->copy(&rotation);
	}
	void GLTransformationMatrix::rotate_x(GLMatrixNumber roll)
	{
		//cos / sin takes radians
		GLTransformationMatrix rotation_x;
		rotation_x.set_element(0,0, 1.0f);
		rotation_x.set_element(0,1, 0.0f);
		rotation_x.set_element(0,2, 0.0f);
		rotation_x.set_element(1,0, 0.0f);
		rotation_x.set_element(1,1, cos(roll));
		rotation_x.set_element(1,2, sin(roll));
		rotation_x.set_element(2,0, 0.0f);
		rotation_x.set_element(2,1, -sin(roll));
		rotation_x.set_element(2,2, cos(roll));

		this->multiply(&rotation_x);
	}
	void GLTransformationMatrix::rotate_y(GLMatrixNumber pitch)
	{
		//cos / sin takes radians
		GLTransformationMatrix rotation_y;
		rotation_y.set_element(0, 0, cos(pitch));
		rotation_y.set_element(0, 1, 0.0f);
		rotation_y.set_element(0, 2, -sin(pitch));

		rotation_y.set_element(1, 0, 0.0f);
		rotation_y.set_element(1, 1, 1.0f);
		rotation_y.set_element(1, 2, 0.0f);

		rotation_y.set_element(2, 0, sin(pitch));
		rotation_y.set_element(2, 1, 0.0f);
		rotation_y.set_element(2, 2, cos(pitch));

		this->multiply(&rotation_y);
	}
	void GLTransformationMatrix::rotate_z(GLMatrixNumber yaw)
	{
		//cos / sin takes radians
		GLTransformationMatrix rotation_z;
		rotation_z.set_element(0,0, cos(yaw));
		rotation_z.set_element(0,1, sin(yaw));
		rotation_z.set_element(0,2, 0.0f);

		rotation_z.set_element(1,0, -sin(yaw));
		rotation_z.set_element(1,1,cos(yaw));
		rotation_z.set_element(1,2, 0.0f);

		rotation_z.set_element(2,0, 0.0f);
		rotation_z.set_element(2,1, 0.0f);
		rotation_z.set_element(2,2, 1.0f);

		this->multiply(&rotation_z);
	}
	GLTransformationMatrix::~GLTransformationMatrix()
	{
		// TODO Auto-generated destructor stub
	}

} /* namespace game */
