/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_logger.h"

void cr::logger::inform(const char* msg) {
	m_get_time();
	SDL_Log(
		"[%02d:%02d:%02d] \033[32m[INFO] %s\033[0m",
		m_dateTime.hour, m_dateTime.minute, m_dateTime.second,
		msg
	);
}

void cr::logger::warn(const char* msg) {
	m_get_time();
	SDL_Log(
		"[%02d:%02d:%02d] \033[33m[WARNING] %s\033[0m",
		m_dateTime.hour, m_dateTime.minute, m_dateTime.second,
		msg
	);
}

void cr::logger::fail(const char* msg) {
	m_get_time();
	SDL_Log(
		"[%02d:%02d:%02d] \033[31m[FAILURE] %s\033[0m",
		m_dateTime.hour, m_dateTime.minute, m_dateTime.second,
		msg
	);
}

void cr::logger::trace_sdl() {
	m_get_time();
	SDL_Log(
		"[%02d:%02d:%02d] \033[35m[TRACE][SDL] %s\033[0m",
		m_dateTime.hour, m_dateTime.minute, m_dateTime.second,
		SDL_GetError()
	);
}

void cr::logger::m_get_time() {
	SDL_Time time;
	SDL_GetCurrentTime(&time);
	SDL_TimeToDateTime(time, &m_dateTime, true);
}
