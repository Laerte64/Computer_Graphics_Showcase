#include "model_editor_window.hpp"

#include "graphics.hpp"
#include "model.hpp"
#include <string>
#include "model_vertex_window.hpp"
#include "model_edges_window.hpp"

Window::Event ModelEditorWindow::draw() {
    ImGui::Begin(("Model " + std::to_string(model_id + 1) + " Editor").c_str(), &open);

    if (ImGui::Button("Vertices")) {
        bool exists = false;
        for (const auto& window : graphics->model_editors)
            if (window->model_id == model_id && typeid(*window) == typeid(ModelVertexWindow)) {
                exists = true;
                break;
            }
        if (!exists)
            graphics->model_editors.emplace_back(std::make_unique<ModelVertexWindow>(graphics, model_id))->open = true;
    }
    if (ImGui::Button("Edges")) {
        bool exists = false;
        for (const auto& window : graphics->model_editors)
            if (window->model_id == model_id && typeid(*window) == typeid(ModelEdgesWindow)) {
                exists = true;
                break;
            }
        if (!exists)
            graphics->model_editors.emplace_back(std::make_unique<ModelEdgesWindow>(graphics, model_id))->open = true;
    }

    ImGui::Separator();

    {
        ImGui::PushID(0);
        ImGui::Text("Rotation Options");

        static float angle = 0;
        ImGui::InputFloat("Angle", &angle);

        const char* axis[] = {"X", "Y", "Z"};
        static int axis_selected = 0;
        ImGui::Combo("Axis", &axis_selected, axis, IM_ARRAYSIZE(axis));

        const char* points[] = {"Origin", "Model Center"};
        static int point_selected = 0;
        ImGui::Combo("Point", &point_selected, points, IM_ARRAYSIZE(points));

        if (ImGui::Button("Apply")) {
            Vec point = 
                point_selected == 0 ?
                Vec(0, 0, 0) :
                model().mid_point();

            Matrix transf = 
                axis_selected == 0 ?
                Matrix::rotateX(angle) :
                axis_selected == 1 ?
                Matrix::rotateY(angle) :
                Matrix::rotateZ(angle);

            model().transform(point, transf);

            angle = 0;
        }

        ImGui::PopID();
    }

    ImGui::Separator();

    {
        ImGui::PushID(1);
        ImGui::Text("Translation Options");

        static float X = 0, Y = 0, Z = 0;
        ImGui::InputFloat("X", &X);
        ImGui::InputFloat("Y", &Y);
        ImGui::InputFloat("Z", &Z);

        if (ImGui::Button("Apply")) {
            model().transform(Vec(0, 0, 0), Matrix::translate(X, Y, Z));
            X = Y = Z = 0;
        }
        ImGui::PopID();
    }
    
    ImGui::Separator();

    {
        ImGui::PushID(2);
        ImGui::Text("Scaling Options");

        static float X = 1, Y = 1, Z = 1;
        ImGui::InputFloat("X", &X);
        ImGui::InputFloat("Y", &Y);
        ImGui::InputFloat("Z", &Z);

        const char* points[] = {"Origin", "Model Center"};
        static int point_selected = 0;
        ImGui::Combo("Point", &point_selected, points, IM_ARRAYSIZE(points));

        if (ImGui::Button("Apply")) {
            Vec point = 
                point_selected == 0 ?
                Vec(0, 0, 0) :
                model().mid_point();

            model().transform(point, Matrix::scale(X, Y, Z));
            X = Y = Z = 1;
        }
        ImGui::PopID();
    }

    ImGui::Separator();

    if (ImGui::Button("Delete")) {
        graphics->delete_model(model_id);
    }

    ImGui::End();
    return nullptr;
}

Model& ModelEditorWindow::model()
{
    return *graphics->models[model_id];
}
