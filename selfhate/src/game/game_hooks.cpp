#include "../sdk/interfaces/interfaces.hpp"
#include "../api/hook/hook.hpp"
#include "../sdk/source-sdk/classes/entity/c_usercmd.hpp"

#include "skins/skin_changer.hpp"
#include "menu/menu.hpp"
#include "misc/misc.hpp"

static CHook<bool __fastcall(void*)> g_mouseInputEnabled;
static bool __fastcall hkMouseInputEnabled(void* rcx) {
    if (menu::IsOpen()) return false;
    return g_mouseInputEnabled.m_pOriginalFn(rcx);
}

static CHook<BYTE* __fastcall(CCSGOInput*, unsigned int, unsigned __int8)>
    g_createmoveOriginal;
BYTE* __fastcall hkCreateMove(CCSGOInput* a1, unsigned int a2,
                                   unsigned __int8 a3) {
    auto ret = g_createmoveOriginal.m_pOriginalFn(a1, a2, a3);
    auto g_cmd = a1->GetUserCmd();
    if (g_cmd) {
        if (misc::bBhop)
            misc::Bhop(g_cmd);
        auto g_basecmd = g_cmd->GetBaseUserCmd();
        if (g_basecmd) {
            
        }
    }
    return ret;
}


static CHook<void __fastcall(void*, int)> g_frameStageNotify;
static void __fastcall hkFrameStageNotify(void* rcx, int frameStage) {
    skin_changer::Run();
    return g_frameStageNotify.m_pOriginalFn(rcx, frameStage);
}

void CS2_HookGameFunctions() {
    g_mouseInputEnabled.Hook(memory::fnMouseInputEnabled,
                             HOOK_FUNCTION(hkMouseInputEnabled));
    g_frameStageNotify.HookVirtual(interfaces::pClient, 29,
                                   HOOK_FUNCTION(hkFrameStageNotify));
    g_createmoveOriginal.Hook(memory::fnCreateMoveOriginal,
                              HOOK_FUNCTION(hkCreateMove));
}

void CS2_UnhookGameFunctions() {}
