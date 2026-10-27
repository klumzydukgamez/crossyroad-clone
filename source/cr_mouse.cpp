/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_mouse.h"

void cr::mouse::window_callback(const SDL_Event& event, void* data) {
	auto* mouse = static_cast<cr::mouse*>(data);
	if (!mouse) {
		SDL_Log("Null mouse.");
		return;
	}
	switch (event.type) {
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (m_is_invalid_button(event.button.button))
				break;
			mouse->m_buttons[event.button.button] = true;
			mouse->m_timestamps[event.button.button] = mouse->m_ticks;
			break;
		case SDL_EVENT_MOUSE_BUTTON_UP:
			if (m_is_invalid_button(event.button.button))
				break;
			mouse->m_buttons[event.button.button] = false;
			break;
	}
}

void cr::mouse::update(uint64_t ticks) {
	m_ticks = ticks;
	SDL_memcpy(m_prevButtons, m_buttons, sizeof(m_prevButtons));
}

bool cr::mouse::is_down(int button) const {
	if (m_is_invalid_button(button)) {
		SDL_Log("Invalid button.");
		return false;
	}
	return m_buttons[button];
}

bool cr::mouse::is_up(int button) const {
	if (m_is_invalid_button(button)) {
		SDL_Log("Invalid button.");
		return false;
	}
	return !m_buttons[button];
}

bool cr::mouse::is_pressed(int button) const {
	if (m_is_invalid_button(button)) {
		SDL_Log("Invalid button.");
		return false;
	}
	return m_buttons[button] && !m_prevButtons[button];
}

bool cr::mouse::is_released(int button) const {
	if (m_is_invalid_button(button)) {
		SDL_Log("Invalid button.");
		return false;
	}
	return !m_buttons[button] && m_prevButtons[button];
}

bool cr::mouse::is_held(int button, uint64_t timeout) const {
	if (m_is_invalid_button(button)) {
		SDL_Log("Invalid button.");
		return false;
	}
	if (!m_buttons[button])
		return false;
	return (m_ticks - m_timestamps[button]) >= timeout;
}

constexpr bool cr::mouse::m_is_invalid_button(int button) {
	return (button < 0 || button >= m_BUTTON_COUNT);
}
