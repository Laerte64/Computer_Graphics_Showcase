#pragma once

#include "window.hpp"

class CurvesWindow : public Window {
public:
    CurvesWindow(Graphics* graphics) : Window(graphics) {}
    Window::Event draw() override;
};