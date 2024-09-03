CC = g++

CPP_FLAGS = -std=c++23 -lraylib

.PHONY: anim8_1945 cat_fighter_fsm

anim8_1945:
	$(CC) $(CPP_FLAGS) examples/anim8_1945/src/main.cpp src/bunraku.cpp src/bunraku_raylib.cpp -o examples/anim8_1945/anim8_1945
	cd examples/anim8_1945 && ./anim8_1945

cat_fighter_fsm:
	$(CC) $(CPP_FLAGS) examples/cat_fighter_fsm/src/main.cpp src/bunraku.cpp src/bunraku_raylib.cpp -o examples/cat_fighter_fsm/cat_fighter_fsm
	cd examples/cat_fighter_fsm && ./cat_fighter_fsm
