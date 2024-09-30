/********************************************************************************
* @author: TURIING
* @email: turiing@163.com
* @date: 2024/9/14 0:00
* @version: 1.0
* @description: 
********************************************************************************/

#ifndef VULKAN_START_VKCONTEXT_H
#define VULKAN_START_VKCONTEXT_H

#include <vector>
#include <memory>
#include <vulkan/vulkan.h>
#include "../BaseDefine.h"


struct QueueFamilyIndices;
struct SwapChainSupportDetails;
class Window;

class VkContext {
public:
    explicit VkContext(std::shared_ptr<Window> &window);
    ~VkContext();
    void DrawFrame();
    void WaitIdle();

private:
    void createInstance();
    static bool checkValidationLayerSupport();
    [[nodiscard]] std::vector<const char*> getRequiredExtensions();
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallBack(VkDebugUtilsMessageSeverityFlagBitsEXT messageServerity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT *pCallBackData, void *pUserData);
    void setupDebugMessager();
    static VkResult createDebugUtilsMessengerExt(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    static void destroyDebugUtilsMessengerExt(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    void pickPhysicalDevice();
    [[nodiscard]] bool isDeviceSuitable(VkPhysicalDevice device);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    void createLogicalDevice();
    void createSurface();
    static bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
    static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);
    void createSwapChain();
    void createSwapChainImageViews();
    void createGraphicsPipeline();
    static std::vector<char> readFile(const std::string &fileName);
    VkShaderModule createShaderModule(const std::vector<char> &code);
    void createRenderPass();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffers();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    void createSyncObjects();

private:
    std::shared_ptr<Window> m_window;

    VkInstance m_instance = nullptr;
    std::vector<const char*> m_requiredExtensions;
    VkDebugUtilsMessengerEXT m_debugMessenger = nullptr;
    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
    VkDevice m_device = nullptr;
    VkQueue m_graphicsQueue = nullptr;
    VkQueue m_presentQueue = nullptr;
    VkSurfaceKHR m_surface = nullptr;


    VkSwapchainKHR m_swapChain = nullptr;
    std::vector<VkImage> m_swapChainImages;
    VkFormat m_swapChainImageFormat = VK_FORMAT_UNDEFINED;
    VkExtent2D m_swapChainExtent = { 0, 0 };
    std::vector<VkImageView> m_swapChainImageViews;

    VkPipelineLayout m_pipelineLayout = nullptr;
    VkRenderPass m_renderPass = nullptr;
    VkPipeline m_graphicsPipeline = nullptr;

    std::vector<VkFramebuffer> m_swapChainFrameBuffers;
    VkCommandPool m_commandPool;
    VkCommandBuffer m_commandBuffer;

    VkSemaphore m_imageAvailableSemaphore = nullptr;
    VkSemaphore m_renderFinishedSemaphore = nullptr;
    VkFence m_inFlightFence = nullptr;
};


#endif //VULKAN_START_VKCONTEXT_H
