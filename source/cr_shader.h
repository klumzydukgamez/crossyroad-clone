/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#if !defined CR_SHADER_H
#define CR_SHADER_H

#include "cr_third_party.h"

namespace cr {

class shader {
public:
	bool init(const char* vertexSource, const char* fragmentSource);
	void cleanup();

private:
	GLuint m_program = 0;
};

} /* namespace cr */

#endif /* CR_SHADER_H */
