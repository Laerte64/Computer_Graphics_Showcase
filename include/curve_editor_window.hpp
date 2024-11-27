#pragma once

#include "window.hpp"

class Curve;

class CurveEditorWindow : public Window {
public:
    int curve_id;
    CurveEditorWindow(Graphics* graphics, int curve_id) : Window(graphics), curve_id(curve_id) {}
    Window::Event draw() override;
    Curve& curve();
};