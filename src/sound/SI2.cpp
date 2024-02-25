#include "sound/SI2.hpp"
#include "ui/FrameScript.hpp"
#include "console/CVar.hpp"

void SI2::RegisterScriptFunctions() {
    FrameScript_Method* item = s_ScriptFunctions;
    while (item->name) {
        FrameScript_RegisterFunction(item->name, item->method);
        item++;
    }
}

int32_t SI2::Init(int32_t flag) {

    Log_Init();
    SI2_LOG("=> Version %s (%s) %s", "1.0.0", "00000", "Feb 25 2024");
    SI2_LOG(" ");
    SI2_LOG("=> Setting up Game Sound:");
    SI2_LOG(" - SESound Engine Init");
    SI2_LOG(" - FMOD Memory Init");

    return 0;
}
