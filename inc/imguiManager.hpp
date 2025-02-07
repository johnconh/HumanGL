#pragma once

#include <filesystem>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "animator.hpp"
#include "model.hpp"

class ImGuiManager {
    public:
        static void init(GLFWwindow* window);
        static void render(Animator& animator, Model& model);
        static void shutdown();
    private:
        static std::vector<std::string> getAnimationFiles(const std::string& path);
};