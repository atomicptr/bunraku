#include <raylib.h>

#include "../../../src/bunraku.hpp"
#include "../../../src/bunraku_fsm.hpp"
#include "../../../src/bunraku_fsm_raylib.hpp"
#include "../../../src/bunraku_raylib.hpp"

enum class CatAnim {
    PunchRight,
    PunchLeft,
    KickRight,
    KickLeft,
};

const float anim_speed = 0.1f;

int main() {
    InitWindow(800, 600, "bunraku cat fighter example");
    SetTargetFPS(60);

    auto texture = LoadTexture("assets/cat_fighter.png");

    auto camera = Camera2D {{0, 0}, {0, 0}, 0.0f, 2.0f};

    auto g = bunraku::Grid {50, 50};

    auto cat = bunraku::FSM<CatAnim>();

    cat.add(CatAnim::PunchRight, {g.frames("6-9", 3), anim_speed});
    cat.add(CatAnim::PunchLeft, {g.frames("6-9", 3), anim_speed, true, false, false, true});
    cat.add(CatAnim::KickRight, {g.frames("0-9", 4, "8-1", 4), anim_speed, true, false, false, true});
    cat.add(CatAnim::KickLeft, {g.frames("0-9", 4, "8-1", 4), anim_speed});

    cat.play(CatAnim::PunchRight);

    while (!WindowShouldClose()) {
        auto dt = GetFrameTime();

        if (IsKeyPressed(KEY_Q)) {
            cat.play(CatAnim::PunchLeft);
        }

        if (IsKeyPressed(KEY_W)) {
            cat.play(CatAnim::PunchRight);
        }

        if (IsKeyPressed(KEY_A)) {
            cat.play(CatAnim::KickRight);
        }

        if (IsKeyPressed(KEY_S)) {
            cat.play(CatAnim::KickLeft);
        }

        cat.update(dt);

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);

        bunraku::raylib::draw(cat, texture, 100, 100);

        DrawText("Q/W to punch left/right, A/S to kick left/right", 10, 10, 10, GREEN);

        EndMode2D();
        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();
}
