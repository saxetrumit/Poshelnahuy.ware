cmake_minimum_required(VERSION 3.10)
project(Poshelnahuy.ware)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_GENERATOR_PLATFORM "Win32")

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/imgui
    ${CMAKE_SOURCE_DIR}/src/minhook/include
    ${CMAKE_SOURCE_DIR}/src/minhook/src/hde
)

set(SOURCE_FILES
    src/dllmain.cpp
    src/menu.cpp
    src/kiero.cpp
    src/imgui/imgui.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_impl_dx11.cpp
    src/imgui/imgui_impl_win32.cpp
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_widgets.cpp
    src/minhook/src/buffer.c
    src/minhook/src/hook.c
    src/minhook/src/trampoline.c
    src/minhook/src/hde/hde32.c
    src/minhook/src/hde/hde64.c
)

add_library(DLL_RESOURCES OBJECT
  src/minhook/dll_resources/MinHook.rc
)

add_library(Poshelnahuy.ware SHARED ${SOURCE_FILES})
target_link_libraries(Poshelnahuy.ware ${CMAKE_THREAD_LIBS_INIT} d3d11 dxgi user32 gdi32 DLL_RESOURCES)

if(EXISTS ${CMAKE_SOURCE_DIR}/src/minhook/dll_resources/MinHook.def)
    set_target_properties(Poshelnahuy.ware PROPERTIES LINK_FLAGS "/DEF:${CMAKE_SOURCE_DIR}/src/minhook/dll_resources/MinHook.def")
endif()

