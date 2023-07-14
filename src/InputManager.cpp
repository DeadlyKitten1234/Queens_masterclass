#include "InputManager.h"

InputManager::InputManager() {}

InputManager::~InputManager() {}

void InputManager::getInput() {
    m_mouseIsPressed = false;
    m_mouseMoved = false;
    m_mouseButtonReleased = false;
    m_keyReleased = false;
    SDL_Event m_event;
    while (SDL_PollEvent(&m_event)) {
        switch (m_event.type) {
        case SDL_QUIT:
            m_quit = true;
            break;

        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&(m_mouseCoord.x), &(m_mouseCoord.y));
            m_mouseMoved = true;
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (m_event.button.button == SDL_BUTTON_LEFT){
                m_mouseIsPressed = true;
                m_mouseIsHeld = true;
            }
            break;
            
        case SDL_MOUSEBUTTONUP:
            if (m_event.button.button == SDL_BUTTON_LEFT) {
                m_mouseButtonReleased = true;
                m_mouseIsHeld = false;
            }
            break;
        case SDL_KEYUP:
            m_keyReleased = true;
            break;
        }
    }
}
