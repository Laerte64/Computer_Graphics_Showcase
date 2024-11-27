#pragma once

#include "window.hpp"

class ModelsWindow : public Window {
public:
    ModelsWindow(Graphics* graphics) : Window(graphics) {}
    Window::Event draw() override;
};