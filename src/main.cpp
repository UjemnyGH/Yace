#include "window.hpp"
#include "runner.hpp"
#include "project.hpp"
#include "file_explorer.hpp"
#include "command_line.hpp"
#include "text_editor.hpp"

class yace_window : public Window {
    virtual void Update() override;
    virtual void Start() override;
};

Project project;
Runner runner;
FileExplorer file_explorer;
CommandLine command_line;
TextEditor text_editor;

void yace_window::Start() {
    int w, h, x, y;
    glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &x, &y, &w, &h);

    glfwSetWindowSize(window, w, h);

    runner.pass_project(&project);
    file_explorer.project = &project;
}

void yace_window::Update() {
    ImGui::BeginMainMenuBar();
    if(ImGui::BeginMenu("File")) {
        if(ImGui::MenuItem("Create new")) {
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

    if(ImGui::BeginMenu("View")) {
        ImGui::MenuItem("File explorer", "", &file_explorer.show_file_explorer);
        ImGui::MenuItem("Command line", "", &command_line.show_command_line);
        ImGui::MenuItem("Text editor", "", &text_editor.show_text_editor);

        ImGui::EndMenu();
    }

    if(project.project_ini.sections[PR_SETT_SEC].vars[PR_PATH].value + "/" + file_explorer.opened_file != text_editor.path) {
        text_editor.OpenFile(project.project_ini.sections[PR_SETT_SEC].vars[PR_PATH].value + "/" + file_explorer.opened_file);
    }

    ImGui::EndMainMenuBar();

    ImGui::ShowDemoWindow(nullptr);

    if(!file_explorer.opened_file.empty()) {
        text_editor.show_text_editor = true;
    }

    runner.ShowRunner();
    project.ShowOpenWindow();
    project.ShowCreateProject();
    file_explorer.ShowFiles();
    command_line.ShowCommandLine();
    text_editor.ShowTextEditor();
}

int main() {
    yace_window y_win;

    y_win.run();
}