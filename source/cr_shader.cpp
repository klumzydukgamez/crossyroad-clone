/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_shader.h"

bool cr::shader::init(const char* vertexSource, const char* fragmentSource) {
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	if (!vertex) {
		SDL_Log("Failed to create GL vertex shader.");
		return false;
	}
	glShaderSource(vertex, 1, &vertexSource, nullptr);
	glCompileShader(vertex);
	int vertexResult = 0;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &vertexResult);
	if (!vertexResult) {
		SDL_Log("Failed to compile GL vertex shader.");
		GLsizei length = 0;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
		if (length > 0) {
			auto* log = static_cast<GLchar*>(SDL_malloc(sizeof(GLchar) * length));
			glGetShaderInfoLog(vertex, length, nullptr, log);
			SDL_Log("%s", log);
			SDL_free(log);
		}
		glDeleteShader(vertex);
		return false;
	}

	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	if (!fragment) {
		SDL_Log("Failed to create GL fragment shader.");
		glDeleteShader(vertex);
		return false;
	}
	glShaderSource(fragment, 1, &fragmentSource, nullptr);
	glCompileShader(fragment);
	int fragmentResult = 0;
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &fragmentResult);
	if (!fragmentResult) {
		SDL_Log("Failed to compile GL fragment shader.");
		GLsizei length = 0;
		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
		if (length > 0) {
			auto* log = static_cast<GLchar*>(SDL_malloc(sizeof(GLchar) * length));
			glGetShaderInfoLog(fragment, length, nullptr, log);
			SDL_Log("%s", log);
			SDL_free(log);
		}
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		return false;
	}

	GLuint program = glCreateProgram();
	if (!program) {
		SDL_Log("Failed to create GL program.");
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		return false;
	}
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	glDetachShader(program, vertex);
	glDetachShader(program, fragment);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	int programResult = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &programResult);
	if (!programResult) {
		SDL_Log("Failed to link GL program.");
		GLsizei length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		if (length > 0) {
			auto* log = static_cast<GLchar*>(SDL_malloc(sizeof(GLchar) * length));
			glGetProgramInfoLog(program, length, nullptr, log);
			SDL_Log("%s", log);
			SDL_free(log);
		}
		glDeleteProgram(program);
		return false;
	}
	m_program = program;

	return true;
}

void cr::shader::cleanup() {
	if (m_program)
		glDeleteProgram(m_program);
}
