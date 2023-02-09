#pragma once

#include "../vendor/imgui/imgui.h"
#include <string>
#include <fstream>

class TextEditor {
private:

public:
    std::string code_buffer;
    std::string path;

    bool show_text_editor = false;

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
            if(ImGui::Begin("Text editor", &show_text_editor, ImGuiWindowFlags_MenuBar)) {
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

                ImGui::InputTextMultiline("##", code_buffer.data(), code_buffer.size(), ImVec2(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y - 55.0f), ImGuiInputTextFlags_AllowTabInput);
            }

            ImGui::End();
        }
    }
};