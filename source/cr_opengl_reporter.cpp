/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_opengl_reporter.h"
#include "cr_third_party.h"
#include "cr_logger.h"

static void APIENTRY gl_debug_msg_callback(
	GLenum src, GLenum type, GLuint id,
	GLenum severity, GLsizei len,
	const GLchar* msg, const void* param
) {
	cr::logger::inform("OpenGL msg caught.");
}

void cr::opengl_reporter::init() {
	GLint flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (!(flags & GL_CONTEXT_FLAG_DEBUG_BIT)) {
		cr::logger::warn("Failed to retrieve debug GL context.");
		return;
	}
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(gl_debug_msg_callback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
}
