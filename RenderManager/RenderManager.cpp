#include "RenderManager.h"
#include <SDL/SDL_gfxPrimitives.h>
#include <time.h>
#include <list>
#include <map>
using namespace std;

namespace {
   int const CellSize = 4;
   inline int pixelhash(int col, int row) { return ((col * 10) + row); }
   map<int, RGBColor> colorMap;
}

RenderManager::RenderManager(GameGrid::Ptr grid)
    : WINDOW_WIDTH((grid->GetGridSize()-1)*CellSize), 
    WINDOW_HEIGHT((grid->GetGridSize()-1)*CellSize), 
    WINDOW_TITLE("Mega-Awesome Game of Life"),
    model(grid),
    GOLDEN_RATIO_CONJUGATE(0.618033988749895)
{
    SDL_Init(SDL_INIT_VIDEO);

    screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption(WINDOW_TITLE, 0);

    close_requested = false;
    //database_connection = spatial_db.get_database();

   hue = (rand()%256)/RAND_MAX;

   RGBColor temp = {240, 128, 0};
   /* Initialize all colors */
   for(size_t col = 0; col < model->GetGridSize()-1; ++col)
   {
       for(size_t row = 0; row < model->GetGridSize()-1; ++row)
       {

           temp.Red = temp.Red++%256;
           temp.Green = temp.Green++%256;
           temp.Blue = temp.Blue++%256;

           colorMap[pixelhash(col, row)] = temp;
       }
   }


}

RenderManager::Ptr RenderManager::construct(GameGrid::Ptr grid)
{
    RenderManager::Ptr c(new RenderManager(grid));
    c->self = c;
    return c;
}

RenderManager::~RenderManager(){}


bool RenderManager::render_frame()
{
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    for(size_t col = 0; col < model->GetGridSize()-1; ++col)
    {
        
        for(size_t row = 0; row < model->GetGridSize()-1; ++row)
        { 
            RGBColor rgb = colorMap[pixelhash(col,row)];
            if(model->GetCellValue(col, row))
                boxRGBA(screen, col*CellSize, row*CellSize, (col+1)*CellSize, (row+1)*CellSize, 
                     rgb.Red, rgb.Green, rgb.Blue, 255);
           if(CellSize >= 4) 
            rectangleRGBA(screen, col*CellSize, row*CellSize, (col+1)*CellSize, (row+1)*CellSize, 
                    195, 195, 195, 255);
        }
    }
    /* Render Cell here */
    SDL_Flip(screen);
#ifdef FRAME_LIMIT
    const int FRAME_TIME = 10;
    static int previous_time = SDL_GetTicks();
    while(FRAME_TIME > (SDL_GetTicks() - previous_time))
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

    }
    previous_time = SDL_GetTicks();
#endif
    return close_requested;

}

void RenderManager::render_cell()
{
    //Cell p;
    RGBColor rgb = get_color();
/*
    boxRGBA(screen,
            p.X, p.Y,
            p.X+10, p.Y+10,
            rgb.Red, rgb.Green, rgb.Blue, 255);
*/
    return;
}

void RenderManager::render_region()
{
    RGBColor rgb = get_color();
    rectangleRGBA( screen,
            0, 0,
            10, 40,
            rgb.Red, rgb.Green, rgb.Blue, 255);
    return;
}


RGBColor RenderManager::get_color()
{
    HSVColor hsv;
    
   hue += GOLDEN_RATIO_CONJUGATE;
   hue = modulus(hue, 1);
    hsv.Hue = hue;
    hsv.Saturation = 0.9;
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





