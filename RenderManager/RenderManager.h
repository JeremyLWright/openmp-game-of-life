/**
 * @brief General Render Manager for drawing to an SDL Surface.
 *
 * @par
 * Copyright Jeremy Wright (c) 2011
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */
#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include <SDL/SDL.h>
#include <tr1/memory>
#include "GameGrid.h"


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
    typedef std::tr1::shared_ptr<RenderManager> Ptr;
    typedef std::tr1::weak_ptr<RenderManager> WeakPtr;
    bool close_requested;
    static RenderManager::Ptr construct(GameGrid::Ptr grid);
    virtual ~RenderManager();
    bool render_frame();
    protected:
    void render_cell();
    const int WINDOW_WIDTH;
    const int WINDOW_HEIGHT;
    void render_region();
    const char* WINDOW_TITLE;
    SDL_Surface* screen;
    SDL_Event event;
    GameGrid::Ptr model;
//    SpatialDB::SpatialModel&  spatial_db;
    const float GOLDEN_RATIO_CONJUGATE;
    double modulus(double a, double b);
    float hue;
    
    RGBColor hsv_to_rgb(HSVColor hsv);
    RGBColor get_color();
    private:
    RenderManager(GameGrid::Ptr grid);
    RenderManager::WeakPtr self;
    
};

#endif
