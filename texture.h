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
 * File header: texture.h
 *
 */

/*

 Mac OS X port by Karakoussis Apostolos
 mail: ktolis@csd.auth.gr
 http://hal.csd.auth.gr/~ktolis

 */


/**********************************************************
 *
 * VARIABLES DECLARATION
 *
 *********************************************************/

/*** Counter to keep track of the last loaded texture ***/
extern int num_texture;


/**********************************************************
 *
 * FUNCTION LoadBitmap(char *)
 *
 * This function loads a bitmap file and return the OpenGL reference ID to use that texture
 *
 *********************************************************/

extern int LoadBitmap(char *filename);

typedef struct _BITMAPFILEHEADER {  // Offset   Size
    short   bfType;                 //      0      2
    long    bfSize;                 //      2      4
    short   bfReserved1;            //      6      2
    short   bfReserved2;            //      8      2
    long    bfOffBits;              //     10      4
} BITMAPFILEHEADER;                 // Total size: 14

typedef struct _BITMAPINFOHEADER                      /**** BMP file info structure ****/
{
//    long   biSize;           /* Size of info header */
    long   biWidth;          /* Width of image */
    long   biHeight;         /* Height of image */
    short  biPlanes;         /* Number of color planes */
    short  biBitCount;       /* Number of bits per pixel */
    long   biCompression;    /* Type of compression to use */
    long   biSizeImage;      /* Size of image data */
    long   biXPelsPerMeter;  /* X pixels per meter */
    long   biYPelsPerMeter;  /* Y pixels per meter */
    long   biClrUsed;        /* Number of colors used */
    long   biClrImportant;   /* Number of important colors */
} BITMAPINFOHEADER;

typedef struct _RGBTRIPLE {
    char    rgbtBlue;
    char    rgbtGreen;
    char    rgbtRed;
//    char    rgbReserved;
} RGBTRIPLE;

#define byte unsigned char

