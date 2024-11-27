#include "models_window.hpp"

#include "graphics.hpp"
#include "model.hpp"
#include <string>

Window::Event ModelsWindow::draw()
{
    ImGui::Begin("Models", &open);

    if (ImGui::Button("Create")) {
        graphics->models.emplace_back(std::make_unique<Model>());
    }

    ImGui::Separator();

    
    for (int i = 0; i < int(graphics->models.size()); i++)
        if (ImGui::Selectable(("Model " + std::to_string(i + 1)).c_str())) {
            bool exists = false;
            for (const auto& window : graphics->model_editors)
                if (window->model_id == i && typeid(*window) == typeid(ModelEditorWindow)) {
                    exists = true;
                    break;
                }
            if (!exists)
                graphics->model_editors.emplace_back(std::make_unique<ModelEditorWindow>(graphics, i))->open = true;
        }

    ImGui::End();
    return nullptr;
}