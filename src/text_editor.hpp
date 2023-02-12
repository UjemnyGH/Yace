#pragma once

#include "../vendor/imgui/imgui.h"
#include "forced_aligment.hpp"
#include <string>
#include <fstream>

class TextEditor {
private:
    void InputTextMultilineColorCoded() {
        
    }

public:
    std::string code_buffer;
    std::string path;

    bool show_text_editor = false;
    bool *cmd_opened;

    void OpenFile(std::string file) {
        path = file;
        std::ifstream f(file, std::ios_base::binary | std::ios_base::ate);

        uint32_t length = f.tellg();

        f.seekg(0, std::ios_base::beg);

        code_buffer.clear();
        code_buffer.resize(length + (65535 * 255));

        f.read(code_buffer.data(), length);

        f.close();
    }

    void ShowTextEditor() {
        if(show_text_editor) {
            if(forced_aligment) {
                if(*cmd_opened) {
                    ImGuiViewport *vp = ImGui::GetMainViewport();
                    ImGui::SetNextWindowPos(ImVec2(vp->WorkPos.x + 324, vp->WorkPos.y));
                    ImGui::SetNextWindowSize(ImVec2(vp->WorkSize.x - 324, vp->WorkSize.y - 200));
                }
                else {
                    ImGuiViewport *vp = ImGui::GetMainViewport();
                    ImGui::SetNextWindowPos(ImVec2(vp->WorkPos.x + 324, vp->WorkPos.y));
                    ImGui::SetNextWindowSize(ImVec2(vp->WorkSize.x - 324, vp->WorkSize.y));
                }
            }

            if(ImGui::Begin("##text_editor", &show_text_editor, ImGuiWindowFlags_MenuBar)) {
                if(ImGui::BeginMenuBar()) {
                    if(ImGui::BeginMenu("File")) {
                        if(ImGui::MenuItem("Save")) {
                            code_buffer.erase(code_buffer.begin() + code_buffer.find_first_of((char)0), code_buffer.end());

                            std::ofstream fout(path, std::ios_base::binary);

                            fout.write(code_buffer.c_str(), code_buffer.size());

                            fout.close();

                            std::ifstream f(path, std::ios_base::binary | std::ios_base::ate);

                            uint32_t length = f.tellg();

                            f.seekg(0, std::ios_base::beg);

                            code_buffer.clear();
                            code_buffer.resize(length + (65535 * 255));

                            f.read(code_buffer.data(), length);

                            f.close();
                        }

                        ImGui::EndMenu();
                    }

                    ImGui::EndMenuBar();
                }

                ImGui::InputTextMultiline("##code_text_lines", code_buffer.data(), code_buffer.size(), ImVec2(ImGui::GetWindowSize().x, ImGui::GetWindowHeight() - 55), ImGuiInputTextFlags_AllowTabInput);
            }

            ImGui::End();
        }
    }
};