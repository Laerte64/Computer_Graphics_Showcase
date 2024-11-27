#include "circle_editor_window.hpp"

#include "graphics.hpp"
#include <string>

Window::Event CircleEditorWindow::draw() {
    ImGui::Begin(("Circle " + std::to_string(circle_id + 1) + " Editor").c_str(), &open);

    ImGui::InputInt("Division", &circle().divisions, 0);
    ImGui::InputFloat("Radius", &circle().radius);

    ImGui::Separator();

    ImGui::PushID(0);
    ImGui::Text("Center");
    ImGui::InputFloat("X", &circle().center.x);
    ImGui::InputFloat("Y", &circle().center.y);
    ImGui::InputFloat("Z", &circle().center.z);
    ImGui::PopID();

    ImGui::Separator();

    if (!circle().direction.has_value())
        circle().direction = Vec(1, 0, 0);

    ImGui::PushID(1);

    static Vec dir = circle().direction.value();
    ImGui::Text("Direction");
    
    ImGui::Checkbox("Show Direction", &circle().show_dir);

    ImGui::InputFloat("X", &dir.x);
    ImGui::InputFloat("Y", &dir.y);
    ImGui::InputFloat("Z", &dir.z);
    ImGui::PopID();

    if (ImGui::Button("Apply"))
        circle().direction = dir = dir.normal();
    ImGui::SameLine();
    if (ImGui::Button("Cancel"))
        dir = circle().direction.value();

    ImGui::Separator();

    float rgb[3] = {circle().color.r / 255.f, circle().color.g / 255.f, circle().color.b / 255.f};
    if (ImGui::ColorEdit3("Color", rgb, ImGuiColorEditFlags_Uint8)) {
        circle().color = {(unsigned char)(255 * rgb[0]), (unsigned char)(255 * rgb[1]), (unsigned char)(255 * rgb[2])};
    }

    if (ImGui::Button("Delete")) {
        graphics->delete_circle(circle_id);
    }

    ImGui::End();
    return nullptr;
}

Circle &CircleEditorWindow::circle() {
    return *graphics->circles[circle_id];
}
