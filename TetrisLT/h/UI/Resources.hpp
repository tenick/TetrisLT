#ifndef RESOURCES_H
#define RESOURCES_H

#include "../../imgui/imgui.h"

namespace Resources {
    extern ImGuiIO* io;
    extern ImGuiStyle* style;

    // load fonts
    extern ImFont* fontR32;
    extern ImFont* fontR64;
    extern ImFont* fontR128;
    extern ImFont* fontB32;
    extern ImFont* fontB64;
    extern ImFont* fontB128;
}

#endif