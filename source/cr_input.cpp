/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_input.h"
#include "cr_logger.h"

void cr::input::window_callback(const SDL_Event& event, void* data) {
	auto* input = static_cast<cr::input*>(data);
	if (!input)
		return;
	switch (event.type) {
		case SDL_EVENT_KEY_DOWN:
			if (event.key.repeat || m_is_invalid_key(event.key.scancode))
				break;
			input->m_keys[event.key.scancode] = true;
			break;
		case SDL_EVENT_KEY_UP:
			if (m_is_invalid_key(event.key.scancode))
				break;
			input->m_keys[event.key.scancode] = false;
			break;
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (m_is_invalid_btn(event.button.button))
				break;
			input->m_btns[event.button.button] = true;
			break;
		case SDL_EVENT_MOUSE_BUTTON_UP:
			if (m_is_invalid_btn(event.button.button))
				break;
			input->m_btns[event.button.button] = false;
			break;
		default:
			break;
	}
}

void cr::input::update() {
	SDL_memcpy(m_prevKeys, m_keys, sizeof(m_prevKeys));
	SDL_memcpy(m_prevBtns, m_btns, sizeof(m_prevBtns));
}

bool cr::input::is_key_down(int key) const {
	if (m_is_invalid_key(key)) {
		cr::logger::warn("Invalid key.");
		return false;
	}
	return m_keys[key];
}

bool cr::input::is_key_up(int key) const {
	if (m_is_invalid_key(key)) {
		cr::logger::warn("Invalid key.");
		return false;
	}
	return !m_keys[key];
}

bool cr::input::is_key_pressed(int key) const {
	if (m_is_invalid_key(key)) {
		cr::logger::warn("Invalid key.");
		return false;
	}
	return m_keys[key] && !m_prevKeys[key];
}

bool cr::input::is_key_released(int key) const {
	if (m_is_invalid_key(key)) {
		cr::logger::warn("Invalid key.");
		return false;
	}
	return !m_keys[key] && m_prevKeys[key];
}

bool cr::input::is_btn_down(int btn) const {
	if (m_is_invalid_btn(btn)) {
		cr::logger::warn("Invalid btn.");
		return false;
	}
	return m_btns[btn];
}

bool cr::input::is_btn_up(int btn) const {
	if (m_is_invalid_btn(btn)) {
		cr::logger::warn("Invalid btn.");
		return false;
	}
	return !m_btns[btn];
}

bool cr::input::is_btn_pressed(int btn) const {
	if (m_is_invalid_btn(btn)) {
		cr::logger::warn("Invalid btn.");
		return false;
	}
	return m_btns[btn] && !m_prevBtns[btn];
}

bool cr::input::is_btn_released(int btn) const {
	if (m_is_invalid_btn(btn)) {
		cr::logger::warn("Invalid btn.");
		return false;
	}
	return !m_btns[btn] && m_prevBtns[btn];
}

constexpr bool cr::input::m_is_invalid_key(int key) {
	return (key < 0 || key >= m_KEY_COUNT);
}

constexpr bool cr::input::m_is_invalid_btn(int btn) {
	return (btn < 0 || btn >= m_KEY_COUNT);
}
