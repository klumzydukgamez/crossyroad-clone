/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_window.h"
#include "cr_keyboard.h"

void quit_callback(const SDL_Event& event, void* data) {
	if (event.type == SDL_EVENT_QUIT) {
		auto* running = static_cast<bool*>(data);
		if (!running)
			return;
		*running = false;
	}
}

int main(int argc, char* argv[]) {
	cr::window window;

	if (!window.init()) {
		window.cleanup();
		return 1;
	}

	bool running = true;
	window.push_callback({quit_callback, &running});

	cr::keyboard keyboard;
	window.push_callback({keyboard.window_callback, &keyboard});

	while (running) {
		keyboard.update(0);

		window.poll_events();

		if (keyboard.was_released(SDL_SCANCODE_SPACE))
			SDL_Log("SPACE");

		window.swap_buffers();
	}

	window.cleanup();

	return 0;
}
