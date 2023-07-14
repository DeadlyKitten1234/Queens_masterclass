#include "Presenter.h"

#include "World.h"

extern World world;



SDL_Texture* Presenter::M_BACKGROUND_TEXTURE = nullptr;
SDL_Texture* Presenter::M_DIGIT = nullptr;
SDL_Window* Presenter::m_mainWindow = nullptr;
SDL_Renderer* Presenter::m_mainRenderer = nullptr;
unsigned int Presenter::m_SCREEN_WIDTH = 0;
unsigned int Presenter::m_SCREEN_HEIGHT = 0;
int2 Presenter::m_digitRectSz = int2(32, 42);

SDL_Renderer* Presenter::getRenderer() {
    return m_mainRenderer;
}

void Presenter::init() {
    m_SCREEN_WIDTH = 1536;
    m_SCREEN_HEIGHT = 864;

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    m_mainWindow = SDL_CreateWindow("Queens", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_SCREEN_WIDTH, m_SCREEN_HEIGHT, 0);
    m_mainRenderer = SDL_CreateRenderer(m_mainWindow, -1, SDL_RENDERER_PRESENTVSYNC);

    //Init nums
    M_DIGIT = loadTexture("Digits\\AllDigits", m_mainRenderer);
}


void Presenter::update() {
}

void Presenter::draw() {
    SDL_RenderPresent(m_mainRenderer);

    SDL_RenderClear(m_mainRenderer);
}

void Presenter::drawObject(SDL_Texture* texture) {
    SDL_RenderCopy(m_mainRenderer, texture, NULL, NULL);
}

void Presenter::drawNumber(int num, int2 stPoint, int2 digitSz) {
    if (num == 0) {
        SDL_Rect tempRect = { stPoint.x, stPoint.y, digitSz.x, digitSz.y };
        SDL_Rect digitRect = { 0, 0, m_digitRectSz.x, m_digitRectSz.y };
        SDL_RenderCopy(m_mainRenderer, M_DIGIT, &digitRect, &tempRect);
    }
    string temp;
    int i = 0;
    while (num > 0) {
        temp += char(num % 10 + '0');
        num /= 10;
        i++;
    }
    for (int j = 0; j < i; j++) {
        SDL_Rect tempRect = { stPoint.x + j * digitSz.x , stPoint.y, digitSz.x, digitSz.y };
        SDL_Rect digitRect = { m_digitRectSz.x * (temp[i - j - 1] - '0'), 0, m_digitRectSz.x, m_digitRectSz.y};
        SDL_RenderCopy(m_mainRenderer, M_DIGIT, &digitRect, &tempRect);
    }
}

void Presenter::drawObject(Drawable& drawable) {
    SDL_RenderCopy(m_mainRenderer, drawable.m_texture, NULL, &drawable.m_rect);
}