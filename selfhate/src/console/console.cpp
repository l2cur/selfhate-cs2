#include <stdio.h>
#include <Windows.h>

#include "console.hpp"

void console::Initialize() {
    HWND window;
    AllocConsole();
    SetConsoleTitleA("cs2cheat debug console");
    freopen_s(reinterpret_cast<FILE**> stdin, "CONIN$", "r", stdin);
    freopen_s(reinterpret_cast<FILE**> stdout, "CONOUT$", "w", stdout);
    /* window = FindWindowA("ConsoleWindowClass", NULL);
         ShowWindow(window, 0);*/
    
}

void console::Shutdown() {
    fclose(stdin);
    fclose(stdout);
    FreeConsole();
}
