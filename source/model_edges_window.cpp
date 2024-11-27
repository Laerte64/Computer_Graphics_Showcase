#include "model_edges_window.hpp"

#include <string>
#include "graphics.hpp"
#include "model.hpp"

Window::Event ModelEdgesWindow::draw()
{
    ImGui::Begin(("Model " + std::to_string(model_id + 1) + " Edges").c_str(), &open);

    auto& edges = model().edges;
    for (size_t i = 0; i < edges.size(); ++i) {
        ImGui::PushID(static_cast<int>(i));

        ImGui::Text("Edge %d", static_cast<int>(i + 1));
        ImGui::InputInt("V1", &edges[i].p1_index, 0, 0);
        ImGui::InputInt("V2", &edges[i].p2_index, 0, 0);

        float rgb[3] = {edges[i].color.r / 255.f, edges[i].color.g / 255.f, edges[i].color.b / 255.f};
        if (ImGui::ColorEdit3("Color", rgb, ImGuiColorEditFlags_Uint8)) {
            edges[i].color = {(unsigned char)(255 * rgb[0]), (unsigned char)(255 * rgb[1]), (unsigned char)(255 * rgb[2])};
        }

        if (ImGui::Button("Delete Edge")) 
            model().edges.erase(model().edges.begin() + i);
        ImGui::Separator();
        ImGui::PopID();
    }

    static int p1_index, p2_index;
    ImGui::InputInt("New V1", &p1_index, 0, 0);
    ImGui::InputInt("New V2", &p2_index, 0, 0);

    static SDL_Color color = {255, 255, 255};
    float rgb[3] = {color.r / 255.f, color.g / 255.f, color.b / 255.f};
    if (ImGui::ColorEdit3("New Color", rgb, ImGuiColorEditFlags_Uint8)) {
        color = {(unsigned char)(255 * rgb[0]), (unsigned char)(255 * rgb[1]), (unsigned char)(255 * rgb[2])};
    }

    if (ImGui::Button("Add Edge")) {
        model().edges.emplace_back(&model(), p1_index, p2_index, color);
    }

    ImGui::End();
    return nullptr;
}