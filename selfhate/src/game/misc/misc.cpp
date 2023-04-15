#include "misc.hpp"
#include "../../sdk/interfaces/interfaces.hpp"

void misc::Bhop(CUserCmd* cmd) {

   if (!interfaces::pEngine->IsInGame()) return;
    CCSPlayerController* pLocalPlayerController =
        interfaces::pEntitySystem->GetLocalPlayerController();
    if (!pLocalPlayerController) return;

    for (int i = 1; i <= MAX_PLAYERS; ++i) {
        CCSPlayerController* pPlayer =
            interfaces::pEntitySystem->GetBaseEntity<CCSPlayerController>(i);
        if (!pPlayer || !pPlayer->IsPlayerController() ||
            !pPlayer->m_bPawnIsAlive())
            continue;

        const bool isLocalPlayer = pPlayer->m_bIsLocalPlayerController();
        if (!isLocalPlayer) continue;

        C_CSPlayerPawn* pPawn = pPlayer->m_hPawn().Get<C_CSPlayerPawn>();
        if (!pPawn) continue;

        if (pPawn->m_MoveType() == MOVETYPE_LADDER) return;

        bool jumped = false;

        if (cmd->buttons & IN_JUMP && !(pPawn->m_fFlags() & FL_ONGROUND)) {
            if (!jumped) {
                cmd->buttons &= ~IN_JUMP;
                jumped = true;
            }
        } else if (jumped) {
            cmd->buttons |= IN_JUMP;
            jumped = false;
        }
    }
}
