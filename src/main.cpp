#include "window.hpp"
#include "runner.hpp"
#include "project.hpp"

class yace_window : public Window {
    virtual void Update() override;
    virtual void Start() override;
};

Project project;
Runner runner;

void yace_window::Start() {
    int w, h, x, y;
    glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &x, &y, &w, &h);

    glfwSetWindowSize(window, w, h);

    runner.pass_project(&project);

    runner.load_runner_config();
}

void yace_window::Update() {
    ImGui::BeginMainMenuBar();
    if(ImGui::BeginMenu("File")) {
        if(ImGui::MenuItem("Open")) {
            project.show_create_project = true;
        }

        if(ImGui::MenuItem("Open")) {
            project.show_open = true;
        }

        if(ImGui::MenuItem("Save")) {
            runner.save_runner_config();
            runner.load_runner_config();

            project.save_project();
        }

        if(ImGui::MenuItem("Exit")) { printf("User request exit!\n"); exit(0); }

        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();

    ImGui::ShowDemoWindow(nullptr);

    runner.ShowRunner();

    project.ShowOpenWindow();
    project.ShowCreateProject();
}

int main() {
    yace_window y_win;

    y_win.run();
}