#include <iostream>
#include <cmath>
#include <windows.h>
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

const float PI = 3.14159265;
void drawCircle(float radius, int centerX, int centerY, int steps = 300) {
    holdLeftMouseButton();
    for (int i = 0; i <= steps; i++) {
        float theta = (2 * PI * i) / steps;
        int x = static_cast<int>(centerX + radius * cos(theta));
        int y = static_cast<int>(centerY + radius * sin(theta));
        Sleep(1);
        SetCursorPos(x, y);
    }
    releaseLeftMouseButton();
}


BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    char title[256];
    GetWindowTextA(hwnd, title, sizeof(title));
    
    if (strstr(title, "Draw")) { //change the window title
        ShowWindow(hwnd, SW_RESTORE);
        SetForegroundWindow(hwnd);
        ShowWindow(hwnd, SW_SHOWMAXIMIZED);
        return FALSE;
    }

    return TRUE;
}

POINT getClickPosition() {
    POINT pt = {0};
    while (true) {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            GetCursorPos(&pt);
            break;
        }
        Sleep(10);
    }
    Sleep(200);
    return pt;
}
int main() {

    EnumWindows(EnumWindowsProc, 0);
    Sleep(1000);

    POINT center = getClickPosition();

    float radius = 150;

    SetCursorPos(center.x + static_cast<int>(radius), center.y);
    Sleep(1000);

    drawCircle(radius, center.x, center.y);
}
