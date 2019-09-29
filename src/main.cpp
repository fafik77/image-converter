#ifdef __cplusplus
    #include <cstdlib>
    #include <stdio.h>
#else
    #include <stdlib.h>
#endif

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



void errorClean()
{
	printf("error occurred! Quits\n");
	IMG_Quit();
	SDL_Quit();
	exit(2);
}

int main( int argc, char* argv[] )
{
	readArgs( argc, argv );
	if(! path_in){
		printf("\
! Does NOT work with UTF fileNames\n\
 instead please rename UTF file to ANSII !\n\
\n\
arg<1>: input image fileName\n\
arg[2]: output fileName (default .jpg)\n\
arg[3]: output quality  (default 100)\n\
arg[4]: RGB r (0-255)\n\
arg[5]: RGB g (0-255)\n\
arg[6]: RGB b (0-255)\n\
");
		exit(1);
	}

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf("sdl init error %s\n", SDL_GetError() );
		errorClean();
	}


	SDL_Surface* surf_image= nullptr;
	SDL_Surface* surf= nullptr;
	int format= SDL_PIXELFORMAT_RGBA32;

	surf_image= IMG_Load( path_in );
	if(!surf_image){
		printf("image not found.\n");
		exit(0);
	}
	surf= SDL_CreateRGBSurfaceWithFormat(0, surf_image->w, surf_image->h, 32, format);
	if(!surf){
		printf("cant create background\n");
		exit(0);
	}

	SDL_Rect tempRect;
	tempRect.x= 0;
	tempRect.y= 0;
	tempRect.w= surf_image->w;
	tempRect.h= surf_image->h;
	SDL_FillRect(surf, &tempRect, SDL_MapRGB(surf->format, settings_RGB_r, settings_RGB_g, settings_RGB_b ) );
	SDL_BlitSurface(surf_image, NULL, surf, &tempRect);

	int retVal= IMG_SaveJPG(surf, ".-jpg", settings_qual);
	retVal<< 16;
	retVal+= rename( ".-jpg", path_out? path_out : ".jpg" );
	if(retVal) printf("Unexpected error %i", retVal);

	IMG_Quit();
	SDL_Quit();
	return retVal;
}

