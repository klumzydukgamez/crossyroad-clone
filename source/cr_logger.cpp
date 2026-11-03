/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_logger.h"

void cr::logger::inform(const char* msg) {
	m_update_time();
	SDL_snprintf(
		m_temp, m_LOG_SIZE,
		"[%02d:%02d:%02d] [INFO] %s",
		m_dateTime.hour, m_dateTime.minute, m_dateTime.second,
		msg
	);
	SDL_Log("%s", m_temp);
}

void cr::logger::warn(const char* msg) {
	m_update_time();
	SDL_snprintf(
		m_temp, m_LOG_SIZE,
		"[%02d:%02d:%02d] [WARNING] %s",
		m_dateTime.hour, m_dateTime.minute, m_dateTime.second,
		msg
	);
	SDL_Log("%s", m_temp);
}

void cr::logger::fail(const char* msg) {
	m_update_time();
	SDL_snprintf(
		m_temp, m_LOG_SIZE,
		"[%02d:%02d:%02d] [FAILURE] %s",
		m_dateTime.hour, m_dateTime.minute, m_dateTime.second,
		msg
	);
	SDL_Log("%s", m_temp);
}

void cr::logger::trace_sdl() {
	m_update_time();
	SDL_snprintf(
		m_temp, m_LOG_SIZE,
		"[%02d:%02d:%02d] [TRACE][SDL] %s",
		m_dateTime.hour, m_dateTime.minute, m_dateTime.second,
		SDL_GetError()
	);
	SDL_Log("%s", m_temp);
}

void cr::logger::m_update_time() {
	SDL_Time time;
	SDL_GetCurrentTime(&time);
	SDL_TimeToDateTime(time, &m_dateTime, true);
}
