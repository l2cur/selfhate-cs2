#include "../../utils/utils.hpp"

#include "../menu/menu.hpp"
#include "../esp/esp.hpp"
#include "../menu/bytes.hpp"

#include "render.hpp"

#include <imgui/imgui.h>

void render::Initialize() {
    ImFontConfig font_config;
    font_config.PixelSnapH = false;
    font_config.OversampleH = 5;
    font_config.OversampleV = 5;
    font_config.RasterizerMultiply = 1.2f;

    static const ImWchar ranges[] = {
        0x0020, 0x00FF,  // Basic Latin + Latin Supplement
        0x0400, 0x052F,  // Cyrillic + Cyrillic Supplement
        0x2DE0, 0x2DFF,  // Cyrillic Extended-A
        0xA640, 0xA69F,  // Cyrillic Extended-B
        0xE000, 0xE226,  // icons
        0,
    };

    font_config.GlyphRanges = ranges;

    font::Hp_font = ImGui::GetIO().Fonts->AddFontFromFileTTF(
        "C:\\Windows\\Fonts\\tahoma.ttf", 10.f);
    font::Esp_font = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(
        esp_font, sizeof(esp_font), 10.0f, &font_config, ranges);
    font::Menu_font = ImGui::GetIO().Fonts->AddFontFromFileTTF(
        "C:\\Windows\\Fonts\\tahoma.ttf", 14.f);

    font::main_text = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(
        menufont, sizeof(menufont), 20.0f, &font_config, ranges);

    font::child_text = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(
        menufont, sizeof(menufont), 16.0f, &font_config, ranges);


}

void render::NewFrame() {
    if (ImGui::IsKeyPressed(ImGuiKey_End, false)) utils::UnloadLibrary();

    esp::Render();
    menu::Render();
}

void render::Shutdown() { menu::Toggle(false); }
