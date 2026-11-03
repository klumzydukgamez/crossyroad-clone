/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_camera.h"
#include "cr_window.h"
#include "cr_logger.h"

void cr::camera::update(float dst) {
	m_prevPosition = m_position;

	glm::vec3 displacement = m_targetPosition - m_position;
	if (glm::dot(displacement, displacement) <= 0.0001f) {
		m_position = m_targetPosition;
		m_velocity = {0.0f, 0.0f, 0.0f};
	} else {
		m_velocity = displacement * m_ACCELERATION;
		m_position += m_velocity * dst;
	}
}

void cr::camera::calculate_matrices(float dft) {
	m_projection = glm::ortho(
		0.0f, static_cast<float>(cr::window::WIDTH),
		static_cast<float>(cr::window::HEIGHT), 0.0f,
		0.001f, 10000.0f
	);
	glm::vec3 position = glm::mix(m_prevPosition, m_position, dft);
	glm::vec3 front;
	front.x = cos(m_PITCH) * sin(m_YAW);
	front.y = sin(m_PITCH);
	front.z = -cos(m_PITCH) * cos(m_YAW);
	m_view = glm::lookAt(position, position + front, {0.0f, 1.0f, 0.0f});
	m_projectionView = m_projection * m_view;
}

void cr::camera::set_target_position(const glm::vec3& position) {
	m_targetPosition = position;
}
