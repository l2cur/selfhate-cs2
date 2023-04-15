#pragma once

#include "sdk/game_defines.hpp"

// Uncomment this for vulkan support, add '-vulkan' into your launch
// parameters and lastly include both 'imgui_impl_vulkan' files.
// #define CS2_SDK_ENABLE_VULKAN_SUPPORT

// Helper
#define SIGNATURE(sig) \
    stb::simple_conversion::build<stb::fixed_string{sig}>::value

// Modules
#define CLIENT_DLL "client.dll"
#define ENGINE2_DLL "engine2.dll"
#define SCHEMASYSTEM_DLL "schemasystem.dll"
#define INPUTSYSTEM_DLL "inputsystem.dll"
#define SDL2_DLL "SDL2.dll"
#define TIER0_DLL "tier0.dll"
#define NAVSYSTEM_DLL "navsystem.dll"
#define RENDERSYSTEMVULKAN_DLL "rendersystemvulkan.dll"

// Interfaces
#define GAME_RESOURCE_SERVICE_CLIENT "GameResourceServiceClientV001"
#define SOURCE2_CLIENT "Source2Client002"
#define SCHEMA_SYSTEM "SchemaSystem_001"
#define INPUT_SYSTEM_VERSION "InputSystemVersion001"
#define SOURCE2_ENGINE_TO_CLIENT "Source2EngineToClient001"
#define ENGINE_CVAR "VEngineCvar007"

// Signatures

// CGameEntitySystem::
#define GET_HIGHEST_ENTITY_INDEX SIGNATURE("33 DB E8 ? ? ? ? 8B 08")
#define GET_BASE_ENTITY SIGNATURE("8B D3 E8 ? ? ? ? 48 8B F8 48 85 C0 74 76")

#define PRINT_SCHEMA_DETAILED_CLASS_LAYOUT \
    SIGNATURE("48 89 5C 24 ? 48 89 6C 24 ? 48 89 4C 24 ?")

#define SCREEN_TRANSFORM SIGNATURE("E8 ? ? ? ? F3 0F 10 45 ? 8B D0")

#define SET_MESH_GROUP_MASK SIGNATURE("E8 ? ? ? ? 8B 45 D0 48 8B 55 D8")
#define GET_BONE_POSITION \
    "48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 4D 8B F1"
#define CREATEMOVE SIGNATURE("48 8B C4 48 89 48 08 55 56 41 54 41 55 48")

#define SCENENODE SIGNATURE("44 8B C0 48 8B D6 48 8B CF E8 ? ? ? ? 48 8B C6")

// CCSGOInput::
#define MOUSE_INPUT_ENABLED \
    SIGNATURE("40 53 48 83 EC 20 80 B9 ? ? ? ? ? 48 8B D9 75 78")

// Internal

#include <cassert>
#define CS2_ASSERT(cond, ...) assert(cond)
