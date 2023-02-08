#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
//#include "../vendor/imgui/imgui_impl_opengl3_loader.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"
#include <GL/gl.h>

class Window {
public:
    GLFWwindow* window;

    void run() {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(800, 600, "Yace", nullptr, nullptr);

        if(!window) {
            printf("Cannot create window!\n");

            exit(1);
        }

        glfwMakeContextCurrent(window);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 430 core");

        Start();

        while(!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            Update();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwPollEvents();

            glfwSwapBuffers(window);
        }

        glfwTerminate();
    }

    virtual void Update() {}
    virtual void Start() {}

    ~Window() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
};