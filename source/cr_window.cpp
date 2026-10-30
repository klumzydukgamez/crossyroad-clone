/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_window.h"
#include "cr_logger.h"

bool cr::window::init() {
	for (int i = 0; i < m_MAX_CALLBACKS; i++)
		m_availableCallbacks[i] = true;

	if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
		cr::logger::fail("Failed to init SDL video sub system.");
		cr::logger::trace_sdl();
		return true;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	m_handle = SDL_CreateWindow("crossyroad-clone", WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	if (!m_handle) {
		cr::logger::fail("Failed to create SDL window.");
		cr::logger::trace_sdl();
		return true;
	}

	m_glContext = SDL_GL_CreateContext(m_handle);
	if (!m_glContext) {
		cr::logger::fail("Failed to create SDL GL context.");
		cr::logger::trace_sdl();
		return true;
	}
	SDL_GL_MakeCurrent(m_handle, m_glContext);

	return true;
}

void cr::window::cleanup() {
	if (m_glContext)
		SDL_GL_DestroyContext(m_glContext);
	if (m_handle)
		SDL_DestroyWindow(m_handle);
}

void cr::window::swap_buffers() {
	SDL_GL_SwapWindow(m_handle);
}

void cr::window::poll_events() {
	SDL_Event event;
	while (SDL_PollEvent(&event))
		fire_event(event);
}

void cr::window::fire_event(const SDL_Event& event) {
	for (int i = 0; i < m_MAX_CALLBACKS; i++) {
		cr::window_callback callback = m_callbacks[i];
		if (callback.function)
			callback.function(event, callback.data);
	}
}

bool cr::window::push_callback(const cr::window_callback& callback, int* index) {
	for (int i = 0; i < m_MAX_CALLBACKS; i++) {
		if (m_availableCallbacks[i]) {
			m_callbacks[i] = callback;
			m_availableCallbacks[i] = false;
			if (index)
				*index = i;
			return true;
		}
	}
	cr::logger::warn("Failed to push window callback.");
	return false;
}

void cr::window::pop_callback(int index) {
	for (int i = 0; i < m_MAX_CALLBACKS; i++) {
		if (!m_availableCallbacks[i]) {
			m_callbacks[i] = {};
			m_availableCallbacks[i] = true;
			return;
		}
	}
	cr::logger::warn("Failed to pop window callback.");
}

void cr::window::set_title(const char* title) {
	SDL_SetWindowTitle(m_handle, title);
}
