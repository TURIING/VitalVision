/********************************************************************************
* @author: TURIING
* @email: turiing@163.com
* @date: 2024/9/13 23:30
* @version: 1.0
* @description: 
********************************************************************************/

#ifndef VULKAN_START_WINDOW_H
#define VULKAN_START_WINDOW_H

#include <vector>
#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "../BaseDefine.h"
struct GLFWwindow;



class Window {
public:
    explicit Window(Size size);
    ~Window();
    GLFWwindow *GetHandle();
    [[nodiscard]] std::vector<const char*> GetGlfwExtensionInfo() const;
    void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
    [[nodiscard]] Size GetFrameBufferSize();

private:
    void init();

private:
    Size m_size;
    GLFWwindow *m_window = nullptr;
};


#endif //VULKAN_START_WINDOW_H
