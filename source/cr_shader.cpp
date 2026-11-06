/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_shader.h"
#include "cr_logger.h"

bool cr::shader::init(const GLchar* vertSrc, const GLchar* fragSrc) {
	GLint status = 0;

	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertSrc, nullptr);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &status);
	if (!status) {
		cr::logger::fail("Failed to compile GL vertex shader.");
		glDeleteShader(vertex);
		return false;
	}

	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragSrc, nullptr);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &status);
	if (!status) {
		cr::logger::fail("Failed to compile GL fragment shader.");
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		return false;
	}

	m_program = glCreateProgram();
	glAttachShader(m_program, vertex);
	glAttachShader(m_program, fragment);
	glLinkProgram(m_program);
	glDetachShader(m_program, vertex);
	glDetachShader(m_program, fragment);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glGetProgramiv(m_program, GL_LINK_STATUS, &status);
	if (!status) {
		cr::logger::fail("Failed to link GL program.");
		glDeleteProgram(m_program);
		return false;
	}

	for (int i = 0; i < m_UNIFORM_COUNT - 1; i++) {
		m_uniformLocations[i] = glGetUniformLocation(m_program, m_UNIFORM_NAMES[i]);
	}

	return true;
}

void cr::shader::cleanup() {
	if (m_program)
		glDeleteProgram(m_program);
}

void cr::shader::set_uniform(cr::shader::uniform uniform, const glm::mat4& mat) {
	GLint loc = m_uniformLocations[static_cast<int>(uniform)];
	if (loc == -1) {
		cr::logger::warn("Failed to set GL shader uniform.");
		return;
	}
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

void cr::shader::use() {
	glUseProgram(m_program);
}
