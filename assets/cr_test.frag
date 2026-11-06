/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#version 460 core

in vec3 vColor;

out vec4 oColor;

void main(void) {
	oColor = vec4(vColor, 1.0);
}
