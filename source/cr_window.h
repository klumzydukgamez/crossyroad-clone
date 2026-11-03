/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#if !defined CR_WINDOW_H
#define CR_WINDOW_H

#include "cr_third_party.h"

namespace cr {

struct window_callback {
	void (*function)(const SDL_Event& event, void* data) = nullptr;
	void* data = nullptr;
};

class window {
public:
	static constexpr int WIDTH = 540; /* 9 * n */
	static constexpr int HEIGHT = 960; /* 16 * n */
	static constexpr float RATIO = static_cast<float>(WIDTH) / static_cast<float>(HEIGHT);

	bool init();
	void cleanup();

	int push_callback(const cr::window_callback& callback);
	void pop_callback(int index);
	void fire_event(const SDL_Event& event);

	void poll_events();
	void swap_buffers();

private:
	static constexpr int m_CALLBACKS_SIZE = 16;

	SDL_Window* m_window = nullptr;
	SDL_GLContext m_glContext = nullptr;
	SDL_Event m_event = {};

	cr::window_callback m_callbacks[m_CALLBACKS_SIZE] = {};
};

} /* namespace cr */

#endif /* CR_WINDOW_H */
