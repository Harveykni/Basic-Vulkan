#include <SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    // init SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Create SDL window with Vulkan flag
    SDL_Window* window = SDL_CreateWindow("Vulkan Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Get Vulkan extensions required by SDL
    unsigned int extensionCount = 0;
    if (!SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, nullptr)) {
        std::cerr << "Failed to get Vulkan extension count from SDL" << std::endl;
        return -1;
    }

    std::vector<const char*> extensions(extensionCount);
    if (!SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, extensions.data())) {
        std::cerr << "Failed to get Vulkan extensions from SDL" << std::endl;
        return -1;
    }

    // Create Vulkan instance
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "SDL2 Vulkan Example";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkInstance instance;
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        std::cerr << "Failed to create Vulkan instance" << std::endl;
        return -1;
    }

    // Main loop
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // <-- Insert rendering here
    }

    // Cleanup
    vkDestroyInstance(instance, nullptr);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
