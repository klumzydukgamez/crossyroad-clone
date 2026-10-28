/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_clock.h"

void cr::clock::tick(cr::window* window) {
	Uint64 currentTicks = SDL_GetTicksNS();
	if (m_lastTicks == 0)
		m_lastTicks = currentTicks;
	Uint64 elapsedTicks = currentTicks - m_lastTicks;
	m_lastTicks = currentTicks;
	if (elapsedTicks >= m_MAX_TICKS)
		elapsedTicks = m_MAX_TICKS;
	m_accumulatedTicks += elapsedTicks;
	m_fpsTicks += elapsedTicks;
	m_accumulatedFps++;
	if (m_fpsTicks >= m_FPS_TICKS) {
		m_fps = m_accumulatedFps;
		m_accumulatedFps = 0;
		m_fpsTicks %= m_FPS_TICKS;
		if (window) {
			char buffer[32];
			SDL_snprintf(buffer, sizeof(buffer), "crossyroad-clone | %d", m_fps);
			window->set_title(buffer);
		}
	}
}

uint64_t cr::clock::get_ticks() const {
	return m_ticks;
}

uint32_t cr::clock::get_fps() const {
	return m_fps;
}
