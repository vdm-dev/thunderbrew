#ifndef SOUND_SI2_HPP
#define SOUND_SI2_HPP

#include "ui/Types.hpp"
#include <storm/Log.hpp>
#include <cstdint>
#include <cstdarg>
#include <fmod.h>
#include <fmod_errors.h>

class SI2 {
    public:
        // Static variables
        static FrameScript_Method s_ScriptFunctions[];
        static uint32_t sm_logFlags;
        static HSLOG sm_log;

        // Static functions
        static void RegisterScriptFunctions();
        static int32_t Log_Init();
        static void Log_Write(const char* format, ...);
        static void Log_Write(uint32_t line, const char* filename, FMOD_RESULT errcode, const char* format, ...);
        static int32_t Init(int32_t flag);
};

#endif
