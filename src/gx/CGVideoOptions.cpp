#include "gx/CGVideoOptions.hpp"
#include "ui/FrameScript.hpp"
#include "util/Unimplemented.hpp"

int32_t Script_GetCurrentResolution(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_GetScreenResolutions(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_GetRefreshRates(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_GetCurrentMultisampleFormat(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_GetMultisampleFormats(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

int32_t Script_IsStereoVideoAvailable(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

FrameScript_Method CGVideoOptions::s_ScriptFunctions[] = {
    { "GetCurrentResolution", &Script_GetCurrentResolution },
    { "GetScreenResolutions", &Script_GetScreenResolutions },
    { "GetRefreshRates", &Script_GetRefreshRates },
    { "GetCurrentMultisampleFormat", &Script_GetCurrentMultisampleFormat },
    { "GetMultisampleFormats", &Script_GetMultisampleFormats },
    { "IsStereoVideoAvailable", &Script_IsStereoVideoAvailable }
};

size_t CGVideoOptions::s_NumScriptFunctions = sizeof(CGVideoOptions::s_ScriptFunctions) / sizeof(FrameScript_Method);

void CGVideoOptions::RegisterScriptFunctions() {
    for (int32_t i = 0; i < CGVideoOptions::s_NumScriptFunctions; i++) {
        auto item = &s_ScriptFunctions[i];
        FrameScript_RegisterFunction(item->name, item->method);
    }
}
