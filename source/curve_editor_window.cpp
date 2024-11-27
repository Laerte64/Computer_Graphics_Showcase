#include "curve_editor_window.hpp"

#include "graphics.hpp"
#include "curve.hpp"
#include "bezier.hpp"
#include "hermit.hpp"
#include "b_spline.hpp"
#include <string>

Window::Event CurveEditorWindow::draw() {
    ImGui::Begin(("Curve " + std::to_string(curve_id + 1) + " Editor").c_str(), &open);

    ImGui::Checkbox("Show Points", &curve().show_contr);

    float rgb[3] = {curve().color.r / 255.f, curve().color.g / 255.f, curve().color.b / 255.f};
    if (ImGui::ColorEdit3("Color", rgb, ImGuiColorEditFlags_Uint8)) {
        curve().color = {(unsigned char)(255 * rgb[0]), (unsigned char)(255 * rgb[1]), (unsigned char)(255 * rgb[2])};
    }

    ImGui::Separator();

    const char * types[] = {"Bezier", "Hermit", "B Spline"};
    static int type_selected =
        typeid(curve()) == typeid(Bezier) ?
        0 :
        typeid(curve()) == typeid(Hermit) ? 
        1 :
        2;
    if (ImGui::Combo("Type", &type_selected, types, IM_ARRAYSIZE(types))) {
        switch (type_selected)
        {
        case 0:
            graphics->curves[curve_id] = std::make_unique<Bezier>(curve().points, curve().color);
            break;
        case 1:
            graphics->curves[curve_id] = std::make_unique<Hermit>(curve().points, curve().color);
            break;
        case 2:
            graphics->curves[curve_id] = std::make_unique<BSpline>(curve().points, curve().color);
            break;
        }
    }



    ImGui::Separator();

    int i = 0;
    for (auto& point : curve().points) {
        ImGui::PushID(i++);
        ImGui::Text("Point %d", i);
        ImGui::InputFloat("X", &point.x);
        ImGui::InputFloat("Y", &point.y);
        ImGui::InputFloat("Z", &point.z);
        ImGui::PopID();
        ImGui::Separator();
    }
    
    if (ImGui::Button("Delete")) {
        graphics->delete_curve(curve_id);
    }

    ImGui::End();
    return nullptr;
}

Curve &CurveEditorWindow::curve() {
    return *graphics->curves[curve_id];
}
