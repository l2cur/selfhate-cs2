#pragma once
#include "../../../math/types/vector.hpp"

class CInButtonStatePB {
   public:
    char pad_0000[24];  // 0x0000
    uint32_t buttons;   // 0x0018
    char pad_001C[12];  // 0x001C
};                      // Size: 0x0030

class CMsgQAngle {
   public:
    char pad_0000[24];  // 0x0000
    float pitch;        // 0x0018
    float yaw;          // 0x001C
    float roll;
    char pad_0020[40];  // 0x0020
};                      // Size: 0x0050

class CBaseUserCmdPB {
   public:
    char pad_0000[56];               // 0x0000
    CInButtonStatePB* button_state;  // 0x0038
    CMsgQAngle* qangle;              // 0x0040
    float unk1;                      // 0x0048
    float unk2;                      // 0x004C
    float forwardmove;               // 0x0050
    float sidemove;                  // 0x0054
    float unk3;                      // 0x0058
    float unk4;                      // 0x005C
    float unk5;                      // 0x0060
    float unk6;                      // 0x0064
    float unk7;                      // 0x0068
    char pad_006C[12];               // 0x006C
};                                   // Size: 120

class CUserCmd {
   public:
    char pad_0000[40];                  // 0x0000
    void* N00000135;                    // 0x0028
    CBaseUserCmdPB* base_user_cmd_ptr;  // 0x0030
    char pad_0038[16];                  // 0x0038
    void* button_state_ptr;             // 0x0048
    uint32_t buttons;                   // 0x0050
    char pad_0054[28];                  // 0x0054

    CBaseUserCmdPB* GetBaseUserCmd() {
        return *(CBaseUserCmdPB**)((uintptr_t)this + 0x30);
    }
};

class CCSGOInput {
   public:
    char pad_0000[64];          // 0x0000
    void* ptr;                  // 0x0040
    char pad_0048[16752];       // 0x0048
    bool N00000CCE;             // 0x41B8
    char pad_41B9[4];           // 0x41B9
    bool in_thirdperson;        // 0x41BD
    char pad_41BE[2];           // 0x41BE
    float N00000CCF;            // 0x41C0
    Vector thirdperson_angles;  // 0x41C4
    float N00000CD0;            // 0x41D0
    float N00000D23;            // 0x41D4
    char pad_41D8[624];         // 0x41D8

    CUserCmd* GetUserCmd() {
        auto sequence_number = *(int*)((uintptr_t)this + 0x41E0);
        auto cmd_array = (CUserCmd*)((uintptr_t)this + 0x10);
        return &cmd_array[sequence_number % 150];
    }

};  // Size: 0x4448
