# bunraku (文楽)

A 2D animation library for making games with C++23

Inspired by the LÖVE library [anim8](https://github.com/kikito/anim8) and the Odin library [anima](https://github.com/atomicptr/anima).

## Compatibility

This library is implemented to be renderer agnostic, however there is a raylib implementation available in src/bunraku\_raylib.hpp/cpp.

## Installation

Copy the files into your project :)

## Usage

Check out one of the examples:

- [anim8 1945 example](./examples/anim8_1945/src/main.cpp) (port of the anim8 demo)
- [cat fighter fsm](./examples/cat_fighter_fsm/src/main.cpp) - Animations with a finite state machine

### Simple example

```cpp
#include <raylib.h>
#include <bunraku/bunraku.hpp>
#include <bunraku/bunraku_raylib.hpp>

int main() {
    InitWindow(800, 600, "Simple Example");
    SetTargetFPS(60);

    auto image = LoadImage("path/to/image.png");
    auto texture = LoadTextureFromImage(image);
    UnloadImage(image);

    // first we need to define our grid
    auto grid = bunraku::Grid{32, 32};

    auto animation = bunraku::Animation{
        // here we specify we want column: 0-7 in row: 0
        grid.frames("0-7", 0),
        // and the animation speed is 0.1s
        0.1f
    };

    while (!WhileWindowShouldClose()) {
        auto dt = GetFrameTime();

        // update the animation before drawing
        animation.update(dt);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // and finally draw the animation
        bunraku::raylib::draw(animation, texture, 100, 100);

        EndDrawing();
    }

    UnloadTexture(texture);
    WindowClose();

    return 0;
}
```

## Documentation

### Grids

Grids exist to make it as easy as possible to quickly define animations using rectangles of teh same size.

Grids are defined like this:

```cpp

bunraku::Grid(
    int frame_width,  // the width of the frame
    int frame_height, // the height of the frame
    int left = 0,     // (optional) starting x position of our grid, this is used to define multiple grids within a single file
    int top = 0,      // (optional) starting y position of our grid, this is used to define multiple grids within a single file 
    int border = 0    // (optional) this allows you to define gaps between images
);

```

![](./.github/images/grid_example.png)
(Took this explanation from the anim8 repo)

To get frames from a grid you need to call the ``Grid::frames`` function

```cpp

auto grid = bunraku::Grid{32, 32};

grid.frames(
    column_interval_range_0, // the defined column range of our animation
    row_interval_range_0,    // the defined row range of our animation
    column_interval_range_1, // the defined column range of our animation
    row_interval_range_1,    // the defined row range of our animation
    column_interval_range_2, // the defined column range of our animation
    row_interval_range_2,    // the defined row range of our animation
    // ...
);

```

### Animations

Animations are a group of frames that change after a set duration

```cpp

bunraku::Animation(
    std::vector<FrameRect> frames,               // the frames to play, this should be supplied using grids
    float duration,                              // the duration each frame will take until the next one will play
    bool playing = true,                         // (optional) is the animation playing? Default is true
    bool oneshot = false,                        // (optional) should the animation only play once? Default is false
    bool flip_h = false,                         // (optional) flip horizontally
    bool flip_v = false,                         // (optional) flip vertically
    std::optional<OnFinishedFn> on_finished = {} // (optional) a callback that will be called every time the current animation has finished
);

```

## Assets

- examples/anim8_1945/assets/1945.png - [Widgetworx Spritelib](http://www.widgetworx.com/widgetworx/portfolio/spritelib.html)
- examples/cat_fighter_fsm/assets/cat_fighter.png - [dogchicken from opengameart.org](https://opengameart.org/content/cat-fighter-sprite-sheet)


## License

BSD 0-Clause
