#include "bunraku.hpp"

#include <cstdlib>
#include <sstream>
#include <variant>

#include "rapture.hpp"

bunraku::Interval bunraku::internal::parse_interval(IntervalT interval) {
    if (std::holds_alternative<Interval>(interval)) {
        return std::get<Interval>(interval);
    } else if (std::holds_alternative<int>(interval)) {
        auto val = std::get<int>(interval);
        return {val, val, true};
    } else if (std::holds_alternative<std::string>(interval)) {
        return parse_interval_string(std::get<std::string>(interval));
    }
    assert(false, "this point should be unreachable");
}

bunraku::Interval bunraku::internal::parse_interval_string(std::string interval_str) {
    auto parts = split(interval_str, '-');
    assert(parts.size() == 2, "Could not parse interval string from, expected format 'X-Y'");

    auto a = atoi(parts[0].c_str());
    auto b = atoi(parts[1].c_str());

    return {a, b, a < b};
}

std::vector<std::string> bunraku::internal::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream token_stream(str);

    while (std::getline(token_stream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

bunraku::Grid::Grid(int frame_width, int frame_height, int left, int top, int border) :
    m_frame_width(frame_width), m_frame_height(frame_height), m_left(left), m_top(top), m_border(border) {}

std::vector<bunraku::FrameRect> bunraku::Grid::frames_impl(std::vector<IntervalT> intervals) const {
    std::vector<bunraku::FrameRect> frames;

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

bunraku::Animation::Animation(
    std::vector<bunraku::FrameRect> frames,
    float duration,
    bool playing,
    bool oneshot,
    bool flip_h,
    bool flip_v,
    std::optional<bunraku::OnFinishedFn> on_finished
) :
    m_frames(frames), m_duration(duration), m_playing(playing), m_oneshot(oneshot), m_flip_h(flip_h), m_flip_v(flip_v),
    m_on_finished(on_finished), m_index(0), m_time(0.0f) {}

void bunraku::Animation::update(float dt) {
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

const bunraku::FrameRect& bunraku::Animation::current_frame() const {
    return m_frames[m_index];
}

bool bunraku::Animation::is_playing() const {
    return m_playing;
}

void bunraku::Animation::resume() {
    m_playing = true;
}

void bunraku::Animation::pause() {
    m_playing = false;
}

void bunraku::Animation::flip_h() {
    m_flip_h = !m_flip_h;
}

void bunraku::Animation::flip_v() {
    m_flip_v = !m_flip_v;
}

bool bunraku::Animation::is_flipped_h() const {
    return m_flip_h;
}

bool bunraku::Animation::is_flipped_v() const {
    return m_flip_v;
}
