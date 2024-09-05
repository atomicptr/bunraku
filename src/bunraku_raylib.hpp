// This file is part of bunraku - A 2D animation library for making games with C++23
// See: https://github.com/atomicptr/bunraku
#pragma once

#include <raylib.h>

#include "bunraku.hpp"

namespace bunraku::raylib {
    inline void draw(const Animation& anim, Texture2D& texture, float x, float y, float rotation = 0.0, Color color = WHITE) {
        auto& frame = anim.current_frame();

        auto flip_x = anim.is_flipped_v() ? -1.0f : 1.0f;
        auto flip_y = anim.is_flipped_h() ? -1.0f : 1.0f;

        DrawTexturePro(
            texture,
            {(float)frame.x, (float)frame.y, flip_x * frame.width, flip_y * frame.height},
            {x, y, (float)frame.width, (float)frame.height},
            {0, 0},
            rotation,
            color
        );
    }
}
