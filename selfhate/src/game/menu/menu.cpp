#include "menu.hpp"

#include "../../sdk/interfaces/interfaces.hpp"
#include "../../utils/utils.hpp"

#include "../esp/esp.hpp"
#include "../misc/misc.hpp"


static bool g_bMenuIsOpen;
static constexpr float g_fMaxWidth = 210.f;
float anim = 0.0f;
static int tabs = 0;
static int pitch = 0;
const char* pitch_variables[2] = {"up", "down"};
static int tab;

template <class T, class U>
static T clamp(const T& in, const U& low, const U& high) {
    if (in <= low) return low;

    if (in >= high) return high;

    return in;
}

namespace ImGuiEx {
    static bool ColorEdit4(const char* label, Color* v,
                           bool show_alpha = true) {
        auto clr = ImVec4{v->r() / 255.0f, v->g() / 255.0f, v->b() / 255.0f,
                          v->a() / 255.0f};

        if (ImGui::ColorEdit4(label, &clr.x, show_alpha)) {
            v->SetColor(clr.x, clr.y, clr.z, clr.w);
            return true;
        }
        return false;
    }
    static bool ColorEdit3(const char* label, Color* v) {
        return ColorEdit4(label, v, false);
    }
}  // namespace ImGuiEx

void menu::Render() {
    static char classInputText[64];

    if (ImGui::IsKeyPressed(ImGuiKey_Insert, false)) Toggle(!IsOpen());
    if (!IsOpen()) return;

    memory::fnSDL_SetRelativeMouseMode(false);
    memory::fnSDL_SetWindowGrab(interfaces::pInputSystem->GetSDLWindow(),
                                false);

    ImGuiIO& IO = ImGui::GetIO();

   auto s = ImVec2{}, p = ImVec2{}, gs = ImVec2{400, 300};
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(600, 400));
    ImGui::Begin("selfhate.xyz", nullptr,
                 ImGuiWindowFlags_NoDecoration |
                     ImGuiWindowFlags_NoBackground);  
    {

        s = ImVec2(
            ImGui::GetWindowSize().x - ImGui::GetStyle().WindowPadding.x * 2,
            ImGui::GetWindowSize().y - ImGui::GetStyle().WindowPadding.y * 2);
        p = ImVec2(ImGui::GetWindowPos().x + ImGui::GetStyle().WindowPadding.x,
                   ImGui::GetWindowPos().y + ImGui::GetStyle().WindowPadding.y);
        auto draw = ImGui::GetWindowDrawList();
        draw->AddRectFilled(p, ImVec2(p.x + s.x, p.y + s.y),
                            ImColor(47, 57, 67, 255));
        draw->AddRectFilledMultiColor(
            p, ImVec2(p.x + s.x, p.y + 61), ImColor(24, 31, 37, 255),
            ImColor(46, 56, 66, 255), ImColor(46, 56, 66, 255),
            ImColor(24, 31, 37, 255));
        ImGui::PushFont(font::main_text);
        draw->AddText(p + ImVec2(173, 22), ImColor(85, 173, 245, 255),
                      "selfhate.xyz | demonstrate yourself");
        ImGui::SetCursorPos(ImVec2(0, 61));
        if (ImGui::tab(tabs == 1, "Aimbot", ImVec2(119.21, 52))) tabs = 1;
        ImGui::SetCursorPos(ImVec2(119.21, 61));
        if (ImGui::tab(tabs == 2, "Visuals", ImVec2(120.2, 52))) tabs = 2;
        ImGui::SetCursorPos(ImVec2(239.4, 61));
        if (ImGui::tab(tabs == 3, "Misc", ImVec2(120.2, 52))) tabs = 3;
        ImGui::SetCursorPos(ImVec2(359.6, 61));
        if (ImGui::tab(tabs == 4, "Skinchanger", ImVec2(120.2, 52))) tabs = 4;
        ImGui::SetCursorPos(ImVec2(479.8, 61));
        if (ImGui::tab(tabs == 5, "Settings", ImVec2(120.2, 52))) tabs = 5;
        ImGui::PopFont();

        if (tabs == 1) {
            ImGui::SetCursorPos(ImVec2(20, 124));
            ImGui::MenuChild("Mem", ImVec2(169, 258));
            {
                ImGui::PushFont(font::Menu_font);
                ImGui::Checkbox("Box", &esp::bBoxEsp);
                ImGui::Checkbox("Glow (Detected)", &esp::bGlowEsp);
                ImGui::Checkbox("Helthbar", &esp::bHealthbar);
                ImGui::Checkbox("Name", &esp::bNameEsp);
                ImGui::Checkbox("Ignore teammates", &esp::bIgnoreTeammates);
                ImGuiEx::ColorEdit3("##color", &esp::GlowCol);
                ImGui::Checkbox("Bhop", &misc::bBhop);
                ImGui::SliderInt("test", &tab, 0, 100);
                ImGui::Combo("pitch", &pitch, pitch_variables, 2);
                ImGui::PopFont();
            }
            ImGui::EndChild();
            ImGui::SetCursorPos(ImVec2(216, 124));
            ImGui::MenuChild("Mem2", ImVec2(169, 123));
            {
            
            }
            ImGui::EndChild();
            ImGui::SetCursorPos(ImVec2(216, 258));
            ImGui::MenuChild("Mem3", ImVec2(169, 123));
            {
            
            }
            ImGui::EndChild();
            ImGui::SetCursorPos(ImVec2(413, 124));
            ImGui::MenuChild("Mem4", ImVec2(169, 258));
            {
            
            }
            ImGui::EndChild();
        }

        ImGui::PopStyleVar();
        ImGui::End();
    }
    
}

void menu::Toggle(bool bState) {
    if (!ImGui::GetCurrentContext() || !interfaces::pInputSystem) return;

    g_bMenuIsOpen = bState;
    if (interfaces::pInputSystem->IsRelativeMouseMode()) {
        const ImVec2 screenCenter = ImGui::GetIO().DisplaySize / 2.f;

        memory::fnSDL_SetRelativeMouseMode(!g_bMenuIsOpen);
        memory::fnSDL_SetWindowGrab(interfaces::pInputSystem->GetSDLWindow(),
                                    !g_bMenuIsOpen);
        memory::fnSDL_WarpMouseInWindow(nullptr, (int)screenCenter.x,
                                        (int)screenCenter.y);
    }
}

bool menu::IsOpen() { return g_bMenuIsOpen; }
