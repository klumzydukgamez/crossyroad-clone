/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#if !defined CR_SHADER_H
#define CR_SHADER_H

#include "cr_third_party.h"

namespace cr {

class shader {
public:
	enum class uniform : int {
		uProjectionView,
		uModel,
		count
	};

	bool init(const GLchar* vertSrc, const GLchar* fragSrc);
	void cleanup();

	void set_uniform(cr::shader::uniform uniform, const glm::mat4& mat);

	void use();

private:
	static constexpr int m_UNIFORM_COUNT = static_cast<int>(uniform::count);
	static constexpr char m_UNIFORM_NAMES[m_UNIFORM_COUNT][64] = {
		"uProjectionView",
		"uModel"
	};

	GLuint m_program = 0;
	GLint m_uniformLocations[m_UNIFORM_COUNT] = {};
};

} /* namespace cr */

#endif /* CR_SHADER_H */
