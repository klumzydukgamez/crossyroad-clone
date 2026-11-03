/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_clock.h"
#include "cr_logger.h"

void cr::clock::tick() {
	Uint64 current = SDL_GetTicksNS();
	Uint64 elapsed = current - m_lastTicks;
	if (elapsed >= m_MAX_ELAPSED_TICKS)
		elapsed = m_MAX_ELAPSED_TICKS;
	m_accumulatedTicks += elapsed;
	m_lastTicks = current;

	while (m_accumulatedTicks >= m_STEP_TICKS) {
		m_accumulatedTicks -= m_STEP_TICKS;
	}
}

float cr::clock::get_delta_step_time() {
	return 1.0f / m_FPS;
}

float cr::clock::get_delta_frame_time() {
	return static_cast<float>(static_cast<double>(m_accumulatedTicks) / m_STEP_TICKS);
}
