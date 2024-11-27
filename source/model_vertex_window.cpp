#include "model_vertex_window.hpp"

#include "graphics.hpp"
#include "model.hpp"
#include <string>

Window::Event ModelVertexWindow::draw()
{
    ImGui::Begin(("Model " + std::to_string(model_id + 1) + " Vertices").c_str(), &open);

    auto& vertices = model().points;
    for (size_t i = 0; i < vertices.size(); ++i) {
        ImGui::PushID(static_cast<int>(i));

        if (!vertices[i].has_value()) {
            ImGui::Separator();
            ImGui::PopID();
            continue;
        }

        ImGui::Text("Vertex %d", static_cast<int>(i + 1));
        ImGui::InputFloat("X", &vertices[i].value().x);
        ImGui::InputFloat("Y", &vertices[i].value().y);
        ImGui::InputFloat("Z", &vertices[i].value().z);

        if (ImGui::Button("Delete Vertex")) 
            model().removePoint(i);
        ImGui::Separator();
        ImGui::PopID();
    }

    static float newX = 0.0f, newY = 0.0f, newZ = 0.0f;
    ImGui::InputFloat("New X", &newX);
    ImGui::InputFloat("New Y", &newY);
    ImGui::InputFloat("New Z", &newZ);

    if (ImGui::Button("Add Vertex")) {
        model().addPoint(Vec(newX, newY, newZ));
        newX = newY = newZ = 0.0f;
    }

    ImGui::End();
    return nullptr;
}