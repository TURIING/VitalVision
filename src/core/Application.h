/********************************************************************************
* @author: TURIING
* @email: turiing@163.com
* @date: 2024/9/13 23:26
* @version: 1.0
* @description: 
********************************************************************************/

#ifndef VULKAN_START_APPLICATION_H
#define VULKAN_START_APPLICATION_H

#include <memory>

class Window;
class VkContext;

class Application {
public:
    Application();
    ~Application();
    void run();

private:
    std::shared_ptr<VkContext> m_vkContent = nullptr;
    std::shared_ptr<Window> m_window = nullptr;
};


#endif //VULKAN_START_APPLICATION_H
