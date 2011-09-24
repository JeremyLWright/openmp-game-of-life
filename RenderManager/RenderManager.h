#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

struct RGBColor {
    int Red;
    int Green;
    int Blue;
};

struct HSVColor {
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
    void render_region();
    const char* WINDOW_TITLE;
    SDL_Surface* screen;
    SDL_Event event;
//    SpatialDB::SpatialModel&  spatial_db;
    const float GOLDEN_RATIO_CONJUGATE;
    double modulus(double a, double b);
    float hue;

    RGBColor hsv_to_rgb(HSVColor hsv);
    RGBColor get_color();
    
};

#endif
