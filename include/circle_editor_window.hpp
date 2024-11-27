#pragma once

#include "window.hpp"

class Circle;

class CircleEditorWindow : public Window {
public:
    int circle_id;
    CircleEditorWindow(Graphics* graphics, int circle_id) : Window(graphics), circle_id(circle_id) {}
    virtual Window::Event draw() override;
    Circle& circle();
};