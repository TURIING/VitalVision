local PROJECTION_DIR = os.curdir()
local RUNTIME_DIR = path.join(PROJECTION_DIR, "Runtime")
local THIRD_PARTY_DIR = path.join(PROJECTION_DIR, "ThirdParty")
local BINARY_DIR = path.join(PROJECTION_DIR, "Bin");

if is_mode("debug") then
    add_defines("MODE_DEBUG")
elseif is_mode("release") then
    add_defines("MODE_RELEASE")
else 
    add_defines("MODE_RELWITHDEBINFO")
end

set_toolset("cc", "clang-cl")
set_toolset("cxx", "clang-cl")
add_cxxflags("-std:c++20", { tools = { "clang-cl" }})
add_defines("__cpp_consteval", { tools = { "clang-cl" }})
add_defines("NOMINMAX", "UNICODE", "_UNICODE")
add_rules("mode.debug", "mode.releasedbg")
set_arch("x64")

-- includes("xmake/dxc.lua")
-- includes("xmake/stduuid.lua")
-- includes("xmake/renderdoc.lua")

-- requires packages
add_requires("fmt 9.1.0")
add_requires("spdlog v1.9.2")   
add_requires("glfw 3.3.8")               
add_requires("vulkan-memory-allocator v3.0.1")
add_requires("magic_enum v0.9.0")
add_requires("vulkansdk", {system = true})
add_requires("glm")
add_requires("stb 2023.01.30")
-- add_requires("imgui v1.89.7-docking", {debug = isDebug})      
-- add_requires("vulkan-hpp v1.3.250", {verify = false})        
-- add_requires("stduuid", {debug = isDebug})
-- add_requires("jsoncpp 1.9.5", {debug = isDebug, configs = {shared = false}})


target("VitalVision")
    set_languages("c++latest")
    set_warnings("all")
    set_kind("binary")
    
    add_headerfiles("Runtime/**.h")
    add_headerfiles("Runtime/**.hpp")
    add_headerfiles("Runtime/**.inc")
    add_files("Runtime/**.cpp")
    add_includedirs(RUNTIME_DIR)
    
    add_defines("PLATFORM_WIN")
    add_defines("VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1")
    add_defines("VULKAN_HPP_NO_CONSTRUCTORS=1")

    add_defines("_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING=1", "_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS=1")

    -- dependent packages
    add_packages("fmt")
    add_packages("spdlog")
    add_packages("glfw")
    add_packages("vulkansdk")
    add_packages("magic_enum")
    add_packages("glm")
    add_packages("stb")
    -- add_packages("imgui")
    -- add_packages("vulkan-hpp")
    -- add_packages("jsoncpp")

    add_defines("VMA_STATIC_VULKAN_FUNCTIONS=0", "VMA_DYNAMIC_VULKAN_FUNCTIONS=1")
    add_packages("vulkan-memory-allocator")

    -- local packages
    -- add_packages("stduuid")

    set_targetdir(BINARY_DIR)
    add_syslinks("Advapi32")
target_end()