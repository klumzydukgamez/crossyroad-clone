/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#if !defined CR_INPUT_H
#define CR_INPUT_H

#include "cr_third_party.h"

namespace cr {

class input {
public:
	static void window_callback(const SDL_Event& event, void* data);

	void update();

	bool is_key_down(int key) const;
	bool is_key_up(int key) const;
	bool is_key_pressed(int key) const;
	bool is_key_released(int key) const;

	bool is_btn_down(int btn) const;
	bool is_btn_up(int btn) const;
	bool is_btn_pressed(int btn) const;
	bool is_btn_released(int btn) const;

private:
	static constexpr bool m_is_invalid_key(int key);
	static constexpr bool m_is_invalid_btn(int btn);

	static constexpr int m_KEY_COUNT = SDL_SCANCODE_COUNT;
	static constexpr int m_BTN_COUNT = 6;

	bool m_keys[m_KEY_COUNT] = {};
	bool m_prevKeys[m_KEY_COUNT] = {};
	bool m_btns[m_BTN_COUNT] = {};
	bool m_prevBtns[m_BTN_COUNT] = {};
};

} /* namespace cr */

#endif /* CR_INPUT_H */
