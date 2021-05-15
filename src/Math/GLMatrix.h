/*
 * GLMatrix.h
 *
 *  Created on: Dec 23, 2012
 *      Author: dustin
 */

#ifndef GLMATRIX_H_
#define GLMATRIX_H_
#include "../GameTypes.h"
#include <string>
#include <cstdio>
#include "Math.h"
namespace game {
typedef GLfloat GLMatrixNumber;
class GLMatrix
{
private:
	char* string_buffer;
	int string_buffer_length;
public:
	int rows;
	int columns;
	GLMatrixNumber* data;
	void zero(void);
	GLMatrix* transpose();
	GLMatrix* inverse();
	GLMatrix* cofactor();
	GLMatrix* adjoint();
	GLMatrix* scalar_multiply(GLMatrixNumber scalare_value);
	GLMatrix* multiply(GLMatrix* operand);
	void set_element(int row, int column, GLMatrixNumber value);
	GLMatrixNumber get_element(int row, int column);
	const char* to_string();
	GLMatrixNumber determinant();
	void copy(GLMatrix* matrix);
	GLMatrix(int rows, int columns);
	virtual ~GLMatrix();
};

} /* namespace game */
#endif /* GLMATRIX_H_ */
