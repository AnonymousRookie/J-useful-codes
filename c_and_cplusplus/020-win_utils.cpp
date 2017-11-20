/************************************************************************
* CREATED TIME: 2017-9-20 23:38:40
* LAST MODIFIED TIME: 2017-9-20 23:38:40
* DESCRIPTION: win_utils
* BY: 357688981@qq.com
************************************************************************/

#include <windows.h>
#include <iostream>

// Returns true if the shift key is currently pressed.
bool IsShiftPressed() {
    return (::GetKeyState(VK_SHIFT) & 0x8000) == 0x8000;
}
// Returns true if the ctrl key is currently pressed.
bool IsCtrlPressed() {
    return (::GetKeyState(VK_CONTROL) & 0x8000) == 0x8000;
}
// Returns true if the alt key is currently pressed.
bool IsAltPressed() {
    return (::GetKeyState(VK_MENU) & 0x8000) == 0x8000;
}

int main() {
    return 0;
}