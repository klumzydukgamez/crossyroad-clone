/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_main.h"
#include "cr_logger.h"
#include <new>

bool cr::main::init() {
	if (!m_window.init()) {
		cr::logger::fail("Failed to init window.");
		return false;
	}

	m_window.push_callback({m_keyboard.window_callback, &m_keyboard});
	m_window.push_callback({m_mouse.window_callback, &m_mouse});
	m_window.push_callback({m_quit_callback, this});

	return true;
}

void cr::main::cleanup() {
	m_window.cleanup();
}

void cr::main::run() {
	while (m_running) {
		m_clock.tick(&m_window);
		m_keyboard.update(m_clock.get_ticks());
		m_mouse.update(m_clock.get_ticks());

		m_window.poll_events();

		m_window.swap_buffers();
	}
}

void cr::main::m_quit_callback(const SDL_Event& event, void* data) {
	auto* main = static_cast<cr::main*>(data);
	if (!main) {
		cr::logger::fail("Null main.");
		return;
	}
	if (event.type == SDL_EVENT_QUIT) {
		cr::logger::inform("Quit event caught.");
		main->m_running = false;
	}
}

int main(int argc, char* argv[]) {
	void* memory = SDL_aligned_alloc(alignof(cr::main), sizeof(cr::main));
	if (!memory) {
		cr::logger::fail("Failed to allocate main memory.");
		return 1;
	}
	auto* main = new (memory) cr::main();

	if (!main->init()) {
		cr::logger::fail("Failed to init main.");
		cr::logger::inform("Cleaning up main.");
		main->cleanup();
		main->~main();
		SDL_free(memory);
		return 1;
	}

	cr::logger::inform("Running main.");
	main->run();

	cr::logger::inform("Cleanup up main.");
	main->cleanup();
	main->~main();
	SDL_free(memory);
	return 0;
}
