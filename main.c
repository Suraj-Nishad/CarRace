#include <stdio.h>
#include "obj_oil.h"
#include "obj_car.h"
#include "obj_powerup.h"

// Default values imports
#include "main.h"

// SDL Includes
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int opponent_pos[] = {160, 210, 260, 310, 360, 440};

// Scores
char  scorebanner[100];
char  levelbanner[100];
char  collisionbanner[] = "Show me your license..";
unsigned int score = 0;
unsigned int level = 1;
unsigned int bg_level_acceleration = 0;
unsigned int bg_max_gear    = 4;

//Surface Definiton
SDL_Surface * car = NULL;
SDL_Surface * opponent1 = NULL;
SDL_Surface * opponent2 = NULL;
SDL_Surface * opponent3 = NULL;
SDL_Surface * screen = NULL;
SDL_Surface * bgTrack = NULL;
SDL_Surface * message = NULL;
TTF_Font *font = NULL;
//The color of the font
SDL_Color textColor = { 255, 255, 255 };


//The frame rate
//const int FRAMES_PER_SECOND = 20;

//car definition
obj_car myCar, opponentCar1, opponentCar2, opponentCar3;
//const  int SPEED= (20);

//The event structure
SDL_Event event;
Uint32 colorKey;
Uint8 *keystate;


//take the offset distance, src surface that is to be blit and destination surface to blit on
void applySurface (int x, int y, SDL_Surface* src, SDL_Surface* dest)
{

    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface (src, NULL, dest, &offset);
}


// Initialise the SLD enviroment
int init()
{
    //Initialize all SDL subsystems
    if ( SDL_Init ( SDL_INIT_EVERYTHING ) == -1 ) {
        return FALSE;
    }

    //Set up the screen
    screen = SDL_SetVideoMode ( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if ( screen == NULL ) {
        return FALSE;
    }

    //Set the window caption
    SDL_WM_SetCaption ( "ecaR raC", NULL );

    //If everything initialized fine
    return TRUE;
}
int load_files()
{
//Open the font
    TTF_Init();
    font = TTF_OpenFont ( "assets/fonts/DejaVuSans.ttf", 24 ); //If there was a problem in loading the background

//If there was an error in loading the font
    if ( font == NULL ) {
        return FALSE;
    }
//If everything loaded fine
    return TRUE;
}



int main (int argc, char * argv[])
{
    int i, j = 0;
    int quit = FALSE;
    int stop_blit = FALSE;

    SDL_Rect carOffset, opponentOffset1, opponentOffset2, opponentOffset3;


    //defining the bagroung offset
    int bgX = 0, bgY = 0;
    int bg_acceleration = 0;
    keystate = SDL_GetKeyState (NULL);

    carOffset.x = myCar.x = 310;
    carOffset.y = myCar.y = 400;
    carOffset.h =  80;
    carOffset.w = 40;
    myCar.speedY = 30;

    opponentOffset1.x = opponentCar1.x = 160 ;
    opponentOffset1.y = opponentCar1.y = -100;
    opponentOffset1.w = 40;
    opponentOffset1.h = 80;
    opponentOffset2.x = opponentCar2.x = 210;
    opponentOffset2.y = opponentCar2.y = -200;
    opponentOffset2.w = 40;
    opponentOffset2.h = 80;
    opponentOffset3.x = opponentCar3.x = 260;
    opponentOffset3.y = opponentCar3.y = -300;
    opponentOffset3.w = 40;
    opponentOffset3.h = 80;

    //Initialise the screen
    if (init() == FALSE ) {
        printf ("Initialisation of screen failed...!! check inti() function... ");
        return 1;
    }
    if (load_files() == FALSE) {
        printf ("Load failed.");
        return 1;
    }

    //loading the images
    bgTrack = IMG_Load ("assets/images/trac.png");
    car   = SDL_DisplayFormat (IMG_Load ("assets/images/car.bmp") );
    opponent1 = SDL_DisplayFormat (IMG_Load ("assets/images/traffic0.bmp") );
    opponent2 = SDL_DisplayFormat (IMG_Load ("assets/images/traffic1.bmp") );
    opponent3 = SDL_DisplayFormat (IMG_Load ("assets/images/traffic2.bmp") );

    //If the image was optimized just fine
    if ( car != NULL ) {
        //Map the color key
        colorKey = SDL_MapRGB ( car->format, 0XFF, 0xFF, 0xFF );
        //Set all pixels of color R 0xFF, G 0xFF, B 0xFF to be transparent
        SDL_SetColorKey ( car, SDL_SRCCOLORKEY, colorKey );
    }
    if ( opponent1 != NULL ) {
        //Map the color key
        colorKey = SDL_MapRGB ( opponent1->format, 0XFF, 0xFF, 0xFF );
        //Set all pixels of color R 0xFF, G 0xFF, B 0xFF to be transparent
        SDL_SetColorKey ( opponent1, SDL_SRCCOLORKEY, colorKey );
    }
    if ( opponent2 != NULL ) {
        //Map the color key
        colorKey = SDL_MapRGB ( opponent2->format, 0XFF, 0xFF, 0xFF );
        //Set all pixels of color R 0xFF, G 0xFF, B 0xFF to be transparent
        SDL_SetColorKey ( opponent2, SDL_SRCCOLORKEY, colorKey );
    }
    if ( opponent3 != NULL ) {
        //Map the color key
        colorKey = SDL_MapRGB ( opponent3->format, 0XFF, 0xFF, 0xFF );
        //Set all pixels of color R 0xFF, G 0xFF, B 0xFF to be transparent
        SDL_SetColorKey ( opponent3, SDL_SRCCOLORKEY, colorKey );
    }



    while (!quit) {
        keystate = SDL_GetKeyState (NULL);


        //polling an event to happen
        while (SDL_PollEvent (&event) ) {
            if (event.type == SDL_QUIT) {
                //clean up everythings
                SDL_FreeSurface (bgTrack);
                SDL_FreeSurface (car);
                //SDL_FreeSurface(screen);
                SDL_Quit();

            }
        }
        //}
        if (keystate[SDLK_UP]) {

            ++i;
            if (i == 20) {
                bg_acceleration += bg_acceleration < bg_max_gear ? 1 : 0;
                i = 0;
            }
            //printf ("BOOO....up key pressed ");

        }
        if (keystate[SDLK_DOWN]) {
            ++j;
            if (j == 12) {

                bg_acceleration -= bg_acceleration > 0 && bg_acceleration > bg_level_acceleration ? 1 : 0;
                //printf ("BOOO....up key pressed ");
                j = 0;
            }

        }
        if (keystate[SDLK_LEFT]) {

            myCar.x -=  myCar.x > 160 ? 2 : 0;
            //printf ("BOOO....up key pressed ");

        }
        if (keystate[SDLK_RIGHT]) {

            myCar.x += myCar.x < 455 ? 2 : 0;
            //printf ("BOOO....up key pressed ");

        }

        //}

        bgY += bg_acceleration + 2;

        //If the background has gone too far
        if ( bgY >= bgTrack->h ) {
            //Reset the offset
            bgY = 0 ;
        }

        //Show the background
        if (!stop_blit) {
            applySurface ( bgX, bgY, bgTrack, screen );
            //        apply_surface( bgX + background->w, bgY, background, screen );
            applySurface ( bgX, bgY - bgTrack->h, bgTrack, screen );
            score += bg_acceleration * 10 + 5;
            if (score % 10000 == 0) {
                level += 1;
                ++bg_level_acceleration;
                ++bg_max_gear;
            }
            sprintf (scorebanner, "Score:%d", score);
            sprintf (levelbanner, "Level:%d", level);
            message = TTF_RenderText_Solid ( font, scorebanner, textColor );
            applySurface ( 0, 50, message, screen );
            message = TTF_RenderText_Solid ( font, levelbanner, textColor );
            applySurface ( 0, 80, message, screen );
        }
        //Show the dot
        if (opponentCar1.y > 480) {
            opponentCar1.x = opponent_pos[rand() % 6] ;
            opponentCar1.y = -100 + rand()%50;
        }
        if (opponentCar2.y > 480) {
            opponentCar2.x = opponent_pos[rand() % 6] ;
            opponentCar2.y = -100 + rand()%50;
        }
        if (opponentCar3.y > 480) {
            opponentCar3.x = opponent_pos[rand() % 6] ;
            opponentCar3.y = -100 + rand()%50;
        }
        opponentCar1.y += bg_max_gear - 3 + bg_acceleration ;
        opponentCar2.y += bg_max_gear - 3 + bg_acceleration;
        opponentCar3.y += bg_max_gear - 3 + bg_acceleration;
        carOffset.x = myCar.x ;
        carOffset.y = myCar.y ;
        opponentOffset1.x = opponentCar1.x ;
        opponentOffset1.y = opponentCar1.y ;
        opponentOffset2.x = opponentCar2.x ;
        opponentOffset2.y = opponentCar2.y ;
        opponentOffset3.x = opponentCar3.x ;
        opponentOffset3.y = opponentCar3.y ;
        if (check_collision (carOffset, opponentOffset1) && stop_blit != TRUE) {
            stop_blit = TRUE;
            //printf("Collision detected");
            SDL_FreeSurface (car);
            SDL_FreeSurface (opponent1);

            car   = SDL_DisplayFormat (IMG_Load ("assets/images/car_damaged.bmp") );
            opponent1 = SDL_DisplayFormat (IMG_Load ("assets/images/traffic0_damaged.bmp") );
            if ( car != NULL ) {
                //Map the color key
                colorKey = SDL_MapRGB ( car->format, 0XFF, 0xFF, 0xFF );
                //Set all pixels of color R 0xFF, G 0xFF, B 0xFF to be transparent
                SDL_SetColorKey ( car, SDL_SRCCOLORKEY, colorKey );
            }
            if ( opponent1 != NULL ) {
                //Map the color key
                colorKey = SDL_MapRGB ( opponent1->format, 0XFF, 0xFF, 0xFF );
                //Set all pixels of color R 0xFF, G 0xFF, B 0xFF to be transparent
                SDL_SetColorKey ( opponent1, SDL_SRCCOLORKEY, colorKey );
            }
            applySurface ( myCar.x, myCar.y, car, screen );
            applySurface (opponentCar1.x , opponentCar1.y , opponent1, screen );
            message = TTF_RenderText_Solid ( font, collisionbanner, textColor );
            applySurface ( 160, 240, message, screen );
            SDL_Flip ( screen );
        }
        if (check_collision (carOffset, opponentOffset2) && stop_blit != TRUE) {
            stop_blit = TRUE;
            //printf("Collision detected");
            SDL_FreeSurface (car);
            SDL_FreeSurface (opponent2);
            car   = SDL_DisplayFormat (IMG_Load ("assets/images/car_damaged.bmp") );
            opponent2 = SDL_DisplayFormat (IMG_Load ("assets/images/traffic1_damaged.bmp") );
            if ( car != NULL ) {
                //Map the color key
                colorKey = SDL_MapRGB ( car->format, 0XFF, 0xFF, 0xFF );
                //Set all pixels of color R 0xFF, G 0xFF, B 0xFF to be transparent
                SDL_SetColorKey ( car, SDL_SRCCOLORKEY, colorKey );
            }
            if ( opponent2 != NULL ) {
                //Map the color key
                colorKey = SDL_MapRGB ( opponent2->format, 0XFF, 0xFF, 0xFF );
                //Set all pixels of color R 0xFF, G 0xFF, B 0xFF to be transparent
                SDL_SetColorKey ( opponent2, SDL_SRCCOLORKEY, colorKey );
            }
            applySurface ( myCar.x, myCar.y, car, screen );
            applySurface (opponentCar2.x , opponentCar2.y , opponent1, screen );
            message = TTF_RenderText_Solid ( font, collisionbanner, textColor );
            applySurface ( 160, 240, message, screen );
            SDL_Flip ( screen );
        }
        if (check_collision (carOffset, opponentOffset3) && stop_blit != TRUE) {
            stop_blit = TRUE;
            //printf("Collision detected");
            SDL_FreeSurface (car);
            SDL_FreeSurface (opponent3);
            car   = SDL_DisplayFormat (IMG_Load ("assets/images/car_damaged.bmp") );
            opponent3 = SDL_DisplayFormat (IMG_Load ("assets/images/traffic2_damaged.bmp") );
            if ( car != NULL ) {
                //Map the color key
                colorKey = SDL_MapRGB ( car->format, 0XFF, 0xFF, 0xFF );
                //Set all pixels of color R 0xFF, G 0xFF, B 0xFF to be transparent
                SDL_SetColorKey ( car, SDL_SRCCOLORKEY, colorKey );
            }
            if ( opponent3 != NULL ) {
                //Map the color key
                colorKey = SDL_MapRGB ( opponent3->format, 0XFF, 0xFF, 0xFF );
                //Set all pixels of color R 0xFF, G 0xFF, B 0xFF to be transparent
                SDL_SetColorKey ( opponent3, SDL_SRCCOLORKEY, colorKey );
            }
            applySurface ( myCar.x, myCar.y, car, screen );
            applySurface (opponentCar3.x , opponentCar3.y , opponent3, screen );
            message = TTF_RenderText_Solid ( font, collisionbanner, textColor );
            applySurface ( 160, 240, message, screen );
            SDL_Flip ( screen );
        }
        if (!stop_blit) {
            applySurface ( myCar.x, myCar.y, car, screen );
            applySurface (opponentCar1.x , opponentCar1.y , opponent1, screen );
            applySurface (opponentCar2.x , opponentCar2.y , opponent2, screen );
            applySurface (opponentCar3.x , opponentCar3.y , opponent3, screen );

        }

        //Update the screen
        if ( SDL_Flip ( screen ) == -1 ) {
            return 1;
        }

        //hold the breath for some sec
        SDL_Delay (1);


    }
    return 0;
}
