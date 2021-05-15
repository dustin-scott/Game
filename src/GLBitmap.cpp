/*
 * GLBitmap.cpp
 *
 *  Created on: Nov 25, 2012
 *      Author: Dustin Scott
 */

#include "GLBitmap.h"

namespace game
{

GLBitmap::GLBitmap()
{
	this->height = 0;
	this->width = 0;
	this->data = 0;
}
GLBitmap::GLBitmap(char* file_name)
{
	this->height = 0;
	this->width = 0;
	this->data = 0;
	this->loadBMP(file_name);
}
GLBitmap::~GLBitmap()
{
	delete this->data;
}
//-----------------------------------------------------------------------------
// Name: getBitmapImageData()
// Desc: Simply image loader for 24 bit BMP files.
//-----------------------------------------------------------------------------
bool GLBitmap::loadBMP(char* file_name)
{
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
	int i;

    if( (pFile = fopen(file_name, "rb") ) == NULL )
		printf("ERROR: getBitmapImageData - %s not found\n",file_name);

    // Seek forward to width and height info
    fseek( pFile, 18, SEEK_CUR );

    if( (i = fread(&this->width, 4, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n", file_name);

    if( (i = fread(&this->height, 4, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n", file_name);

    if( (fread(&nNumPlanes, 2, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read plane count from %s.\n", file_name);

    if( nNumPlanes != 1 )
		printf( "ERROR: getBitmapImageData - Plane count from %s is not 1: %u\n", file_name, nNumPlanes );

    if( (i = fread(&nNumBPP, 2, 1, pFile)) != 1 )
		printf( "ERROR: getBitmapImageData - Couldn't read BPP from %s.\n", file_name );

    if( nNumBPP != 24 )
		printf( "ERROR: getBitmapImageData - BPP from %s is not 24: %u\n", file_name, nNumBPP );

    // Seek forward to image data
    fseek( pFile, 24, SEEK_CUR );

	// Calculate the image's total size in bytes. Note how we multiply the
	// result of (width * height) by 3. This is becuase a 24 bit color BMP
	// file will give you 3 bytes per pixel.
    int nTotalImagesize = (this->width * this->height) * 3;

    this->data = (char*) malloc( nTotalImagesize );

    if( (i = fread(this->data, nTotalImagesize, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n", file_name);

    //
	// Finally, rearrange BGR to RGB
	//

	char charTemp;
    for( i = 0; i < nTotalImagesize; i += 3 )
	{
		charTemp = this->data[i];
		this->data[i] = this->data[i+2];
		this->data[i+2] = charTemp;
    }

    return true;
}
} /* namespace game */
