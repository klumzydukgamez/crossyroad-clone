/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#if !defined CR_MOUSE_H
#define CR_MOUSE_H

#include "cr_window.h"

namespace cr {

class mouse {
public:
	static void window_callback(const SDL_Event& event, void* data);

	void update(uint64_t ticks);

	bool is_down(int button) const;
	bool is_up(int button) const;
	bool is_pressed(int button) const;
	bool is_released(int button) const;
	bool is_held(int button, uint64_t timeout = 15) const;

private:
	static constexpr bool m_is_invalid_button(int button);

	static constexpr int m_BUTTON_COUNT = 6;

	uint64_t m_ticks = 0;
	bool m_buttons[m_BUTTON_COUNT] = {};
	bool m_prevButtons[m_BUTTON_COUNT] = {};
	uint64_t m_timestamps[m_BUTTON_COUNT] = {};
};

} /* namespace cr */

#endif /* CR_MOUSE_H */
