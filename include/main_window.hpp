#pragma once

#include "window.hpp"

class MainWindow : public Window {
public:
    MainWindow(Graphics *graphics) : Window(graphics) {}
    Window::Event draw() override;

private:
    
};