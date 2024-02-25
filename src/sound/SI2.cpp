#include "sound/SI2.hpp"
#include "ui/FrameScript.hpp"

void SI2::RegisterScriptFunctions() {
    FrameScript_Method* item = s_ScriptFunctions;
    while (item->name) {
        FrameScript_RegisterFunction(item->name, item->method);
        item++;
    }
}

int32_t SI2::Init(int32_t flag) {
    return 0;
}
