/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#include "cr_camera.h"

void cr::camera::update(float dt) {
	m_prevPosition = m_position;
	m_prevRotation = m_rotation;

	m_position += m_velocity * dt;
	m_velocity -= m_FRICTION * dt;
}

void cr::camera::calculate_view_projection(float dt) {
}
