#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace menu {
    void Render();

    void Toggle(bool bState);
    bool IsOpen();
}  // namespace menu

namespace font {
    inline ImFont* child_text;
    inline ImFont* main_text;
    inline ImFont* Esp_font;
    inline ImFont* Hp_font;
    inline ImFont* Menu_font;
}
