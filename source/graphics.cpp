#include "graphics.hpp"

#include <SDL2/SDL_opengl.h>
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>
#include "edge.hpp"
#include <algorithm>

Graphics::Graphics()
    : camera(Vec(0, 0, -3), Vec(0, 0, 1), {{M_PI/4, 4.f/3.f, 0.1, 100.0}}), 
    window(nullptr), glContext(nullptr), 
    isRunning(true), printer(Edge::Bresenham),
    main_window(this), clipping_window(this),
    models_window(this), circles_window(this),
    curves_window(this) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        std::cerr << "SDL Init Error: " << SDL_GetError() << std::endl;
        isRunning = false;
        return;
    }

    window = SDL_CreateWindow("CG1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 
                              SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cerr << "Window Creation Error: " << SDL_GetError() << std::endl;
        isRunning = false;
        return;
    }

    SDL_MaximizeWindow(window);

    setupOpenGL();
    setupImGui();

    Model::cube(*models.emplace_back(std::make_unique<Model>()));
    Model::pyramid(*models.emplace_back(std::make_unique<Model>()));
    models[0]->transform(Vec(0, 0, 0), Matrix::translate(0.75, 0, 0));
    models[1]->transform(Vec(0, 0, 0), Matrix::translate(-0.75, 0, 0));

    circles.emplace_back(std::make_unique<Circle>(Vec(0, 0, 0.75), 0.5, Vec(0, 0, 1)));

}

Graphics::~Graphics() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graphics::setupOpenGL() {
    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cerr << "OpenGL Context Error: " << SDL_GetError() << std::endl;
        isRunning = false;
        return;
    }

    // Set basic OpenGL attributes if needed
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Initialize viewport and clear color
    glViewport(0, 0, width, height);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Graphics::setupImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Graphics::renderPixel(int x, int y, SDL_Color color) {
    glBegin(GL_POINTS);
    glColor3f(color.r / 255.f, color.g / 255.f, color.b / 255.f);
    glVertex2f((2.0f * x) / width - 1.0f, 1.0f - (2.0f * y) / height);
    glEnd();
}

void Graphics::delete_model(int id)
{
    for (int i = model_editors.size() - 1; i >= 0; i--)
        model_editors[i]->open &= model_editors[i]->model_id != id;
    for (const auto& window : model_editors)
        if (window->model_id > id)
            window->model_id--;
    models.erase(models.begin() + id);
}

void Graphics::delete_circle(int id) {
    for (int i = circle_editors.size() - 1; i >= 0; i--)
        circle_editors[i]->open &= circle_editors[i]->circle_id != id;
    for (const auto& window : circle_editors)
        if (window->circle_id > id)
            window->circle_id--;
    circles.erase(circles.begin() + id);
}

void Graphics::delete_curve(int id) {
    for (int i = curve_editors.size() - 1; i >= 0; i--)
        curve_editors[i]->open &= curve_editors[i]->curve_id != id;
    for (const auto& window : curve_editors)
        if (window->curve_id > id)
            window->curve_id--;
    curves.erase(curves.begin() + id);
}

void Graphics::input(SDL_Event event) {

}

void Graphics::update() {

}

void Graphics::movement(SDL_Event event)
{
    main_window.open |= event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE;

    static bool isDragging = false;
    static int lastMouseX = 0, lastMouseY = 0;
    bool isShiftPressed = (SDL_GetModState() & KMOD_SHIFT);

    if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
        isDragging = false;
    }

    if (event.type == SDL_MOUSEMOTION && isDragging) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        float deltaX = static_cast<float>(mouseX - lastMouseX);
        float deltaY = static_cast<float>(mouseY - lastMouseY);

        float sensitivity = 0.01f;
        camera.add_theta(-deltaX * sensitivity, isShiftPressed);
        camera.add_phi(-deltaY * sensitivity, isShiftPressed);

        lastMouseX = mouseX;
        lastMouseY = mouseY;
    }

    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT && !ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
        isDragging = true;
        SDL_GetMouseState(&lastMouseX, &lastMouseY);
    }

    if (event.type == SDL_MOUSEWHEEL && !ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
        camera.add_zoom(event.wheel.y);
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    Vec forward = (camera.orientation - camera.orientation * Vec(0, 1, 0) * Vec(0, 1, 0)).normal();
    Vec rightward = forward ^ Vec(0, 1, 0);
    Vec movement = Vec(0, 0, 0);

    if (state[SDL_SCANCODE_W]) {
        movement += forward;
    }
    if (state[SDL_SCANCODE_S]) {
        movement -= forward;
    }
    if (state[SDL_SCANCODE_A]) {
        movement -= rightward;
    }
    if (state[SDL_SCANCODE_D]) {
        movement += rightward;
    }
    if (movement.mag() > 0.1)
        movement = movement.normal();
    if (state[SDL_SCANCODE_SPACE]) {
        movement += Vec(0, 1, 0);
    }
    if (state[SDL_SCANCODE_LCTRL]) {
        movement.y *= -1;
    }

    float speed = 0.05;
    camera.pos += speed * movement;
}

void Graphics::operator()() {
    
    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) isRunning = false;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
                SDL_GetWindowSize(window, &width, &height);
                camera.aspect = static_cast<float>(width) / static_cast<float>(height);
                glViewport(0, 0, width, height);
            }
            movement(event);
            input(event);
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        if (main_window.open)
            main_window.draw();
        if (clipping_window.open)
            clipping_window.draw();
        if (models_window.open)
            models_window.draw();
        if (circles_window.open)
            circles_window.draw();
        if (curves_window.open)
            curves_window.draw();
        
        for (int i = model_editors.size() - 1; i >= 0; i--) {
            const auto& window = model_editors[i];
            if (window->open)
                window->draw();
            else
                model_editors.erase(model_editors.begin() + i);
        }
        for (int i = circle_editors.size() - 1; i >= 0; i--) {
            const auto& window = circle_editors[i];
            if (window->open)
                window->draw();
            else
                circle_editors.erase(circle_editors.begin() + i);
        }
        for (int i = curve_editors.size() - 1; i >= 0; i--) {
            const auto& window = curve_editors[i];
            if (window->open)
                window->draw();
            else
                curve_editors.erase(curve_editors.begin() + i);
        }
            
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        update();

        for (auto& model : models)
            model->draw(*this);
        for (auto& circle : circles)
            circle->draw(*this);
        for (auto& curve : curves) {
            curve->by_matrix(curve->div).draw(*this);
            if (curve->show_contr)
                curve->control(curve->color).draw(*this);
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }
}