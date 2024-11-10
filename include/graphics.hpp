#pragma once

#include <SDL2/SDL.h>
#include "camera.hpp"

class Graphics {
public:
    Graphics();
    ~Graphics();
    void operator() ();
    void renderPixel(int x, int y, float r, float g, float b);
    Camera camera;
    int width, height;

protected:
    virtual void update() = 0;
    SDL_Window* window;
    SDL_GLContext glContext;
    bool isRunning;

private:
    void setupOpenGL();
    void setupImGui();
};