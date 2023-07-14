#pragma once 

#include <iomanip>
#include <SDL_TTF.h>
#include "Globals.h"
#include "Drawable.h"
using std::string;

class Presenter
{
public:
    static SDL_Window* m_mainWindow;
    static SDL_Renderer* m_mainRenderer;

    static int2 m_digitRectSz;

    static unsigned int m_SCREEN_WIDTH;
    static unsigned int m_SCREEN_HEIGHT;
    static SDL_Texture* M_BACKGROUND_TEXTURE;
    static SDL_Texture* M_DIGIT;

    void init();
    void update();
    void draw();

    SDL_Renderer* getRenderer();

    static void drawObject(SDL_Texture* texture);
    static void drawNumber(int num, int2 stPoint, int2 digitSz); //For now works only for positive numbers and 0
    static void drawObject(Drawable& drawable);
}; 