/** \brief This simple program converts any given input image file into jpg or png format and saves it
 * to compile; needs x32 mingw, with all SDL2 libs also x32 (not any 86_64_32 ibm mix)
 update: 2024-02-18 now supports PNG export as actual PNG, no more renames of temp files (if you relied on file presence then get over it as rename would often times fail)
 */


#ifdef __cplusplus
    #include <cstdlib>
    #include <stdio.h>
    #include <cstring>
#else
    #include <stdlib.h>
#endif

#include <windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//#include <string>		///too big!!!!


char* path_in= nullptr;
char* path_out= nullptr;
Uint8 settings_RGB_r= 0;
Uint8 settings_RGB_g= 0;
Uint8 settings_RGB_b= 0;
int settings_qual= 100;

void readArgs( int argc, char* argv[] )
{
	if( argc> 1 ){
		path_in= argv[1];
		if(argc> 2)
			path_out= argv[2];
		if(argc> 3)
			settings_qual= atoi( argv[3] );
		if(!settings_qual) settings_qual= 100;

		if(argc> 4)	settings_RGB_r= atoi( argv[4] );
		if(argc> 5)	settings_RGB_g= atoi( argv[5] );
		if(argc> 6)	settings_RGB_b= atoi( argv[6] );
//		printf("path_in = |%s|\n", path_in);
	}
}
 ///checks if provided name ends with .png (any case variation)
bool isPngType(const char* name)
{
	if(!name) return false;
	size_t len= strlen(path_out);
	const char* last4c= name+ len -4;
	if(last4c[0] != '.') return false;
	if(last4c[1] != 'P' && last4c[1] != 'p') return false;
	if(last4c[2] != 'N' && last4c[2] != 'n') return false;
	if(last4c[3] != 'G' && last4c[3] != 'g') return false;
	return true;
}


void errorClean()
{
	printf("Error occurred! Quits\n");
	IMG_Quit();
	SDL_Quit();
	exit(ERROR_FILE_NOT_FOUND);
}

 ///the main program converts the input image into desired output format (jpg/png)
 ///@return should be 0 on success
int main( int argc, char* argv[] )
{
	readArgs( argc, argv );
	if(! path_in){
		printf("\
Copyright (C) 2021 fafik77 ( https://github.com/fafik77 )\n\
    This program comes with ABSOLUTELY NO WARRANTY; for details read 'License (ConvertImage).txt'.\n\
    This is free software.\n\
! Does NOT work with UTF fileNames\n\
 instead please rename UTF file to ANSII !\n\
\n\
arg<1>: input image fileName\n\
arg[2]: output fileName (default .jpg)\n\
arg[3]: output quality  (default 100) unused for .PNG\n\
arg[4]: RGB r (0-255)\n\
arg[5]: RGB g (0-255)\n\
arg[6]: RGB b (0-255)\n\
");
		exit(ERROR_INVALID_FUNCTION);
	}

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf("Error! SDL init error %s\n", SDL_GetError() );
		errorClean();
	}


	SDL_Surface* surf_image= nullptr;
	SDL_Surface* surf= nullptr;
	int format= SDL_PIXELFORMAT_RGBA32;

	surf_image= IMG_Load( path_in );
	if(!surf_image){
		printf("Error! image not found.\n");
		IMG_Quit();
		SDL_Quit();
		exit(ERROR_FILE_NOT_FOUND);
	}

 //export as PNG
	if(isPngType(path_out)){
		printf("exporting as PNG\n");
		int retVal= IMG_SavePNG(surf_image, path_out ? path_out : ".png");
		retVal<<= 16;
		IMG_Quit();
		SDL_Quit();
		return retVal;
	}

 //export as jpg with set bg color
	surf= SDL_CreateRGBSurfaceWithFormat(0, surf_image->w, surf_image->h, 32, format);
	if(!surf){
		printf("Error! can't create background\n");
		IMG_Quit();
		SDL_Quit();
		exit(ERROR_INVALID_FUNCTION);
	}

	SDL_Rect tempRect;
	tempRect.x= 0;
	tempRect.y= 0;
	tempRect.w= surf_image->w;
	tempRect.h= surf_image->h;
	SDL_FillRect(surf, &tempRect, SDL_MapRGB(surf->format, settings_RGB_r, settings_RGB_g, settings_RGB_b ) );
	SDL_BlitSurface(surf_image, NULL, surf, &tempRect);

	printf("exporting as JPEG\n");
	int retVal= IMG_SaveJPG(surf, path_out? path_out : ".jpg", settings_qual);
	retVal<<= 16;
//	retVal+= rename( ".-jpg", path_out? path_out : ".jpg" );
	if(retVal) printf("Unexpected error %i", retVal);

	IMG_Quit();
	SDL_Quit();
	return retVal;
}

