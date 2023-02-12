#pragma once

#include "../vendor/imgui/imgui.h"
#include "forced_aligment.hpp"
#include <string>
#include <iostream>
#include <cstdio>

class CommandLine {
private:
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

public:
    bool show_command_line = false;
    std::string command;
    std::string command_output;

    void ShowCommandLine() {
        if(show_command_line) {
            if(forced_aligment) {
                ImGuiViewport *vp = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(ImVec2(vp->WorkPos.x + 324, vp->Size.y - 200));
                ImGui::SetNextWindowSize(ImVec2(vp->WorkSize.x - 324, 200));
            }

            if(ImGui::Begin("Command line", &show_command_line)) {
                command.resize(2048);

                const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
                if(ImGui::BeginChild("##cmd_output", ImVec2(0, -footer_height_to_reserve), true, ImGuiWindowFlags_HorizontalScrollbar)) {
                    ImGui::Text("%s", command_output.c_str());
                }

                ImGui::EndChild();

                ImGui::Separator();

                if(ImGui::InputText("##cmd", command.data(), 2048, ImGuiInputTextFlags_EnterReturnsTrue)) {
                    command.erase(command.begin() + command.find_first_of((char)0), command.end());

                    command_output += execute(command);
                    command_output += "\n";

                    command.clear();

                    ImGui::SetItemDefaultFocus();

                    ImGui::SetKeyboardFocusHere(-1);
                }
            }

            ImGui::End();
        }
    }
};