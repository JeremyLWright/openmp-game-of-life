#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include "Lemming.h"
#include "Region.h"
#include "SpatialModel.h"
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

class RGBColor {
    public:
    int Red;
    int Green;
    int Blue;
};

class HSVColor {
    public:
    float Hue;
    float Saturation;
    float Value;
};

class RenderManager {
    public:
    RenderManager();

    bool close_requested;
    bool render_frame();
    protected:
    void render_cell();
    const int WINDOW_WIDTH;
    const int WINDOW_HEIGHT;
    const char* WINDOW_TITLE;
    SDL_Surface* screen;
    SDL_Event event;
    SpatialDB::SpatialModel&  spatial_db;
    const float GOLDEN_RATIO_CONJUGATE;
    double modulus(double a, double b);
    float hue;

    RGBColor hsv_to_rgb(HSVColor hsv);
    RGBColor get_color();
    
};

#endif
