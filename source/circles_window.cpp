#include "circles_window.hpp"

#include "graphics.hpp"
#include "model.hpp"
#include <string>
#include "circle_editor_window.hpp"
#include <iostream>

Window::Event CirclesWindow::draw() {
    ImGui::Begin("Circles", &open);

    if (ImGui::Button("Create")) {
        graphics->circles.emplace_back(std::make_unique<Circle>(Vec(0, 0, 0), 0));
    }

    ImGui::Separator();

    for (int i = 0; i < int(graphics->circles.size()); i++)
        if (ImGui::Selectable(("Circle " + std::to_string(i + 1)).c_str())) {
            bool exists = false;
            for (const auto& window : graphics->circle_editors)
                if (window->circle_id == i && typeid(*window) == typeid(CircleEditorWindow)) {
                    exists = true;
                    break;
                }
            if (!exists)
                graphics->circle_editors.emplace_back(std::make_unique<CircleEditorWindow>(graphics, i))->open = true;
        }
        
    ImGui::End();
    return nullptr;
}