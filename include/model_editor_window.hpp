#pragma once

#include "window.hpp"

class Model;

class ModelEditorWindow : public Window {
public:
    int model_id;
    ModelEditorWindow(Graphics* graphics, int model_id) : Window(graphics), model_id(model_id) {}
    virtual Window::Event draw() override;
    Model& model();
};