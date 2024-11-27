#pragma once

#include "model_editor_window.hpp"

class Model;

class ModelEdgesWindow : public ModelEditorWindow {
public:
    ModelEdgesWindow(Graphics* graphics, int model_id) : ModelEditorWindow(graphics, model_id) {}
    Window::Event draw() override;
};