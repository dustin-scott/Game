#include "GLMatrix.h"
namespace game {

GLMatrix::GLMatrix(int rows, int columns) {
	this->rows = rows;
	this->columns = columns;
	this->data = new GLMatrixNumber[rows*columns];
	this->string_buffer = 0;
	this->string_buffer_length = 0;
	this->zero();
}
void GLMatrix::set_element(int row, int column, GLMatrixNumber value)
{

	this->data[column*this->rows+row] = value;
}
GLMatrixNumber GLMatrix::get_element(int row, int column)
{
	return this->data[column*this->rows+row];
}
void GLMatrix::copy(GLMatrix* matrix)
{
	int i = 0;
	int iterations = this->rows*this->columns;
	for(i = 0; i < iterations; i++)
	{
		this->data[i] = matrix->data[i];
	}
}
const char* GLMatrix::to_string()
{
	std::string buf;

	int i = 0;
	int j =0;
	for(i=0; i < this->rows; i++)
	{
		for(j = 0; j < this->columns; j++)
		{
			char char_buff[25];
			std::sprintf(&char_buff[0], "%f ", this->get_element(i, j));
			buf.append(char_buff);
		}
		buf.append("\n");
	}
	int buf_length = buf.length();
	if(this->string_buffer_length < buf_length+1)
	{
		if(this->string_buffer_length > 0)
		{
			delete[] this->string_buffer;
		}
		this->string_buffer = new char[buf_length+1];
	}
	buf.copy(this->string_buffer,buf_length);
	this->string_buffer[buf_length] = '\0';
	this->string_buffer_length = buf_length;

	return this->string_buffer;
}
GLMatrix* GLMatrix::inverse()
{
	GLMatrix* return_matrix = 0;
	if(this->columns == this->rows)
	{
		GLMatrixNumber determinant = this->determinant();

		if(determinant != 0)
		{
			GLMatrixNumber inverse_determinant = 1.0f/determinant;
			GLMatrix* adjoint = this->adjoint();
			return_matrix = adjoint->scalar_multiply(inverse_determinant);
			delete adjoint;
		}
	}

	return return_matrix;
}
GLMatrix* GLMatrix::cofactor()
{
	GLMatrix* return_matrix = new GLMatrix(this->rows, this->columns);

	int i = 0;
	int j = 0;
	int k = 0;
	int a = 0;
	int s = 0;
	int d = 0;
	int sign = 1;
	GLMatrix calc_matrix(this->rows-1, this->columns-1);

	for(i = 0; i < this->rows; i++)
	{
		for(j=0; j < this->columns; j++, sign *= -1)
		{
			for(k = 0, s = 0; k < this->rows; k++)
			{
				if(k != i)
				{
					for(a=0, d = 0; a < this->columns; a++)
					{
						if(a != j)
						{
							calc_matrix.set_element(s,d, this->get_element(k,a));
							d++;
						}
					}
					s++;
				}
			}
			//printf("%s\n", calc_matrix.toString());
			//printf("%f\n", calc_matrix.determinant());
			return_matrix->set_element(i,j, pow(-1, (i+j))*calc_matrix.determinant());
		}
	}

	return return_matrix;
}

GLMatrix* GLMatrix::adjoint()
{
	int i = 0;
	int j = 0;
	GLMatrix* matrix_of_cofactors = this->cofactor();
	GLMatrix* return_matrix = new GLMatrix(this->rows, this->columns);

	for(i=0; i < matrix_of_cofactors->rows; i++)
	{
		for(j=0; j < matrix_of_cofactors->columns; j++)
		{
			return_matrix->set_element(j, i, matrix_of_cofactors->get_element(i,j));
		}
	}

	delete matrix_of_cofactors;

	return return_matrix;
}
GLMatrix* GLMatrix::multiply(GLMatrix* operand)
{
	GLMatrix* return_matrix = 0;

	if(this->columns == operand->rows)
	{
		return_matrix = new GLMatrix(this->rows, operand->columns);
		int i = 0;
		int j = 0;
		int k = 0;
		for(i = 0; i < return_matrix->rows; i++)
		{
			for(j = 0; j < return_matrix->columns; j++)
			{
				for(k = 0; k < this->columns; k++)
				{
					return_matrix->set_element(i,j, return_matrix->get_element(i,j) + this->get_element(i,k)*operand->get_element(k,j));
				}
			}
		}
	}

	return return_matrix;
}
void GLMatrix::zero()
{
	int i = 0;
	int iterations = this->rows*this->columns;
	for(i = 0; i < iterations; i++)
	{
		this->data[i] = 0.0f;
	}
}

GLMatrix* GLMatrix::scalar_multiply(GLMatrixNumber scalar_value)
{
	GLMatrix* return_matrix = new GLMatrix(this->rows, this->columns);
	int i = 0;
	int j = 0;
	for(i = 0; i < this->rows; i++)
	{
		for(j = 0; j < this->columns; j++)
		{
			return_matrix->set_element(i, j, scalar_value*this->get_element(i,j));
		}
	}

	return return_matrix;
}
GLMatrixNumber GLMatrix::determinant()
{
	int i = 0;
	int j = 0;
	int k = 0;
	int a = 0;
	int s = 0;
	int d = 0;
	int sign = 1;
	GLMatrix calc_matrix(this->rows-1, this->columns-1);
	GLMatrixNumber sum = 0.0f;

	if(this->rows > 2 || this->columns > 2)
	{
		for(i = 0, j=0; j < this->rows; j++, sign *= -1)
		{
			for(k = 0, s = 0; k < this->rows; k++)
			{
				if(k != i)
				{
					for(a=0, d = 0; a < this->columns; a++)
					{
						if(a != j)
						{
							calc_matrix.set_element(s, d, this->get_element(k,a));
							d++;
						}
					}
					s++;
				}
			}
			//printf("%s\n sign: %i\n", calc_matrix.toString(), sign);
			//printf("adding: %f\n", sign*this->data[i][j]*calc_matrix.determinant());
			//printf("%f\n", calc_matrix.determinant());
			sum += sign*this->get_element(i,j)*calc_matrix.determinant();
		}
	}
	else
	{
		//printf("((%f * %f) - (%f * %f))\n",this->data[0][0],this->data[1][1],this->data[1][0],this->data[0][1]);
		sum = (this->get_element(0,0)*this->get_element(1,1))-(this->get_element(1,0)*this->get_element(0,1));
	}

	return sum;
}
GLMatrix* GLMatrix::transpose()
{
	GLMatrix* transpose_matrix = new GLMatrix(this->rows, this->columns);
	int i = 0;
	int j = 0;
	for(i=0; i < this->rows; i++)
	{
		for(j = 0; j < this->columns; j++)
		{
			transpose_matrix->set_element(i,j, this->get_element(j,i));
		}
	}
	return transpose_matrix;
}
GLMatrix::~GLMatrix()
{
	if(this->string_buffer_length)
	{
		delete[] this->string_buffer;
	}
	delete[] this->data;
}

} /* namespace game */
