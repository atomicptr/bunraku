build:
    cmake -B build
    cmake --build build -j8

anim8_1945: build
    cd examples/anim8_1945 && ../../build/anim8_1945

cat_fighter_fsm: build
    cd examples/cat_fighter_fsm && ../../build/cat_fighter_fsm
