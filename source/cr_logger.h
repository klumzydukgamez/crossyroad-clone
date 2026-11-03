/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#if !defined CR_LOGGER_H
#define CR_LOGGER_H

#include "cr_third_party.h"

namespace cr {

class logger {
public:
	static void inform(const char* msg);
	static void warn(const char* msg);
	static void fail(const char* msg);
	static void trace(const char* msg);

	static void trace_sdl();

private:
	static constexpr int m_LOG_SIZE = 256;

	static void m_update_time();

	static inline SDL_DateTime m_dateTime = {};
	static inline char m_temp[m_LOG_SIZE] = {};
};

} /* namespace cr */

#endif /* CR_LOGGER_H */
