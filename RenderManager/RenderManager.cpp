#include "RenderManager.h"
#include <time.h>
#include <list>
using namespace std;

RenderManager::RenderManager()
    : WINDOW_WIDTH(640), 
    WINDOW_HEIGHT(480), 
    WINDOW_TITLE("Mega-Awesome Game of Life"),
    /* Initialize Model Here */
    GOLDEN_RATIO_CONJUGATE(0.618033988749895)
{
    SDL_Init(SDL_INIT_VIDEO);

    screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption(WINDOW_TITLE, 0);

    close_requested = false;
    database_connection = spatial_db.get_database();

   hue = (rand()%256)/RAND_MAX;

}


bool RenderManager::render_frame()
{
    if(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            close_requested = true;
            SDL_Quit();
            return close_requested;
        }
    }

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    /* Render Cell here */
    SDL_Flip(screen);
    return close_requested;

}

void RenderManager::render_cell()
{
    Cell p;

    RGBColor rgb = get_color();

    boxRGBA(screen,
            p.X, p.Y,
            p.X+10, p.Y+10,
            rgb.Red, rgb.Green, rgb.Blue, 255);

    return;
}

RGBColor RenderManager::get_color()
{
    HSVColor hsv;
    
   hue += GOLDEN_RATIO_CONJUGATE;
   hue = modulus(hue, 1);
    hsv.Hue = hue;
    hsv.Saturation = 0.5;
    hsv.Value = 0.95;
    return hsv_to_rgb(hsv);
}


RGBColor RenderManager::hsv_to_rgb(HSVColor hsv)
{

      RGBColor rgb;
      int h_i = (int)(hsv.Hue*6);
      float f = hsv.Hue*6 - h_i;
	  float p = hsv.Value * (1 - hsv.Saturation);
	  float q = hsv.Value * (1 - f*hsv.Saturation);
	  float t = hsv.Value * (1 - (1 - f) * hsv.Saturation);
      switch(h_i)
      {
        case 0:
            rgb.Red = (int)(hsv.Value*256);
            rgb.Green = (int)(t*256);
            rgb.Blue = (int)(p*256);
        break;
        case 1:
            rgb.Red = (int)(q*256);
            rgb.Green = (int)(hsv.Value*256);
            rgb.Blue = (int)(p*256);
        break;
        case 2:
            rgb.Red = (int)(p*256);
            rgb.Green = (int)(hsv.Value*256);
            rgb.Blue = (int)(t*256);
        break;
        case 3:
            rgb.Red = (int)(p*256);
            rgb.Green = (int)(q*256);
            rgb.Blue = (int)(hsv.Value*256);
        break;
        case 4:
            rgb.Red = (int)(t*256);
            rgb.Green = (int)(p*256);
            rgb.Blue = (int)(hsv.Value*256);
        break;
        case 5:
            rgb.Red = (int)(hsv.Value*256);
            rgb.Green = (int)(p*256);
            rgb.Blue = (int)(q*256);
        break;
      }
      return rgb;

}

double RenderManager::modulus(double a, double b)
{
int result = static_cast<int>( a / b );
return a - static_cast<double>( result ) * b;
}





