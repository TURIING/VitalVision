/********************************************************************************
* @author: TURIING
* @email: turiing@163.com
* @date: 2024/9/13 23:32
* @version: 1.0
* @description: 
********************************************************************************/

#ifndef VULKAN_START_BASEDEFINE_H
#define VULKAN_START_BASEDEFINE_H

#include <tuple>

/*************************************************** type define ***************************************************/
struct Size {
    int32_t width = 0;
    int32_t height = 0;
};



/*************************************************** constant variable **********************************************/
const Size WINDOW_SIZE = {1000, 800};
constexpr const char *APP_NAME = "vulkan_demo";


/*************************************************** vulkan defind **************************************************/
constexpr const char *VK_LAYER_KHRONOS_VALIDATION = "VK_LAYER_KHRONOS_validation";
constexpr const char *VK_EXT_DEBUG_UTILS = "VK_EXT_debug_utils";

#endif //VULKAN_START_BASEDEFINE_H
