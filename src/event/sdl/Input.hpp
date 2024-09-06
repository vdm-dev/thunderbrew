#ifndef EVENT_SDL_INPUT_HPP
#define EVENT_SDL_INPUT_HPP

#include "event/Input.hpp"

bool SDLInputActive();

int32_t SDLInputGet(OSINPUT* id, int32_t* param0, int32_t* param1, int32_t* param2, int32_t* param3);

void SDLInputGetMousePosition(int32_t* x, int32_t *y);

#endif
