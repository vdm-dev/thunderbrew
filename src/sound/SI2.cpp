#include "sound/SI2.hpp"
#include "ui/FrameScript.hpp"
#include "console/CVar.hpp"
#include <storm/Memory.hpp>

void* F_CALL FMOD_Alloc(unsigned int size, FMOD_MEMORY_TYPE type, const char* sourcestr) {
    return SMemAlloc(size, sourcestr, 0, 0);
}

void* F_CALL FMOD_ReAlloc(void* ptr, unsigned int size, FMOD_MEMORY_TYPE type, const char* sourcestr) {
    return SMemReAlloc(ptr, size, sourcestr, 0, 0);
}

void F_CALL FMOD_Free(void* ptr, FMOD_MEMORY_TYPE type, const char* sourcestr) {
    SMemFree(ptr, sourcestr, 0, 0);
}


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

    auto errcode = FMOD::Memory_Initialize(nullptr, 0, &FMOD_Alloc, &FMOD_ReAlloc, &FMOD_Free);
    SI2_ERR(errcode, " - FMOD Memory Init");

    return 0;
}

void SI2::StartGlueMusic(const char* filename) {

}
