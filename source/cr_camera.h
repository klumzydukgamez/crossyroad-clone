/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#if !defined CR_CAMERA_H
#define CR_CAMERA_H

#include "cr_third_party.h"

namespace cr {

class camera {
public:
	void simulate(float dt);

private:
	static constexpr glm::vec3 m_FRICTION = {0.1f, 0.1f, 0.1f};
	static constexpr glm::vec3 m_ROTATIONAL_FRICTION = {0.1f, 0.1f, 0.1f};

	glm::vec3 m_position = {0.0f, 0.0f, 0.0f};
	glm::vec3 m_prevPosition = {0.0f, 0.0f, 0.0f};

	glm::quat m_rotation = {1.0f, 0.0f, 0.0f, 0.0f};
	glm::quat m_prevRotation = {1.0f, 0.0f, 0.0f, 0.0f};

	glm::vec3 m_velocity = {0.0f, 0.0f, 0.0f};
	glm::vec3 m_rotationVelocity = {0.0f, 0.0f, 0.0f};

	glm::mat4 m_view = {};
	glm::mat4 m_projection = {};
	glm::mat4 m_projectionView = {};
};

} /* namespace cr */

#endif /* CR_CAMERA_H */
