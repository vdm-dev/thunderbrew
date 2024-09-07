#include "client/gui/OsGui.hpp"

static void* s_GxDevWindow = nullptr;

void* OsGuiGetWindow(int32_t type) {
    switch (type) {
    case 0:
        return s_GxDevWindow;
    default:
        return nullptr;
    }
}

bool OsGuiIsModifierKeyDown(int32_t key) {
    // TODO
    return false;
}

int32_t OsGuiProcessMessage(void* message) {
    return 0;
}

void OsGuiSetGxWindow(void* window) {
    s_GxDevWindow = window;
}
