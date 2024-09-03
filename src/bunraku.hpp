// This file is part of bunraku - A 2D animation library for making games with C++23
// See: https://github.com/atomicptr/bunraku
#pragma once

#include <functional>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace bunraku {
    struct Interval {
        int from;
        int to;
        bool forward;
    };

    using IntervalT = std::variant<Interval, int, std::string>;

    struct FrameRect {
        int x;
        int y;
        int width;
        int height;
    };

    namespace internal {
        Interval parse_interval(IntervalT interval);
        Interval parse_interval_string(std::string interval_str);

        std::vector<std::string> split(const std::string& str, char delimiter);
    }

    class Grid {
      public:
        Grid(int frame_width, int frame_height, int left = 0, int top = 0, int border = 0);

        template <class... T>
        std::vector<FrameRect> frames(T... intervals) const {
            static_assert(
                sizeof...(intervals) % 2 == 0,
                "Intervals are interpreted as (column, row) pairs but you did not provide an even amount of parameters"
            );
            return frames_impl({intervals...});
        }

      private:
        int m_frame_width;
        int m_frame_height;
        int m_left;
        int m_top;
        int m_border;

        std::vector<FrameRect> frames_impl(std::vector<IntervalT> interval) const;
    };

    class Animation;

    using OnFinishedFn = std::function<void(Animation*)>;

    class Animation {
      public:
        Animation(
            std::vector<FrameRect> frames,
            float duration,
            bool playing = true,
            bool oneshot = false,
            bool flip_h = false,
            bool flip_v = false,
            std::optional<OnFinishedFn> on_finished = {}
        );

        void update(float dt);
        const FrameRect& current_frame() const;

        void play();
        void resume();
        void pause();

        void flip_h();
        void flip_v();

        bool is_playing() const;

        bool is_flipped_h() const;
        bool is_flipped_v() const;

      private:
        std::vector<FrameRect> m_frames;
        float m_duration;
        bool m_playing;
        bool m_oneshot;
        bool m_flip_h;
        bool m_flip_v;
        std::optional<OnFinishedFn> m_on_finished;
        int m_index;
        float m_time;
    };
}
