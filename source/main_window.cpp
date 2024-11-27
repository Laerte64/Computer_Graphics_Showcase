#include "main_window.hpp"

#include "graphics.hpp"
#include "edge.hpp"

MainWindow::Event MainWindow::draw() {
    ImGui::Begin("Main", &open);

    const char* alg_names[] = { "DDA", "Bresenham"};
    static int selected_edge_alg = 0; 
    if (ImGui::Combo("Select an Line Algorithm", &selected_edge_alg, alg_names, IM_ARRAYSIZE(alg_names))) {
        switch (selected_edge_alg)
        {
        case 0: graphics->printer = Edge::DDA; break;
        case 1: graphics->printer = Edge::Bresenham; break;
        }
    }

    graphics->clipping_window.open |= ImGui::Button("Clipping");
    graphics->models_window.open |= ImGui::Button("Models");
    graphics->circles_window.open |= ImGui::Button("Circles");
    graphics->curves_window.open |= ImGui::Button("Curves");

    ImGui::End();
    return nullptr;
}