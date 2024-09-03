#include <vector>

#include <raylib.h>

#include "../../../src/bunraku.hpp"
#include "../../../src/bunraku_raylib.hpp"

int main() {
    InitWindow(800, 600, "bunraku example");

    auto texture = LoadTexture("assets/1945.png");

    auto g32 = bunraku::Grid {32, 32, 3, 3, 1};

    auto spinning = std::vector<bunraku::Animation> {
        bunraku::Animation {g32.frames("0-7", 0), 0.1},
        bunraku::Animation {g32.frames(17, "7-10", 17, "9-6"), 0.2f},
        bunraku::Animation {g32.frames("0-7", 1), 0.3},
        bunraku::Animation {g32.frames(18, "7-10", 18, "9-6"), 0.4f},
        bunraku::Animation {g32.frames("0-7", 2), 0.5},
        bunraku::Animation {g32.frames(19, "7-10", 19, "9-6"), 0.6f},
        bunraku::Animation {g32.frames("0-7", 3), 0.7},
        bunraku::Animation {g32.frames(20, "7-10", 20, "9-6"), 0.8f},
        bunraku::Animation {g32.frames("0-7", 4), 0.9}
    };

    auto g64 = bunraku::Grid{64, 64, 299, 101, 2};

    auto plane = bunraku::Animation{g64.frames(0, "0-2"), 0.1f};
    auto seaplane = bunraku::Animation{g64.frames("1-3", 2), 0.1f};
    auto seaplane_angle = 0.0f;

    auto gs = bunraku::Grid{32, 98, 366, 102, 1};

    auto submarine = bunraku::Animation{gs.frames("0-6", 0, "5-2", 0), 0.5f};

    while (!WindowShouldClose()) {
        auto dt = GetFrameTime();

        if (IsKeyPressed(KEY_SPACE)) {
            for (auto& spinner : spinning) {
                spinner.flip_h();
            }

            plane.flip_v();
            seaplane.flip_v();
            submarine.flip_v();
        }

        
        for (auto& spinner : spinning) {
            spinner.update(dt);
        }

        plane.update(dt);
        seaplane.update(dt);
        submarine.update(dt);

        seaplane_angle += 20.0f * dt;

        BeginDrawing();
        ClearBackground(BLACK);

        auto i = 0;
        for (auto& spinner : spinning) {
            bunraku::raylib::draw(spinner, texture, i * 75, i * 50);
            i++;
        }

        bunraku::raylib::draw(plane, texture, 100, 400);
        bunraku::raylib::draw(seaplane, texture, 250, 432, seaplane_angle);
        bunraku::raylib::draw(submarine, texture, 600, 100);

        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();
}
