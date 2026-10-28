/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_window.h"
#include "cr_clock.h"
#include "cr_keyboard.h"
#include "cr_mouse.h"
#include "cr_shader.h"

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
	cr::clock clock;
	cr::keyboard keyboard;
	cr::mouse mouse;
	cr::shader shader;
	bool running = true;

	if (!window.init()) {
		window.cleanup();
		return 1;
	}

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress))) {
		window.cleanup();
		return 1;
	}

	window.push_callback({keyboard.window_callback, &keyboard});
	window.push_callback({mouse.window_callback, &mouse});
	window.push_callback({quit_callback, &running});

	if (!shader.init("", ""))
		shader.cleanup();

	while (running) {
		clock.tick(&window);
		keyboard.update(clock.get_ticks());
		mouse.update(clock.get_ticks());

		window.poll_events();

		window.swap_buffers();
	}

	shader.cleanup();
	window.cleanup();
	return 0;
}
