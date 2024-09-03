#pragma once

#include <raylib.h>

#include "bunraku.hpp"

namespace bunraku::raylib {
    void draw(const Animation& anim, Texture2D& texture, float x, float y, float rotation = 0.0, Color color = WHITE);
}
