#pragma once

#include "window.hpp"

class CirclesWindow : public Window {
public:
    CirclesWindow(Graphics* graphics) : Window(graphics) {}
    Window::Event draw() override;
};