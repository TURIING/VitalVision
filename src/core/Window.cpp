/********************************************************************************
* @author: TURIING
* @email: turiing@163.com
* @date: 2024/9/13 23:30
* @version: 1.0
* @description: 
********************************************************************************/

#include "Window.h"
#include <glog/logging.h>

Window::Window(Size size): m_size(size) {
    this->init();
}

void Window::init() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    m_window = glfwCreateWindow(m_size.width, m_size.height, "Vulkan demo", nullptr, nullptr);
    LOG_ASSERT(google::FATAL) << "Failed to create window!";
}

GLFWwindow *Window::GetHandle() {
    LOG_ASSERT(m_window != nullptr);
    return m_window;
}

Window::~Window() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

std::vector<const char*> Window::GetGlfwExtensionInfo() const {
    unsigned int extCount = 0;
    const char **extName = glfwGetRequiredInstanceExtensions(&extCount);
    return std::vector<const char*> {extName, extName + extCount};
}

void Window::CreateWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
    const auto result = glfwCreateWindowSurface(instance, m_window, nullptr, surface);
    LOG_IF(ERROR, result != VK_SUCCESS) << "Failed to create window surface!";
}

Size Window::GetFrameBufferSize() {
    int32_t width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
    return Size{ width, height };
}
