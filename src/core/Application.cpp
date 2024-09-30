/********************************************************************************
* @author: TURIING
* @email: turiing@163.com
* @date: 2024/9/13 23:26
* @version: 1.0
* @description: 
********************************************************************************/

#include "Application.h"
#include <GLFW/glfw3.h>
#include "../BaseDefine.h"
#include "Window.h"
#include "VkContext.h"

Application::Application() {
    m_window = std::make_shared<Window>(WINDOW_SIZE);
    m_vkContent = std::make_shared<VkContext>(m_window);
}

Application::~Application() {

}

void Application::run() {
    while (!glfwWindowShouldClose(m_window->GetHandle())) {
        glfwPollEvents();
        m_vkContent->DrawFrame();
    }
    m_vkContent->WaitIdle();
}


