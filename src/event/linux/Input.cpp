#include <common/Time.hpp>

#include "event/Input.hpp"

#if defined(WHOA_BUILD_GLSDL)
#include "event/sdl/Input.hpp"
#endif

int32_t OsInputGet(OSINPUT* id, int32_t* param0, int32_t* param1, int32_t* param2, int32_t* param3) {
#if defined(WHOA_BUILD_GLSDL)
    if (SDLInputActive()) {
        return SDLInputGet(id, param0, param1, param2, param3);
    }
#endif
    if (Input::s_queueTail == Input::s_queueHead) {
        return 0;
    }

    OsQueueSetParam(3, OsGetAsyncTimeMs());

    return OsQueueGet(id, param0, param1, param2, param3);
}

void OsInputSetMouseMode(OS_MOUSE_MODE mode) {
    // TODO
}

int32_t OsWindowProc(void* window, uint32_t message, uintptr_t wparam, intptr_t lparam) {
    return 0;
}

void OsInputGetMousePosition(int32_t* x, int32_t* y) {
#if defined(WHOA_BUILD_GLSDL)
    if (SDLInputActive()) {
        SDLInputGetMousePosition(x, y);
        return;
    }
#endif

    if (x) {
        *x = 0;
    }
    if (y) {
        *y = 0;
    }
}
