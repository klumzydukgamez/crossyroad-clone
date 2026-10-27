/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_keyboard.h"

void cr::keyboard::window_callback(const SDL_Event& event, void* data) {
	auto* keyboard = static_cast<cr::keyboard*>(data);
	if (!keyboard) {
		SDL_Log("Null keyboard.");
		return;
	}
	switch (event.type) {
		case SDL_EVENT_KEY_DOWN:
			if (event.key.repeat || m_is_invalid_key(event.key.scancode))
				break;
			keyboard->m_keys[event.key.scancode] = true;
			keyboard->m_timestamps[event.key.scancode] = keyboard->m_ticks;
			break;
		case SDL_EVENT_KEY_UP:
			if (m_is_invalid_key(event.key.scancode))
				break;
			keyboard->m_keys[event.key.scancode] = false;
			break;
	}
}

void cr::keyboard::update(uint64_t ticks) {
	m_ticks = ticks;
	SDL_memcpy(m_prevKeys, m_keys, sizeof(m_prevKeys));
}

bool cr::keyboard::is_down(int key) const {
	if (m_is_invalid_key(key)) {
		SDL_Log("Invalid key.");
		return false;
	}
	return m_keys[key];
}

bool cr::keyboard::is_up(int key) const {
	if (m_is_invalid_key(key)) {
		SDL_Log("Invalid key.");
		return false;
	}
	return !m_keys[key];
}

bool cr::keyboard::is_pressed(int key) const {
	if (m_is_invalid_key(key)) {
		SDL_Log("Invalid key.");
		return false;
	}
	return m_keys[key] && !m_prevKeys[key];
}

bool cr::keyboard::is_released(int key) const {
	if (m_is_invalid_key(key)) {
		SDL_Log("Invalid key.");
		return false;
	}
	return !m_keys[key] && m_prevKeys[key];
}

bool cr::keyboard::is_held(int key, uint64_t timeout) const {
	if (m_is_invalid_key(key)) {
		SDL_Log("Invalid key.");
		return false;
	}
	if (!m_keys[key])
		return false;
	return (m_ticks - m_timestamps[key]) >= timeout;
}

constexpr bool cr::keyboard::m_is_invalid_key(int key) {
	return (key < 0 || key >= m_KEY_COUNT);
}
