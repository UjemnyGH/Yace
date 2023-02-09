#pragma once

#include "../vendor/imgui/imgui.h"
#include "project.hpp"

class FileExplorer {
private:

public:
    std::string opened_file;
    bool show_file_explorer = true;
    Project *project;

    void ShowFiles() {
        if(show_file_explorer) {
            if(ImGui::Begin("File Explorer", &show_file_explorer)) {
                for(auto file : project->project_ini.sections[PR_FILES_SEC].vars) {
                    bool selected = false;
                    if(file.second.value.size() > 1) {
                        ImGui::Selectable(file.second.value.c_str(), &selected);
                    }

                    if(selected) {
                        opened_file = file.second.value;
                        
                    }
                }

                if(ImGui::BeginPopupContextWindow("##file_explorer_popup")) {
                    if(ImGui::Selectable("Add file")) { 
                        project->show_add_file = true; 
                    }

                    ImGui::EndPopup();
                }

                ImGui::End();
            }

            project->add_file_menu();
        }
    }
};