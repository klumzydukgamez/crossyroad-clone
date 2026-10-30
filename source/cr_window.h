/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#if !defined CR_WINDOW_H
#define CR_WINDOW_H

#include "cr_third_party.h"

namespace cr {

struct window_callback {
	void (*function)(const SDL_Event&, void*) = nullptr;
	void* data = nullptr;
};

class window {
public:
	static constexpr int WIDTH = 360;
	static constexpr int HEIGHT = 640;
	static constexpr float HALF_WIDTH = WIDTH / 2.0f;
	static constexpr float HALF_HEIGHT = HEIGHT / 2.0f;
	static constexpr float RATIO = static_cast<float>(WIDTH) / static_cast<float>(HEIGHT);

	bool init();
	void cleanup();

	void swap_buffers();

	void poll_events();
	void fire_event(const SDL_Event& event);

	bool push_callback(const cr::window_callback& callback, int* index = nullptr);
	void pop_callback(int index);

	void set_title(const char* title);

private:
	static constexpr int m_MAX_CALLBACKS = 16;

	SDL_Window* m_handle = nullptr;
	SDL_GLContext m_glContext = nullptr;
	cr::window_callback m_callbacks[m_MAX_CALLBACKS] = {};
	bool m_availableCallbacks[m_MAX_CALLBACKS] = {};
};

} /* namespace cr */

#endif /* CR_WINDOW_H */
