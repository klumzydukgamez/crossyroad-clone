/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_window.h"

bool cr::window::init() {
	for (int i = 0; i < m_CALLBACK_COUNT; i++)
		m_availableCallbacks[i] = true;

	if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
		SDL_Log("Failed to init SDL video sub system.");
		return false;
	}

	if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4)) {
		SDL_Log("Failed to set SDL GL attribute.");
		return false;
	}
	if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6)) {
		SDL_Log("Failed to set SDL GL attribute.");
		return false;
	}
	if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE)) {
		SDL_Log("Failed to set SDL GL attribute.");
		return false;
	}

	m_handle = SDL_CreateWindow("crossyroad-clone", WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	if (!m_handle) {
		SDL_Log("Failed to create SDL window.");
		return false;
	}

	m_glContext = SDL_GL_CreateContext(m_handle);
	if (!m_glContext) {
		SDL_Log("Faield to create SDL GL context.");
		return false;
	}
	if (!SDL_GL_MakeCurrent(m_handle, m_glContext)) {
		SDL_Log("Failed to use SDL GL context.");
		return false;
	}

	return true;
}

void cr::window::cleanup() {
	if (m_glContext)
		SDL_GL_DestroyContext(m_glContext);
	if (m_handle)
		SDL_DestroyWindow(m_handle);
}

void cr::window::swap_buffers() {
	if (!SDL_GL_SwapWindow(m_handle))
		SDL_Log("Failed to swap SDL GL window buffers.");
}

void cr::window::poll_events() {
	SDL_Event event;
	while (SDL_PollEvent(&event))
		fire_event(event);
}

void cr::window::fire_event(const SDL_Event& event) {
	for (int i = 0; i < m_CALLBACK_COUNT; i++) {
		cr::window_callback callback = m_callbacks[i];
		if (callback.function)
			callback.function(event, callback.data);
	}
}

int cr::window::push_callback(const cr::window_callback& callback) {
	for (int i = 0; i < m_CALLBACK_COUNT; i++) {
		if (m_availableCallbacks[i]) {
			m_callbacks[i] = callback;
			m_availableCallbacks[i] = false;
			return i;
		}
	}
	SDL_Log("Failed to push window callback.");
	return -1;
}

void cr::window::pop_callback(int index) {
	for (int i = 0; i < m_CALLBACK_COUNT; i++) {
		if (!m_availableCallbacks[i]) {
			m_callbacks[i] = {};
			m_availableCallbacks[i] = true;
			return;
		}
	}
	SDL_Log("Failed to pop windo callback.");
}

void cr::window::set_title(const char* title) {
	if (!SDL_SetWindowTitle(m_handle, title))
		SDL_Log("Failed to set SDL window title.");
}
