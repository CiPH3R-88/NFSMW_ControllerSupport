#include <windows.h>
#include <filesystem>
#include <string>
#include "ControllerSupport.h"

struct ControllerConfig {
    int   Mode = 3;                  // 0 = Off, 1 = Xbox, 2 = PlayStation, 3 = Auto Detect
    float LeftStickDeadzone = 10.0f;
    float RightStickDeadzone = 10.0f;
    std::filesystem::path GamePath;
    std::filesystem::path IniPath;

    void Load() {
        char exePath[MAX_PATH] = { 0 };
        GetModuleFileNameA(NULL, exePath, MAX_PATH);
        GamePath = std::filesystem::path(exePath).parent_path();

        IniPath = GamePath / "scripts" / "NFSMW_ControllerSupport.ini";
        if (!std::filesystem::exists(IniPath)) {
            IniPath = GamePath / "NFSMW_ControllerSupport.ini";
        }
        if (!std::filesystem::exists(IniPath)) {
            IniPath = GamePath / "scripts" / "ControllerSupport.ini";
        }
        if (!std::filesystem::exists(IniPath)) {
            IniPath = GamePath / "ControllerSupport.ini";
        }

        std::string iniStr = IniPath.string();

        Mode = GetPrivateProfileIntA("CONTROLLER", "ControllerSupport", -1, iniStr.c_str());
        if (Mode == -1) {
            Mode = GetPrivateProfileIntA("MISC", "ControllerSupport", -1, iniStr.c_str());
        }
        if (Mode == -1) {
            Mode = GetPrivateProfileIntA("MISC", "GamepadSupport", -1, iniStr.c_str());
        }
        if (Mode < 0 || Mode > 3) {
            Mode = 3;
        }

        char leftDzBuf[64] = { 0 };
        GetPrivateProfileStringA("CONTROLLER", "LeftStickDeadzone", "10.0", leftDzBuf, sizeof(leftDzBuf), iniStr.c_str());
        LeftStickDeadzone = static_cast<float>(atof(leftDzBuf));

        char rightDzBuf[64] = { 0 };
        GetPrivateProfileStringA("CONTROLLER", "RightStickDeadzone", "10.0", rightDzBuf, sizeof(rightDzBuf), iniStr.c_str());
        RightStickDeadzone = static_cast<float>(atof(rightDzBuf));
    }
};

static ControllerConfig g_ControllerConfig;

static void InitializeMod() {
    static bool s_Initialized = false;
    if (s_Initialized) return;
    s_Initialized = true;

    g_ControllerConfig.Load();

    ControllerSupport::Init(
        g_ControllerConfig.Mode,
        g_ControllerConfig.LeftStickDeadzone,
        g_ControllerConfig.RightStickDeadzone,
        g_ControllerConfig.GamePath
    );
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hinstDLL);

        char moduleName[MAX_PATH] = { 0 };
        GetModuleFileNameA(NULL, moduleName, MAX_PATH);
        if (strstr(moduleName, "speed.exe") || strstr(moduleName, "SPEED.EXE")) {
            InitializeMod();
        }
    }
    return TRUE;
}
