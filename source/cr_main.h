/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#if !defined CR_MAIN_H
#define CR_MAIN_H

#include "cr_window.h"
#include "cr_clock.h"
#include "cr_camera.h"

namespace cr {

class main {
public:
	bool init();
	void cleanup();

	void run();

private:
	static void m_quit_callback(const SDL_Event& event, void* data);

	bool m_running = true;

	cr::window m_window = {};
	cr::clock m_clock = {};
	cr::camera m_camera = {};
};

} /* namespace cr */

#endif /* CR_MAIN_H */
