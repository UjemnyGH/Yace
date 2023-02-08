#pragma once

#include "ini_loader.hpp"
#include "../vendor/imgui/imgui.h"
#include <cstring>
#define PR_SETT_SEC "project_settings"
#define PR_PATH "project_path"
#define PR_NAME "project_name"
#define PR_LANG "language"

#define PR_FILES_SEC "project_files"
#define PR_FILES_DONT_CARE_PREFIX "dont_care_"

const char *project_languages[] = {
    "C", "C++", "Lua"
};

const char *project_not_ignored_files[] = {
    ".c", 
    ".cpp", ".cc", ".cxx",
    ".lua",
};

enum ProjectType {
    c = 0,
    cpp = 1,
    lua = 2,
};

const char c_hello_world[] = "#include <stdio.h>\n\nint main(int argc, char **argv) {\n\tprintf(\"Hello world!\\n\");\n}\n";
const char cpp_hello_world[] = "#include <iostream>\n\nint main(int argc, char **argv) {\n\tstd::cout << \"Hello world!\" << std::endl;\n}\n";
const char lua_hello_world[] = "print(\"Hello world!\")";

class Project {
private:
    void create_c_project(std::string path, std::string project_name) {
        project_ini.sections.clear();

        project_ini.add_section(PR_SETT_SEC);
        project_ini.add_var_to_section(PR_SETT_SEC, PR_PATH, path + "/" + project_name);
        project_ini.add_var_to_section(PR_SETT_SEC, PR_NAME, project_name);
        project_ini.add_var_to_section(PR_SETT_SEC, PR_LANG, project_languages[0]);

        project_ini.add_section(PR_FILES_SEC);
        project_ini.add_var_to_section(PR_FILES_SEC, "main", "src/main.c");

        project_ini.save_ini(path + "/" + project_name + "/" + project_name);

        system(("mkdir " + path + "/" + project_name).c_str());
        system(("mkdir " + path + "/" + project_name + "/src").c_str());
        
        FILE* file = fopen((path + "/" + project_name + "/src/main.c").c_str(), "wb+");

        fwrite(c_hello_world, sizeof(char), strlen(c_hello_world), file);

        fclose(file);
    }

    void create_cpp_project(std::string path, std::string project_name) {
        project_ini.sections.clear();

        project_ini.add_section(PR_SETT_SEC);
        project_ini.add_var_to_section(PR_SETT_SEC, PR_PATH, path + "/" + project_name);
        project_ini.add_var_to_section(PR_SETT_SEC, PR_NAME, project_name);
        project_ini.add_var_to_section(PR_SETT_SEC, PR_LANG, project_languages[1]);

        project_ini.add_section(PR_FILES_SEC);
        project_ini.add_var_to_section(PR_FILES_SEC, "main", "src/main.cpp");

        project_ini.save_ini(path + "/" + project_name + "/" + project_name);

        system(("mkdir " + path + "/" + project_name).c_str());
        system(("mkdir " + path + "/" + project_name + "/src").c_str());
        
        FILE* file = fopen((path + "/" + project_name + "/src/main.cpp").c_str(), "wb+");

        fwrite(cpp_hello_world, sizeof(char), strlen(cpp_hello_world), file);

        fclose(file);
    }

    void create_lua_project(std::string path, std::string project_name) {
        project_ini.sections.clear();

        project_ini.add_section(PR_SETT_SEC);
        project_ini.add_var_to_section(PR_SETT_SEC, PR_PATH, path + "/" + project_name);
        project_ini.add_var_to_section(PR_SETT_SEC, PR_NAME, project_name);
        project_ini.add_var_to_section(PR_SETT_SEC, PR_LANG, project_languages[2]);

        project_ini.add_section(PR_FILES_SEC);
        project_ini.add_var_to_section(PR_FILES_SEC, "main", "src/main.lua");

        project_ini.save_ini(path + "/" + project_name + "/" + project_name);

        system(("mkdir " + path + "/" + project_name).c_str());
        system(("mkdir " + path + "/" + project_name + "/src").c_str());
        
        FILE* file = fopen((path + "/" + project_name + "/src/main.lua").c_str(), "wb+");

        fwrite(lua_hello_world, sizeof(char), strlen(lua_hello_world), file);

        fclose(file);
    }

public:
    IniLoader project_ini;
    ProjectType project_type;

    bool project_exist = false;

    bool show_open = false;
    bool show_create_project = false;

    std::string project_name_tmp;
    std::string project_path_tmp;

    Project() {
        project_ini.add_section(PR_SETT_SEC);
        project_ini.add_var_to_section(PR_SETT_SEC, PR_PATH, ".");
        project_ini.add_var_to_section(PR_SETT_SEC, PR_NAME, ".");
        project_ini.add_var_to_section(PR_SETT_SEC, PR_LANG, project_languages[0]);

        project_ini.add_section(PR_FILES_SEC);
        project_ini.add_var_to_section(PR_FILES_SEC, "", "");
    }

    void ShowOpenWindow() {
        if(show_open) {
            if(ImGui::Begin("Open project", &show_open)) {
                std::string open_path;

                open_path.resize(2048);

                if(ImGui::InputText("Path", open_path.data(), 2048, ImGuiInputTextFlags_EnterReturnsTrue)) {
                    open_path.erase(open_path.begin() + open_path.find_first_of((char)0), open_path.end());

                    load_project(open_path);
                }

                ImGui::End();
            }
        }
    }

    void ShowCreateProject() {
        if(show_create_project) {
            if(ImGui::Begin("Create project", &show_create_project)) {
                project_name_tmp.resize(2048);
                project_path_tmp.resize(2048);

                ImGui::InputText("Project name", project_name_tmp.data(), 2048);
                ImGui::InputText("Project path", project_path_tmp.data(), 2048);

                if(ImGui::BeginCombo("Language", project_languages[project_type])) {
                    for(int i = 0; i < 3; i++) {

                        const bool selected = (project_type == i);
                        if(ImGui::Selectable(project_languages[i], selected)) {
                            project_type = (ProjectType)i;
                        }

                        if(selected) {
                            ImGui::SetItemDefaultFocus();
                        }
                    }

                    ImGui::EndCombo();
                }

                if(ImGui::Button("Create project")) {
                    project_name_tmp.erase(project_name_tmp.begin() + project_name_tmp.find_first_of((char)0), project_name_tmp.end());
                    project_path_tmp.erase(project_path_tmp.begin() + project_path_tmp.find_first_of((char)0), project_path_tmp.end());

                    create_project(project_path_tmp, project_name_tmp, project_type);

                    show_create_project = false;
                }

                ImGui::End();
            }
        }
    }

    void load_project(std::string project_path) {
        project_exist = true;

        project_ini.load_ini(project_path);
    }

    void save_project() {
        std::string pr_path = project_ini.sections[PR_SETT_SEC].vars[PR_PATH].value;
        std::string pr_name = project_ini.sections[PR_SETT_SEC].vars[PR_NAME].value;

        project_ini.save_ini(pr_path + "/" + pr_name);
    }

    void create_project(std::string project_path, std::string project_name, ProjectType type) {
        project_exist = true;

        project_type = type;

        if(project_type == c) {
            create_c_project(project_path, project_name);
        }
        else if(project_type = cpp) {
            create_cpp_project(project_path, project_name);
        }
        else if(project_type == lua) {
            create_lua_project(project_path, project_name);
        }
    }

    void add_file_to_project(std::string file_name) {
        bool do_care = false;
        
        for(int i = 0; i < 5; i++) {
            if(file_name.find(project_not_ignored_files[i]) != -1) {
                do_care = true;
            }
        }

        if(do_care) {
            std::string name = file_name;

            int dot = name.find('.');

            name.erase(name.begin() + dot, name.end());

            project_ini.add_var_to_section(PR_FILES_SEC, name, "src/" + file_name);
        }
        else {
            std::string name = file_name;

            int dot = name.find('.');

            name.erase(name.begin() + dot, name.end());

            project_ini.add_var_to_section(PR_FILES_SEC, PR_FILES_DONT_CARE_PREFIX + name, "src/" + file_name);
        }

        fclose(fopen((project_ini.sections[PR_SETT_SEC].vars[PR_PATH].value + "/src/" + file_name).c_str(), "wb+"));
    }
};