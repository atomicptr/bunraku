// This file is part of bunraku - A 2D animation library for making games with C++23
// See: https://github.com/atomicptr/bunraku
#pragma once

#include <raylib.h>

#include "bunraku.hpp"

namespace bunraku::raylib {
    void draw(const Animation& anim, Texture2D& texture, float x, float y, float rotation = 0.0, Color color = WHITE);
}
