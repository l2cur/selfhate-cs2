#pragma once

#define IN_JUMP 0x2
#define FL_ONGROUND 0x1

enum MoveType_t {
    MOVETYPE_NONE = 0x0,
    MOVETYPE_OBSOLETE = 0x1,
    MOVETYPE_WALK = 0x2,
    MOVETYPE_STEP = 0x3,
    MOVETYPE_FLY = 0x4,
    MOVETYPE_FLYGRAVITY = 0x5,
    MOVETYPE_VPHYSICS = 0x6,
    MOVETYPE_PUSH = 0x7,
    MOVETYPE_NOCLIP = 0x8,
    MOVETYPE_OBSERVER = 0x9,
    MOVETYPE_LADDER = 0xa,
    MOVETYPE_CUSTOM = 0xb,
    MOVETYPE_LAST = 0xc,
    MOVETYPE_MAX_BITS = 0x5,
};