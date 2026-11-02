/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_crash_reporter.h"
#include "cr_third_party.h"

#if defined SDL_PLATFORM_WINDOWS
#include <windows.h>

static LONG WINAPI crash_handler_exception_filter(EXCEPTION_POINTERS* exceptionPointers) {
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "crossyroad-clone", "Crash caught.", nullptr);
	return EXCEPTION_EXECUTE_HANDLER;
}

void cr::crash_reporter::init() {
	SetUnhandledExceptionFilter(crash_handler_exception_filter);
}

#endif
