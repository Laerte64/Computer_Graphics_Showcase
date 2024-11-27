#pragma once

#include "window.hpp"

class ClippingWindow : public Window {
public:
    ClippingWindow(Graphics *graphics) : Window(graphics) {}
    Event draw() override;

private:
    static void slider(const char* label, float& leftPoint, float& rightPoint, float minVal, float maxVal);
};