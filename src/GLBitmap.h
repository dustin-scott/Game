/*
 * GLBitmap.h
 *
 *  Created on: Nov 25, 2012
 *      Author: Dustin Scott
 */

#ifndef GLBITMAP_H_
#define GLBITMAP_H_
#include <stdlib.h>
#include <stdio.h>
namespace game
{

	class GLBitmap
	{
		public:
			int width;
			int height;
			char* data;
			bool loadBMP(char* file_name);
			GLBitmap();
			GLBitmap(char* file_name);
			virtual ~GLBitmap();
	};

} /* namespace game */
#endif /* GLBITMAP_H_ */
