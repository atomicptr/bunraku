// This file is part of bunraku - A 2D animation library for making games with C++23
// See: https://github.com/atomicptr/bunraku
#pragma once

#include <optional>
#include <unordered_map>

#include "bunraku.hpp"

#if !defined(assert) || !defined(unreachable)
    #include "rapture.hpp"
#endif

namespace bunraku {
    template <typename T>
    class FSM {
      public:
        FSM() : current({}), states({}) {}

        void add(T ident, Animation animation) {
            assert(!states.contains(ident), "There is already an animation registered for this identifier!");
            states.insert_or_assign(ident, animation);
        }

        void play(T ident) {
            if (ident == current) {
                return;
            }

            if (current.has_value()) {
                pause();
            }

            assert(states.contains(ident), "Unknown animation");

            current = ident;
            states.at(ident).play();
        }

        void resume() {
            assert(current.has_value(), "No animation selected");
            assert(states.contains(current.value()), "Unknown animation");
            states.at(current.value()).resume();
        }

        void pause() {
            assert(current.has_value(), "No animation selected");
            assert(states.contains(current.value()), "Unknown animation");
            states.at(current.value()).pause();
        }

        void update(float dt) {
            assert(current.has_value(), "No animation selected");
            assert(states.contains(current.value()), "Unknown animation");
            states.at(current.value()).update(dt);
        }

        const Animation& current_animation() const {
            assert(current.has_value(), "No animation selected");
            assert(states.contains(current.value()), "Unknown animation");
            return states.at(current.value());
        }

      private:
        std::optional<T> current;
        std::unordered_map<T, Animation> states;
    };
}
