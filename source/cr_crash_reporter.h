/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#if !defined CR_CRASH_REPORTER_H
#define CR_CRASH_REPORTER_H

namespace cr {

class crash_reporter {
public:
	/* only works on Windows */
	static void init();
};

} /* namespace cr */

#endif /* CR_CRASH_REPORTER_H */
