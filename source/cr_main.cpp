/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_main.h"
#include "cr_crash_reporter.h"
#include "cr_logger.h"

bool cr::main::init() {
	cr::crash_reporter::init();

	if (!m_window.init()) {
		cr::logger::fail("Failed to init window.");
		return false;
	}

	m_window.push_callback({m_quit_callback, this});

	return true;
}

void cr::main::cleanup() {
	m_window.cleanup();
}

void cr::main::run() {
	while (m_running) {
		m_window.poll_events();

		m_clock.tick();

		while (m_clock.step()) {
			m_camera.update(m_clock.get_delta_step_time());
			m_camera.set_target_position({100.0f, 0.0f, 100.0f});
		}

		m_camera.calculate_matrices(m_clock.get_delta_frame_time());

		m_window.swap_buffers();
	}
}

void cr::main::m_quit_callback(const SDL_Event& event, void* data) {
	auto* main = static_cast<cr::main*>(data);
	if (!main)
		return;
	if (event.type == SDL_EVENT_QUIT)
		main->m_running = false;
}

int main(int argc, char* argv[]) {
	void* memory = SDL_malloc(sizeof(cr::main));
	if (!memory) {
		cr::logger::fail("Failed to allocate main memory.");
		return -1;
	}
	auto* main = ::new (memory) cr::main();

	if (!main->init()) {
		main->cleanup();
		main->~main();
		SDL_free(memory);
		return 1;
	}

	main->run();

	main->cleanup();
	main->~main();
	SDL_free(memory);

	return 0;
}
