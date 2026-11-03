/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#if !defined CR_CAMERA_H
#define CR_CAMERA_H

#include "cr_third_party.h"

namespace cr {

class camera {
public:
	void update(float dst);
	void calculate_matrices(float dft);

	void set_target_position(const glm::vec3& position);

private:
	static constexpr float m_PITCH = glm::radians(-45.0f);
	static constexpr float m_YAW = glm::radians(45.0f);
	static constexpr float m_ACCELERATION = 2.0f;
	static constexpr float m_FRICTION = 0.5f;

	glm::vec3 m_position = {};
	glm::vec3 m_prevPosition = {};

	glm::vec3 m_velocity = {};
	glm::vec3 m_targetPosition = {};

	glm::mat4 m_view = {1.0f};
	glm::mat4 m_projection = {1.0f};
	glm::mat4 m_projectionView = {1.0f};
};

} /* namespace cr */

#endif /* CR_CAMERA_H */
