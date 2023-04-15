#pragma once
#include "../color.hpp"

class CGlowProperty {
   public:
    SCHEMA_FIELD(m_bGlowing, "CGlowProperty", "m_bGlowing", bool);
    SCHEMA_FIELD(m_iGlowType, "CGlowProperty", "m_iGlowType", int);
    SCHEMA_FIELD(m_glowColorOverride, "CGlowProperty", "m_glowColorOverride",
                 Color);
};
