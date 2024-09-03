#include "bunraku_raylib.hpp"

void bunraku::raylib::draw(const Animation& anim, Texture2D& texture, float x, float y, float rotation, Color color) {
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
