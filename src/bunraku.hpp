// This file is part of bunraku - A 2D animation library for making games with C++23
// See: https://github.com/atomicptr/bunraku
#pragma once

#include <cstdlib>
#include <functional>
#include <optional>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

#if !defined(assert) || !defined(unreachable)
    #include "rapture.hpp"
#endif

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
        inline auto split(const std::string& str, char delimiter) {
            std::vector<std::string> tokens;
            std::string token;
            std::istringstream token_stream(str);

            while (std::getline(token_stream, token, delimiter)) {
                tokens.push_back(token);
            }

            return tokens;
        }

        inline Interval parse_interval_string(std::string interval_str) {
            auto parts = split(interval_str, '-');
            assert(parts.size() == 2, "Could not parse interval string from, expected format 'X-Y'");

            auto a = atoi(parts[0].c_str());
            auto b = atoi(parts[1].c_str());

            return {a, b, a < b};
        }

        inline Interval parse_interval(IntervalT interval) {
            if (std::holds_alternative<Interval>(interval)) {
                return std::get<Interval>(interval);
            } else if (std::holds_alternative<int>(interval)) {
                auto val = std::get<int>(interval);
                return {val, val, true};
            } else if (std::holds_alternative<std::string>(interval)) {
                return parse_interval_string(std::get<std::string>(interval));
            }
            unreachable();
        }
    }

    class Grid {
      public:
        Grid(int frame_width, int frame_height, int left = 0, int top = 0, int border = 0) :
            m_frame_width(frame_width), m_frame_height(frame_height), m_left(left), m_top(top), m_border(border) {}

        template <class... T>
        auto frames(T... frame_intervals) const {
            static_assert(
                sizeof...(frame_intervals) % 2 == 0,
                "Intervals are interpreted as (column, row) pairs but you did not provide an even amount of parameters"
            );

            auto intervals = std::vector<IntervalT> {std::forward<IntervalT>(frame_intervals)...};

            std::vector<FrameRect> frames;

            auto cond = [](int index, Interval interval) -> bool {
                if (interval.forward) {
                    return index <= interval.to;
                }
                return index >= interval.to;
            };

            for (size_t i = 0; i < intervals.size(); i += 2) {
                auto column = internal::parse_interval(intervals[i]);
                auto row = internal::parse_interval(intervals[i + 1]);

                for (int y = row.from; cond(y, row); y += (row.forward ? 1 : -1)) {
                    for (int x = column.from; cond(x, column); x += (column.forward ? 1 : -1)) {
                        frames.emplace_back(
                            m_left + x * m_frame_width + (x + 1) * m_border,
                            m_top + y * m_frame_height + (y + 1) * m_border,
                            m_frame_width,
                            m_frame_height
                        );
                    }
                }
            }

            return frames;
        }

      private:
        int m_frame_width;
        int m_frame_height;
        int m_left;
        int m_top;
        int m_border;
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
        ) :
            m_frames(frames), m_duration(duration), m_playing(playing), m_oneshot(oneshot), m_flip_h(flip_h),
            m_flip_v(flip_v), m_on_finished(on_finished), m_index(0), m_time(0.0f) {}

        void update(float dt) {
            if (!m_playing) {
                return;
            }

            m_time += dt;

            if (m_time >= m_duration) {
                m_index = (m_index + 1) % m_frames.size();
                m_time = 0.0;

                if (m_on_finished.has_value()) {
                    m_on_finished.value()(this);
                }

                if (m_oneshot) {
                    m_playing = false;
                }
            }
        }

        const FrameRect& current_frame() const {
            return m_frames[m_index];
        }

        void play() {
            m_playing = true;
            m_index = 0;
        }

        void resume() {
            m_playing = true;
        }

        void pause() {
            m_playing = false;
        }

        void flip_h() {
            m_flip_h = !m_flip_h;
        }

        void flip_v() {
            m_flip_v = !m_flip_v;
        }

        bool is_playing() const {
            return m_playing;
        }

        bool is_flipped_h() const {
            return m_flip_h;
        }

        bool is_flipped_v() const {
            return m_flip_v;
        }

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
