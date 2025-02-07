#include "../inc/imguiManager.hpp"

void ImGuiManager::init(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void ImGuiManager::render(Animator& animator, Model& model, float deltaTime) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //ImGui::Text("Selected: %s", animationFiles[selectedIndex].c_str());
    static std::vector<std::string> animationFiles = getAnimationFiles("resources/animation");
    static int selectedIndex = 2;

    ImGui::Begin("Animation Selector");

    if(ImGui::BeginCombo("Select Animations", animationFiles[selectedIndex].c_str())) {
        for(std::vector<std::string>::size_type i = 0; i < animationFiles.size(); i++) {
            bool isSelected = (selectedIndex == static_cast<int>(i));
            if(ImGui::Selectable(animationFiles[i].c_str(), isSelected)) {
                selectedIndex = i;

                std::string newAnimationPath = "resources/animation/" + animationFiles[i];
                Animation* newAnimation = new Animation(newAnimationPath, &model);
                animator.PlayAnimation(newAnimation); 
            }
        }
        ImGui::EndCombo();
    }

    //ImGui::Text("Animation Time: %f", animationTime);
    static bool isPaused = false;
    static float animationTime = 0.0f;

    if(ImGui::Button(isPaused ? "Play" : "Pause")) {
        isPaused = !isPaused;
        animator.setPause(isPaused);
    }

    ImGui::SameLine();

    if(ImGui::SliderFloat("Time", &animationTime, 0.0f, animator.getDuration())) {
        if(isPaused) {
            animator.setCurrentTime(animationTime);
        }
    }

    if(!isPaused) {
        animationTime += deltaTime  * animator.getTicksPerSecond();
        animationTime = fmod(animationTime, animator.getDuration());
        animator.setCurrentTime(animationTime);
    }

    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());  
}

void ImGuiManager::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

std::vector<std::string> ImGuiManager::getAnimationFiles(const std::string& path) {
    std::vector<std::string> files;
    try {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            if (entry.is_regular_file() && entry.path().extension() == ".dae") {
                files.push_back(entry.path().filename().string());
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error accessing animation directory: " << e.what() << std::endl;
    }

    return files;
}