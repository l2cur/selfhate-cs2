#pragma once

#include "ccollisionproperty.hpp"
#include "centityinstance.hpp"
#include "cgamescenenode.hpp"
#include "m_movetype.hpp"
#include "c_glowpoperty.hpp"

// This is not from the game, it was written by me.
struct BBox_t {
    float x, y, w, h;
};

class C_BaseEntity : public CEntityInstance {
   public:
    bool IsPlayerController();
    bool GetBoundingBox(BBox_t& out);

    SCHEMA_FIELD(m_pGameSceneNode, "C_BaseEntity", "m_pGameSceneNode",
                 CGameSceneNode*);
    SCHEMA_FIELD(m_pCollision, "C_BaseEntity", "m_pCollision",
                 CCollisionProperty*);
    SCHEMA_FIELD(m_iTeamNum, "C_BaseEntity", "m_iTeamNum", uint8_t);
    SCHEMA_FIELD(m_hOwnerEntity, "C_BaseEntity", "m_hOwnerEntity", uint8_t);
    SCHEMA_FIELD(m_MoveType, "C_BaseEntity", "m_MoveType", MoveType_t);
    SCHEMA_FIELD(m_fFlags, "C_BaseEntity", "m_fFlags", uint8_t);
    SCHEMA_FIELD(m_Glow, "C_BaseModelEntity", "m_Glow", CGlowProperty);
};
