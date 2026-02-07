#include <windows.h>
#include <shellapi.h>
#include <thread>
#include <iostream>
#include <cmath>
using namespace std;

void holdLeftMouseButton() {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));
}
void releaseLeftMouseButton() {
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
}

const float PI = 3.14159265f;
void drawCircle(float radius, int centerX, int centerY, int steps = 300) {
    holdLeftMouseButton();
    for (int i = 0; i <= steps; i++) {
        float theta = (2 * PI * i) / steps;
        int x = static_cast<int>(centerX + radius * cos(theta));
        int y = static_cast<int>(centerY + radius * sin(theta));
        SetCursorPos(x, y);
        Sleep(1);
    }
    releaseLeftMouseButton();
}

HWND FindBrowserWindow(DWORD pid) {
    HWND hwndFound = NULL;
    EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
        DWORD windowPID;
        GetWindowThreadProcessId(hwnd, &windowPID);
        HWND* pHwnd = reinterpret_cast<HWND*>(lParam);
        if (windowPID == *(DWORD*)pHwnd && IsWindowVisible(hwnd)) {
            *pHwnd = hwnd;
            return FALSE;
        }
        return TRUE;
    }, (LPARAM)&hwndFound);
    return hwndFound;
}

int main() {
    string url = "https://neal.fun/perfect-circle/";

    SHELLEXECUTEINFOA shExecInfo = {0};
    shExecInfo.cbSize = sizeof(SHELLEXECUTEINFOA);
    shExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    shExecInfo.hwnd = NULL;
    shExecInfo.lpVerb = "open";
    shExecInfo.lpFile = "chrome.exe";
    shExecInfo.lpParameters = url.c_str();
    shExecInfo.nShow = SW_SHOWNORMAL;

    if (!ShellExecuteExA(&shExecInfo)) {
        cerr << "Failed to open browser. Make sure chrome.exe is in PATH.\n";
        return 1;
    }

    DWORD pid = GetProcessId(shExecInfo.hProcess);
    keybd_event(VK_F11, 0, 0, 0);
    Sleep(100);
    keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);

    int screenX = GetSystemMetrics(SM_CXSCREEN);
    int screenY = GetSystemMetrics(SM_CYSCREEN);
    int centerX = screenX / 2;
    int centerY = screenY / 2;
    SetCursorPos(centerX, centerY);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); 
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0); 
    Sleep(500);
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0); 
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    

    int radius = 290;
    SetCursorPos(centerX + static_cast<int>(radius), centerY);
    drawCircle(radius, centerX, centerY, 300);
    return 0;
}
