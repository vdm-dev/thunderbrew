#include "sound/SI2.hpp"
#include <storm/Error.hpp>
#include <bc/os/File.hpp>
#include <cstdio>

uint32_t SI2::sm_logFlags = STORM_LOG_FLAG_DEFAULT;
HSLOG SI2::sm_log = nullptr;

int32_t SI2::Log_Init() {
    OsCreateDirectory("Logs", 0);
    SLogCreate("Logs\\Sound.log", sm_logFlags, &sm_log);
    sm_logFlags |= STORM_LOG_FLAG_APPEND;
    // return OsDeleteFile((Blizzard::File*)"Logs\\SESound.log");
    return 0;
}

void SI2::Log_Write(const char* format, ...) {
    STORM_ASSERT(format);

    char output[512] = { 0 };
    if (format[0]) {
        va_list va;
        va_start(va, format);
        vsnprintf(output, sizeof(output), format, va);
        va_end(va);
    }

    // Log_Write(__LINE__, __FILE__, FMOD_OK, output);
    Log_Write(__LINE__, __FILE__, 0, output);
}

void SI2::Log_Write(uint32_t line, const char* filename, int32_t errcode, const char* format, ...) {
    static uint32_t s_nNumErrors = 0;

    if (s_nNumErrors > 200) {
        return;
    }

    if (s_nNumErrors == 200) {
        SLogWrite(sm_log, " -######## TOO MANY ERRORS. NO FURTHER ERRORS WILL BE LOGGED.");
        SLogFlush(sm_log);
        s_nNumErrors++;
        return;
    }

    STORM_ASSERT(format);

    char output[512] = { 0 };
    if (format[0]) {
        va_list va;
        va_start(va, format);
        vsnprintf(output, sizeof(output), format, va);
        va_end(va);
    }

#if defined(WHOA_BUILD_SOUND_FMOD)
    if (errcode == FMOD_OK) {
        SLogWrite(sm_log, output);
        SLogFlush(sm_log);
    }

    if (errcode == FMOD_ERR_HTTP_PROXY_AUTH) {
        return;
    }

    SLogWrite(sm_log, " -######## FMOD ERROR! (err %d) %s", errcode, FMOD_ErrorString(errcode));
#endif

    if (format[0]) {
        SLogWrite(sm_log, output);
    }
    SLogWrite(sm_log, "%s(%d)", filename, line);
    SLogFlush(sm_log);
    s_nNumErrors++;

}
