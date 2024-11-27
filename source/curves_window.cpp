#include "curves_window.hpp"

#include "graphics.hpp"
#include "model.hpp"
#include <string>
#include "bezier.hpp"

Window::Event CurvesWindow::draw()
{
    ImGui::Begin("Curves", &open);

    if (ImGui::Button("Create")) {
        graphics->curves.emplace_back(std::make_unique<Bezier>(std::array<Vec, 4>{Vec(0, 0, 0), Vec(0, 0, 0), Vec(0, 0, 0), Vec(0, 0, 0)}));
    }

    ImGui::Separator();

    for (int i = 0; i < int(graphics->curves.size()); i++)
        if (ImGui::Selectable(("Curve " + std::to_string(i + 1)).c_str())) {
            bool exists = false;
            for (const auto& window : graphics->curve_editors)
                if (window->curve_id == i && typeid(*window) == typeid(CurveEditorWindow)) {
                    exists = true;
                    break;
                }
            if (!exists)
                graphics->curve_editors.emplace_back(std::make_unique<CurveEditorWindow>(graphics, i))->open = true;
        }

    ImGui::End();

    return nullptr;
}