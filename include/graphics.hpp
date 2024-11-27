#pragma once

class Graphics;
#include <SDL2/SDL.h>
#include <vector>
#include "camera.hpp"
#include "main_window.hpp"
#include "clipping_window.hpp"
#include "models_window.hpp"
#include "model_editor_window.hpp"
#include "circles_window.hpp"
#include "circle.hpp"
#include "circle_editor_window.hpp"
#include "curves_window.hpp"
#include "curve.hpp"
#include "curve_editor_window.hpp"
#include <memory>

class Graphics {
public:
    Graphics();
    ~Graphics();
    void operator() ();
    void renderPixel(int x, int y, SDL_Color color);
    Camera camera;
    int width, height;

protected:
    virtual void input(SDL_Event event);
    virtual void update();
    SDL_Window* window;
    SDL_GLContext glContext;
    bool isRunning;

public:
    void (*printer)(Graphics &graphics, Vec p1, Vec p2, SDL_Color);

    std::vector<std::unique_ptr<Model>> models;
    void delete_model(int id);

    std::vector<std::unique_ptr<Circle>> circles;
    void delete_circle(int id);

    std::vector<std::unique_ptr<Curve>> curves;
    void delete_curve(int id);

    MainWindow main_window;
    ClippingWindow clipping_window;
    ModelsWindow models_window;
    CirclesWindow circles_window;
    CurvesWindow curves_window;

    std::vector<std::unique_ptr<ModelEditorWindow>> model_editors; 
    std::vector<std::unique_ptr<CircleEditorWindow>> circle_editors; 
    std::vector<std::unique_ptr<CurveEditorWindow>> curve_editors; 

private:
    void movement(SDL_Event event);
    void setupOpenGL();
    void setupImGui();
};