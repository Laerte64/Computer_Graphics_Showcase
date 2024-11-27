#include "clipping_window.hpp"

#include "edge.hpp"
#include <algorithm>
#include "clipping.hpp"
#include "graphics.hpp"

ClippingWindow::Event ClippingWindow::draw() {
    ImGui::Begin("Clipping", &open);

    slider("X", Clipping::corners.first.x, Clipping::corners.second.x, -1, 1);
    slider("Y", Clipping::corners.first.y, Clipping::corners.second.y, -1, 1);
    slider("Z", Clipping::corners.first.z, Clipping::corners.second.z, 0, 1);

    ImGui::End();
    return nullptr;
}

void ClippingWindow::slider(const char *label, float &leftPoint, float &rightPoint, float minVal, float maxVal) {
    ImGui::Text("%s", label);

    leftPoint = std::clamp(leftPoint, minVal, rightPoint);
    rightPoint = std::clamp(rightPoint, leftPoint, maxVal);

    float sliderWidth = ImGui::GetContentRegionAvail().x;
    float sliderHeight = 20.0f;
    float handleRadius = 8.0f;

    ImVec2 sliderStart = ImGui::GetCursorScreenPos();
    ImVec2 sliderEnd = ImVec2(sliderStart.x + sliderWidth, sliderStart.y + sliderHeight);
    ImGui::GetWindowDrawList()->AddRectFilled(sliderStart, sliderEnd, ImGui::GetColorU32(ImGuiCol_FrameBg));

    float sliderRange = sliderEnd.x - sliderStart.x;
    float leftPointPos = sliderStart.x + (leftPoint - minVal) / (maxVal - minVal) * sliderRange;
    float rightPointPos = sliderStart.x + (rightPoint - minVal) / (maxVal - minVal) * sliderRange;

    char ID[3] = {label[0], '1', '\0'};
    ImVec2 leftHandlePos = ImVec2(leftPointPos, sliderStart.y + sliderHeight / 2);
    ImGui::GetWindowDrawList()->AddCircleFilled(leftHandlePos, handleRadius, ImGui::GetColorU32(ImGuiCol_SliderGrab));
    ImGui::SetCursorScreenPos(ImVec2(leftHandlePos.x - handleRadius, sliderStart.y));
    ImGui::InvisibleButton(ID, ImVec2(2 * handleRadius, sliderHeight));
    if (ImGui::IsItemActive()) {
        float newLeftPoint = (ImGui::GetIO().MousePos.x - sliderStart.x) / sliderRange * (maxVal - minVal) + minVal;
        leftPoint = std::clamp(newLeftPoint, minVal, rightPoint);
    }

    ID[1] = '2';
    ImVec2 rightHandlePos = ImVec2(rightPointPos, sliderStart.y + sliderHeight / 2);
    ImGui::GetWindowDrawList()->AddCircleFilled(rightHandlePos, handleRadius, ImGui::GetColorU32(ImGuiCol_SliderGrab));
    ImGui::SetCursorScreenPos(ImVec2(rightHandlePos.x - handleRadius, sliderStart.y));
    ImGui::InvisibleButton(ID, ImVec2(2 * handleRadius, sliderHeight));
    if (ImGui::IsItemActive()) {
        float newRightPoint = (ImGui::GetIO().MousePos.x - sliderStart.x) / sliderRange * (maxVal - minVal) + minVal;
        rightPoint = std::clamp(newRightPoint, leftPoint, maxVal);
    }

    ImGui::SetCursorScreenPos(ImVec2(sliderStart.x, sliderEnd.y + 5));
    ImGui::Text("Left: %.2f  Right: %.2f", leftPoint, rightPoint);
}