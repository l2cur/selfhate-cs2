#pragma once
#include "../../sdk/source-sdk/classes/color.hpp"
namespace esp {
    void Render();

    inline bool bBoxEsp, bNameEsp, bHealthbar, bIgnoreTeammates, bGlowEsp;
    inline Color GlowCol = Color(255, 255, 255, 255);
}  // namespace esp
