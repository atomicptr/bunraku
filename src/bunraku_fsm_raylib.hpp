// This file is part of bunraku - A 2D animation library for making games with C++23
// See: https://github.com/atomicptr/bunraku
#pragma once

#include <raylib.h>

#include "bunraku_fsm.hpp"
#include "bunraku_raylib.hpp"

namespace bunraku::raylib {

    template<typename T>
    void draw(const FSM<T>& fsm, Texture2D texture, float x, float y, float rotation = 0.0f, Color color = WHITE) {
        draw(fsm.current_animation(), texture, x, y, rotation, color);
    }
}
