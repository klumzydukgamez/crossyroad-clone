/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#if !defined CR_CLOCK_H
#define CR_CLOCK_H

#include "cr_third_party.h"

namespace cr {

class clock {
public:
	void tick();

	float get_delta_step_time();
	float get_delta_frame_time();

private:
	static constexpr int m_FPS = 60;
	static constexpr Uint64 m_STEP_TICKS = 1'000'000'000 / m_FPS;
	static constexpr Uint64 m_MAX_ELAPSED_TICKS = m_STEP_TICKS * 8;

	Uint64 m_lastTicks = 0;
	Uint64 m_accumulatedTicks = 0;
	Uint64 m_ticks = 0;
};

} /* namespace cr */

#endif /* CR_CLOCK_H */
