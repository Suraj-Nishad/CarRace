#include <SDL/SDL.h>
#include "main.h"
int check_collision ( SDL_Rect A, SDL_Rect B )
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;
    if ( bottomA <= topB ) {
        return FALSE;
    }
    if ( topA >= bottomB ) {
        return FALSE;
    }
    if ( rightA <= leftB ) {
        return FALSE;
    }
    if ( leftA >= rightB ) {
        return FALSE;
    }
    return TRUE;
}
