#pragma once

#include <string>
#include "ini_loader.hpp"
#include "../vendor/imgui/imgui.h"
#include "project.hpp"

#define COMPILE_SECTION_NAME "compile_conf"
#define COMPILER_NAME "compiler_name"
#define COMPILER_ARGS_FRONT "compiler_args_front"
#define COMPILER_ARGS_BACK "compiler_args_back"

#define RUN_SECTION_NAME "run_conf"
#define EXECUTABLE_NAME "executable_name"
#define RUN_DEFAULT_ARGS "default_args"

class Runner {
private:
    const std::string run_config = "compile_config";
    std::string path = "";
    IniLoader run_config_loader;
    bool show_config_editing = false;
    std::string output;
    bool show_output = false;

    std::string execute(std::string command) {
        char buffer[256];
        
        std::string result;

        FILE *pipe = popen(command.c_str(), "r");

        while(fgets(buffer, sizeof(buffer), pipe) != NULL) {
            result += buffer;
        }

        pclose(pipe);

        return result;
    }

    void show_comp_and_run_output() {
        if(show_output) {
            if(ImGui::Begin("Output", &show_output)) {
                ImGui::Text("%s", output.c_str());
            }
            
            ImGui::End();
        }
    }

    void config_editor() {
        if(show_config_editing) {
            if(ImGui::Begin("Compiler config editor", &show_config_editing)) {
                ImGui::Text("Path to compiler config file: %s.ini", (path + run_config).c_str());

                if(ImGui::CollapsingHeader("Compiler")) {
                    run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_NAME].value.resize(256);
                    ImGui::InputText("Compiler name", run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_NAME].value.data(), 256);
                    run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_NAME].value.erase(run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_NAME].value.begin() + 
                        run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_NAME].value.find_first_of((char)0), 
                        run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_NAME].value.end());

                    run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_FRONT].value.resize(1024);
                    ImGui::InputText("Compiler arguments front", run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_FRONT].value.data(), 1024);
                    run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_FRONT].value.erase(run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_FRONT].value.begin() + 
                        run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_FRONT].value.find_first_of((char)0), 
                        run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_FRONT].value.end());

                    run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_BACK].value.resize(1024);
                    ImGui::InputText("Compiler arguments back", run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_BACK].value.data(), 1024);
                    run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_BACK].value.erase(run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_BACK].value.begin() + 
                        run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_BACK].value.find_first_of((char)0), 
                        run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_BACK].value.end());

                    run_config_loader.sections[RUN_SECTION_NAME].vars[EXECUTABLE_NAME].value.resize(1024);
                    ImGui::InputText("Compiler executable name", run_config_loader.sections[RUN_SECTION_NAME].vars[EXECUTABLE_NAME].value.data(), 1024);
                    run_config_loader.sections[RUN_SECTION_NAME].vars[EXECUTABLE_NAME].value.erase(run_config_loader.sections[RUN_SECTION_NAME].vars[EXECUTABLE_NAME].value.begin() + 
                        run_config_loader.sections[RUN_SECTION_NAME].vars[EXECUTABLE_NAME].value.find_first_of((char)0), 
                        run_config_loader.sections[RUN_SECTION_NAME].vars[EXECUTABLE_NAME].value.end());
                }

                if(ImGui::CollapsingHeader("Runner")) {
                    run_config_loader.sections[RUN_SECTION_NAME].vars[RUN_DEFAULT_ARGS].value.resize(1024);
                    ImGui::InputText("Arguments passed while running app", run_config_loader.sections[RUN_SECTION_NAME].vars[RUN_DEFAULT_ARGS].value.data(), 1024);
                    run_config_loader.sections[RUN_SECTION_NAME].vars[RUN_DEFAULT_ARGS].value.erase(run_config_loader.sections[RUN_SECTION_NAME].vars[RUN_DEFAULT_ARGS].value.begin() + 
                        run_config_loader.sections[RUN_SECTION_NAME].vars[RUN_DEFAULT_ARGS].value.find_first_of((char)0), 
                        run_config_loader.sections[RUN_SECTION_NAME].vars[RUN_DEFAULT_ARGS].value.end());
                }

                if(ImGui::Button("Applay")) {
                    //run_config_loader.sections[RUN_SECTION_NAME].vars[EXECUTABLE_NAME].value.erase(run_config_loader.sections[RUN_SECTION_NAME].vars[EXECUTABLE_NAME].value.begin());
                    //run_config_loader.sections[RUN_SECTION_NAME].vars[RUN_DEFAULT_ARGS].value.erase(run_config_loader.sections[RUN_SECTION_NAME].vars[RUN_DEFAULT_ARGS].value.begin());
                    //run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_NAME].value.erase(run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_NAME].value.begin());
                    //run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_FRONT].value.erase(run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_FRONT].value.begin());
                    //run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_BACK].value.erase(run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_BACK].value.begin());

                    run_config_loader.sections[COMPILE_SECTION_NAME].name = COMPILE_SECTION_NAME;
                    run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_BACK].name = COMPILER_ARGS_BACK;
                    run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_FRONT].name = COMPILER_ARGS_FRONT;
                    run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_NAME].name = COMPILER_NAME;

                    run_config_loader.sections[RUN_SECTION_NAME].name = RUN_SECTION_NAME;
                    run_config_loader.sections[RUN_SECTION_NAME].vars[EXECUTABLE_NAME].name = EXECUTABLE_NAME;
                    run_config_loader.sections[RUN_SECTION_NAME].vars[RUN_DEFAULT_ARGS].name = RUN_DEFAULT_ARGS;

                    save_runner_config();
                    load_runner_config();

                    show_config_editing = false;
                }

                ImGui::SameLine();

                if(ImGui::Button("Restore")) {
                    load_runner_config();
                }

                ImGui::SameLine();

                if(ImGui::Button("Regenerate")) {
                    run_config_loader.sections.clear();
                    init_loader();
                    save_runner_config();
                }
            }
            
            ImGui::End();
        }
    }

public:
    Project *project;

    Runner() {

    }

    void pass_project(Project *pr) {
        project = pr;
    }

    void init_loader() {
        run_config_loader.add_section(COMPILE_SECTION_NAME);
        run_config_loader.add_section(RUN_SECTION_NAME);

        run_config_loader.add_var_to_section(COMPILE_SECTION_NAME, COMPILER_NAME, "");
        run_config_loader.add_var_to_section(COMPILE_SECTION_NAME, COMPILER_ARGS_FRONT, "");
        run_config_loader.add_var_to_section(COMPILE_SECTION_NAME, COMPILER_ARGS_BACK, "");

        run_config_loader.add_var_to_section(RUN_SECTION_NAME, EXECUTABLE_NAME, "");
        run_config_loader.add_var_to_section(RUN_SECTION_NAME, RUN_DEFAULT_ARGS, "");
    }

    void save_runner_config() {
        run_config_loader.save_ini(project->project_ini.sections[PR_SETT_SEC].vars[PR_PATH].value + "/" + run_config);
    }

    void load_runner_config() {
        run_config_loader.load_ini(project->project_ini.sections[PR_SETT_SEC].vars[PR_PATH].value + "/" + run_config);
    }

    void ShowRunner() {
        if(ImGui::Begin("##runner_win", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize)) {
            if(ImGui::Button("Run")) {
                show_output = true;

                output = execute((std::string("./") + project->project_ini.sections[PR_SETT_SEC].vars[PR_PATH].value + "/" + run_config_loader.sections[RUN_SECTION_NAME].vars[EXECUTABLE_NAME].value + std::string(" ") + run_config_loader.sections[RUN_SECTION_NAME].vars[RUN_DEFAULT_ARGS].value).c_str());
            }

            ImGui::SameLine();

            if(ImGui::Button("Compile")) {
                std::string prefix = ".c";

                if(project->project_ini.sections[PR_SETT_SEC].vars[PR_LANG].value == std::string(project_languages[0])) {
                    prefix = ".c";
                }
                else if(project->project_ini.sections[PR_SETT_SEC].vars[PR_LANG].value == std::string(project_languages[1])) {
                    prefix = ".cpp";
                }
                else if(project->project_ini.sections[PR_SETT_SEC].vars[PR_LANG].value == std::string(project_languages[2])) {
                    prefix = ".lua";
                }

                show_output = true;

                output = execute((run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_NAME].value + std::string(" ") + 
                    run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_FRONT].value + std::string(" ") + 
                    project->project_ini.sections[PR_SETT_SEC].vars[PR_PATH].value + "/" + 
                    run_config_loader.sections[RUN_SECTION_NAME].vars[EXECUTABLE_NAME].value  + std::string(" ") + 
                    project->project_ini.sections[PR_SETT_SEC].vars[PR_PATH].value + "/src/*" + prefix + " " +
                    run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_BACK].value).c_str());
            }

            ImGui::SameLine();

            if(ImGui::Button("Compile and run")) {
                std::string prefix = ".c";

                if(project->project_ini.sections[PR_SETT_SEC].vars[PR_LANG].value == std::string(project_languages[0])) {
                    prefix = ".c";
                }
                else if(project->project_ini.sections[PR_SETT_SEC].vars[PR_LANG].value == std::string(project_languages[1])) {
                    prefix = ".cpp";
                }
                else if(project->project_ini.sections[PR_SETT_SEC].vars[PR_LANG].value == std::string(project_languages[2])) {
                    prefix = ".lua";
                }

                show_output = true;

                output = execute((run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_NAME].value + std::string(" ") + 
                    run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_FRONT].value + std::string(" ") + 
                    project->project_ini.sections[PR_SETT_SEC].vars[PR_PATH].value + "/" +
                    run_config_loader.sections[RUN_SECTION_NAME].vars[EXECUTABLE_NAME].value  + std::string(" ") + 
                    project->project_ini.sections[PR_SETT_SEC].vars[PR_PATH].value + "/src/*" + prefix + " " +
                    run_config_loader.sections[COMPILE_SECTION_NAME].vars[COMPILER_ARGS_BACK].value).c_str());

                output += execute((std::string("./") + project->project_ini.sections[PR_SETT_SEC].vars[PR_PATH].value + "/" + run_config_loader.sections[RUN_SECTION_NAME].vars[EXECUTABLE_NAME].value + std::string(" ") + run_config_loader.sections[RUN_SECTION_NAME].vars[RUN_DEFAULT_ARGS].value).c_str());            }

            ImGui::SameLine();

            if(ImGui::Button("Edit config")) {
                show_config_editing = true;
            }
        }
        
        ImGui::End();

        config_editor();
        show_comp_and_run_output();
    }
};