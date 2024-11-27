#pragma once

class Graphics;

class Window {
public:
    typedef void* (*Event)(Graphics *graphics);

    Graphics *graphics;
    bool open;

    Window(Graphics *graphics) : graphics(graphics), open(false) {}
    virtual Event draw() = 0;
};