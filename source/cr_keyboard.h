/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#if !defined CR_KEYBOARD_H
#define CR_KEYBOARD_H

#include "cr_window.h"

namespace cr {

class keyboard {
public:
	static void window_callback(const SDL_Event& event, void* data);

	void update(uint64_t ticks);

	bool is_down(int key) const;
	bool is_up(int key) const;
	bool is_pressed(int key) const;
	bool is_released(int key) const;
	bool is_held(int key, uint64_t timeout = 15) const;

private:
	static constexpr bool m_is_invalid_key(int key);

	static constexpr int m_KEY_COUNT = SDL_SCANCODE_COUNT;

	uint64_t m_ticks = 0;
	bool m_keys[m_KEY_COUNT] = {};
	bool m_prevKeys[m_KEY_COUNT] = {};
	uint64_t m_timestamps[m_KEY_COUNT] = {};
};

} /* namespace cr */

#endif /* CR_KEYBOARD_H */
