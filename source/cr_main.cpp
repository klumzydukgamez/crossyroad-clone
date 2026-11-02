/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_crash_reporter.h"

int main(int argc, char* argv[]) {
	cr::crash_reporter::init();

	int* ptr = nullptr;
	*ptr = 10;

	return 0;
}
