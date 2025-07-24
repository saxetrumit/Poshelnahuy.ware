#pragma once

uintptr_t сlient_t = (uintptr_t)GetModuleHandleA("client.dll");

namespace client
{
	namespace BaseClient{
		constexpr uint32_t dwCSGOInput = 0x1A78280;
        constexpr uint32_t dwEntityList = 0x1A05670;
        constexpr uint32_t dwGameEntitySystem = 0x1B28D78;
        constexpr uint32_t dwGameEntitySystem_highestEntityIndex = 0x20F0;
        constexpr uint32_t dwGameRules = 0x1A69CB8;
        constexpr uint32_t dwGlobalVars = 0x184CEB0;
        constexpr uint32_t dwGlowManager = 0x1A69408;
        constexpr uint32_t dwLocalPlayerController = 0x1A53C38;
        constexpr uint32_t dwLocalPlayerPawn = 0x18590D0;
        constexpr uint32_t dwPlantedC4 = 0x1A72ED0;
        constexpr uint32_t dwPrediction = 0x1858F50;
        constexpr uint32_t dwSensitivity = 0x1A6A9D8;
        constexpr uint32_t dwSensitivity_sensitivity = 0x40;
        constexpr uint32_t dwViewAngles = 0x1A78650;
        constexpr uint32_t dwViewMatrix = 0x1A6E3F0;
        constexpr uint32_t dwViewRender = 0x1A6ED00;
        constexpr uint32_t dwWeaponC4 = 0x1A07700;
	}
	namespace C_CSPlayerPawn
	{
		constexpr uint32_t m_iHealth = 0x344;
		constexpr uint32_t m_iMaxHealth	= 0x340;
		constexpr uint32_t m_vOrigin = 0x1324;
		constexpr uint32_t m_iTeamNum = 0x3E3;
		constexpr uint32_t m_hPlayerPawn = 0x824;
		constexpr uint32_t m_bLeftHanded = 0x22C1;
		constexpr uint32_t m_pGlowServices = 0x1530;
		constexpr uint32_t m_ArmorValue = 0x241C;

		constexpr uint32_t m_bIsScoped = 0x23E8;
		constexpr uint32_t m_bIsDefusing = 0x23EA;
		
		constexpr uint32_t m_pCameraServices = 0x11E0;
		constexpr uint32_t m_pViewModelServices = 0x1368;
	}
	namespace CCSPlayerController
	{
		constexpr uint32_t m_iPing = 0x740;
		constexpr uint32_t m_sSanitizedPlayerName = 0x778;
	}
}