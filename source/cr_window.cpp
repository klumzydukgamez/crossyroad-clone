/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_window.h"
#include "cr_logger.h"

bool cr::window::init() {
	if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
		cr::logger::fail("Failed to init SDL video sub system.");
		cr::logger::trace_sdl();
		return false;
	}

	if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4)) {
		cr::logger::warn("Failed to set SDL GL major version attribute.");
		cr::logger::trace_sdl();
	}
	if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6)) {
		cr::logger::warn("Failed to set SDL GL minor version attribute.");
		cr::logger::trace_sdl();
	}
	if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE)) {
		cr::logger::warn("Failed to set SDL GL profile mask attribute.");
		cr::logger::trace_sdl();
	}

	m_window = SDL_CreateWindow("crossyroad-clone", WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	if (!m_window) {
		cr::logger::fail("Failed to create SDL window.");
		cr::logger::trace_sdl();
		return false;
	}

	m_glContext = SDL_GL_CreateContext(m_window);
	if (!m_glContext) {
		cr::logger::fail("Failed to create SDL GL context.");
		cr::logger::trace_sdl();
		return false;
	}
	SDL_GL_MakeCurrent(m_window, m_glContext);
	SDL_GL_SetSwapInterval(0);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress))) {
		cr::logger::fail("Failed to load GL.");
		return false;
	}

	return true;
}

void cr::window::cleanup() {
	if (m_glContext)
		SDL_GL_DestroyContext(m_glContext);
	if (m_window)
		SDL_DestroyWindow(m_window);
}

int cr::window::push_callback(const cr::window_callback& callback) {
	for (int i = 0; i < m_CALLBACKS_SIZE; i++) {
		if (!m_callbacks[i].function) {
			m_callbacks[i] = callback;
			return i;
		}
	}
	cr::logger::warn("Failed to push window callback.");
	return -1;
}

void cr::window::pop_callback(int index) {
	for (int i = 0; i < m_CALLBACKS_SIZE; i++) {
		if (m_callbacks[i].function) {
			m_callbacks[i] = {};
			return;
		}
	}
	cr::logger::warn("Failed to pop window callback.");
}

void cr::window::fire_event(const SDL_Event& event) {
	for (int i = 0; i < m_CALLBACKS_SIZE; i++) {
		cr::window_callback& callback = m_callbacks[i];
		if (callback.function) {
			callback.function(event, callback.data);
		}
	}
}

void cr::window::poll_events() {
	while (SDL_PollEvent(&m_event)) {
		fire_event(m_event);
	}
}

void cr::window::swap_buffers() {
	SDL_GL_SwapWindow(m_window);
}
