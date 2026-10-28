/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#if !defined CR_CLOCK_H
#define CR_CLOCK_H

#include "cr_third_party.h"
#include "cr_window.h"

namespace cr {

class clock {
public:
	void tick(cr::window* window = nullptr);

	uint64_t get_ticks() const;
	uint32_t get_fps() const;

private:
	static constexpr int m_FPS = 60;
	static constexpr Uint64 m_MAX_TICKS = 250'000'000;
	static constexpr Uint64 m_FRAME_TICKS = 1'000'000'000 / m_FPS;
	static constexpr Uint64 m_FPS_TICKS = 1'000'000'000;

	Uint64 m_lastTicks = 0;
	Uint64 m_accumulatedTicks = 0;
	uint64_t m_ticks = 0;

	Uint64 m_fpsTicks = 0;
	uint32_t m_accumulatedFps = 0;
	uint32_t m_fps = 0;
};

} /* namespace cr */

#endif /* CR_CLOCK_H */
