#pragma once

#include "../vendor/imgui/imgui.h"
#include "project.hpp"
#include "forced_aligment.hpp"
#include <algorithm>

class FileExplorer {
private:

public:
    //std::vector<std::string> opened_file;
    std::string opened_file;
    bool show_file_explorer = true;
    Project *project;

    void ShowFiles() {
        if(show_file_explorer) {
            if(forced_aligment) {
                ImGuiViewport *vp = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(ImVec2(0, vp->WorkPos.y + 35));
                ImGui::SetNextWindowSize(ImVec2(324, vp->WorkSize.y - 35));
            }
            
            if(ImGui::Begin("File Explorer", &show_file_explorer)) {
                for(auto file : project->project_ini.sections[PR_FILES_SEC].vars) {
                    bool selected = false;
                    if(file.second.value.size() > 1) {
                        ImGui::Selectable(file.second.value.c_str(), &selected);
                    }

                    if(selected && !file.second.value.empty()) {
                        opened_file = file.second.value;
                    }

                    /*auto iter = std::find(opened_file.begin(), opened_file.end(), file.second.value);

                    if(selected && *iter == (char*)((void*)0)) {
                        opened_file.push_back(file.second.value);
                    }*/
                }

                if(ImGui::BeginPopupContextWindow("##file_explorer_popup")) {
                    if(ImGui::Selectable("Add file")) { 
                        project->show_add_file = true; 
                    }

                    ImGui::EndPopup();
                }
            }

            ImGui::End();

            project->add_file_menu();
        }
    }
};