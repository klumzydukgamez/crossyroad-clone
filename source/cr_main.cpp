/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_main.h"
#include "cr_crash_reporter.h"
#include "cr_opengl_reporter.h"
#include "cr_logger.h"
#include "cr_assets.h"

bool cr::main::init() {
	cr::crash_reporter::init();

	if (!m_window.init()) {
		cr::logger::fail("Failed to init window.");
		return false;
	}

	m_window.push_callback({m_quit_callback, this});
	m_window.push_callback({m_input.window_callback, &m_input});

	cr::opengl_reporter::init();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	if (!m_shader.init(cr::assets::test_vert, cr::assets::test_frag)) {
		cr::logger::fail("Failed to init shader.");
		return false;
	}

	glGenVertexArrays(1, &m_vao);

	return true;
}

void cr::main::cleanup() {
	m_shader.cleanup();
	m_window.cleanup();
	if (m_vao)
		glDeleteVertexArrays(1, &m_vao);
}

void cr::main::run() {
	while (m_running) {
		m_window.poll_events();

		m_clock.tick();

		while (m_clock.step()) {
			m_camera.set_target_position(glm::vec3(sin(m_clock.get_ticks() * 0.01) * 100.0, 0.0f, cos(m_clock.get_ticks() * 0.01) * 100.0));
			m_camera.update(m_clock.get_delta_step_time());

			m_input.update();
		}

		m_camera.calculate_matrices(m_clock.get_delta_frame_time());

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_shader.use();

		m_shader.set_uniform(cr::shader::uniform::uProjectionView, m_camera.get_projection_view());
		glm::mat4 model = {1.0f};
		model = glm::translate(model, glm::vec3(cr::window::WIDTH / 2.0f, cr::window::HEIGHT / 2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
		model = glm::rotate(model, static_cast<float>(sin(m_clock.get_ticks() * 0.01)), glm::vec3(0.0f, 1.0f, 0.0f));
		m_shader.set_uniform(cr::shader::uniform::uModel, model);

		glBindVertexArray(m_vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

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
