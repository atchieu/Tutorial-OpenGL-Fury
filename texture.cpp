/*
 * ---------------- www.spacesimulator.net --------------
 *   ---- Space simulators and 3d engine tutorials ----
 *
 * Author: Damiano Vitulli
 *
 * This program is released under the BSD licence
 * By using this program you agree to licence terms on spacesimulator.net copyright page
 *
 * Tutorial 3: 3d engine - Texture mapping with OpenGL!
 *
 * Include File: texture.cpp
 *
 */

/*
 
Mac OS X port by Karakoussis Apostolos
mail: ktolis@csd.auth.gr
http://hal.csd.auth.gr/~ktolis

 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include "texture.h"        


/**********************************************************
 *
 * VARIABLES DECLARATION
 *
 *********************************************************/

/*** Counter to keep track of the last loaded texture ***/
int num_texture=-1;

long _Swap16(long D) {
	return((D<<8)|(D>>8));
}

/**********************************************************
 *
 * FUNCTION LoadBitmap(char *)
 *
 * This function loads a bitmap file and return the OpenGL reference ID to use that texture
 *
 *********************************************************/
int LoadBitmap(char *filename)
{
    unsigned char *l_texture; // The pointer to the memory zone in which we will load the texture
    int l_index, l_index2=0;
    FILE * file;
     
    // windows.h gives us these types to work with the Bitmap files
    BITMAPFILEHEADER fileheader; 
    BITMAPINFOHEADER infoheader;
    RGBTRIPLE rgb;

    num_texture++; // The counter of the current texture is increased

    if( (file = fopen(filename, "rb"))==NULL) return (-1); // Open the file for reading
    
    fread(&fileheader, sizeof(fileheader), 1, file); // Read the fileheader
    
    fseek(file, sizeof(fileheader), SEEK_SET); // Jump the fileheader
    fread(&infoheader, sizeof(infoheader), 1, file); // and read the infoheader


    fileheader.bfSize=_Swap16(fileheader.bfSize);
  
//    infoheader.biSize=_Swap16(infoheader.biSize);
    infoheader.biWidth=_Swap16(infoheader.biWidth);
    infoheader.biHeight=_Swap16(infoheader.biHeight);

/*
  printf("\nType   : %c%c",fileheader.bfType,fileheader.bfType>>8);
  printf("\nSize   : %d",fileheader.bfSize);
  printf("\nRes1   : %d",fileheader.bfReserved1);
  printf("\nRes2   : %d",fileheader.bfReserved2);
  printf("\nOffBits: %d\n",fileheader.bfOffBits);

//  printf("\nSize       : %d",infoheader.biSize);
  printf("\nWidth      : %d",infoheader.biWidth);
  printf("\nHeight     : %d",infoheader.biHeight);
  printf("\nPlanes     : %d",infoheader.biPlanes);
  printf("\nBitCount   : %d",infoheader.biBitCount);
  printf("\nCompression: %d",infoheader.biCompression);
  printf("\nSizeImage  : %d",infoheader.biSizeImage);
  printf("\nXPels      : %d",infoheader.biXPelsPerMeter);
  printf("\nYPels      : %d",infoheader.biYPelsPerMeter);
  printf("\nClrUsed    : %d",infoheader.biClrUsed);
  printf("\nClrImpor   : %d",infoheader.biClrImportant);
  printf("\n");
*/

    // Now we need to allocate the memory for our image (width * height * color deep)
    l_texture = (byte *) malloc(infoheader.biWidth * infoheader.biHeight * 4);
    // And fill it with zeros
    memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);
 
    // At this point we can read every pixel of the image
    for (l_index=0; l_index < infoheader.biWidth*infoheader.biHeight; l_index++)
    {            
            // We load an RGB value from the file
            fread(&rgb, sizeof(rgb), 1, file); 
						
            // And store it
            l_texture[l_index2+0] = rgb.rgbtRed; // Red component
            l_texture[l_index2+1] = rgb.rgbtGreen; // Green component
            l_texture[l_index2+2] = rgb.rgbtBlue; // Blue component
            l_texture[l_index2+3] = 255; // Alpha value
            l_index2 += 4; // Go to the next position
    }

    fclose(file); // Closes the file stream
     
    glBindTexture(GL_TEXTURE_2D, num_texture); // Bind the ID texture specified by the 2nd parameter

    // The next commands sets the texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // The magnification function ("linear" produces better results)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //The minifying function

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // We don't combine the color with the original surface color, use only the texture map.

    // Finally we define the 2d texture
    glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    // And create 2d mipmaps for the minifying function
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    free(l_texture); // Free the memory we used to load the texture

    return (num_texture); // Returns the current texture OpenGL ID
}
