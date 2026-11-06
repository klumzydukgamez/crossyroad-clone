/* Copyright (c) 2026 Klumzy Duk Gamez.
 * See LICENSE.md for full terms. */

#version 460 core

out vec3 vColor;

uniform mat4 uProjectionView;
uniform mat4 uModel;

void main(void) {
	const vec3 positions[36] = vec3[](
        // Back face
        vec3(-0.5, -0.5, -0.5), vec3( 0.5,  0.5, -0.5), vec3( 0.5, -0.5, -0.5),
        vec3( 0.5,  0.5, -0.5), vec3(-0.5, -0.5, -0.5), vec3(-0.5,  0.5, -0.5),
        // Front face
        vec3(-0.5, -0.5,  0.5), vec3( 0.5, -0.5,  0.5), vec3( 0.5,  0.5,  0.5),
        vec3( 0.5,  0.5,  0.5), vec3(-0.5,  0.5,  0.5), vec3(-0.5, -0.5,  0.5),
        // Left face
        vec3(-0.5,  0.5,  0.5), vec3(-0.5,  0.5, -0.5), vec3(-0.5, -0.5, -0.5),
        vec3(-0.5, -0.5, -0.5), vec3(-0.5, -0.5,  0.5), vec3(-0.5,  0.5,  0.5),
        // Right face
        vec3( 0.5,  0.5,  0.5), vec3( 0.5, -0.5, -0.5), vec3( 0.5,  0.5, -0.5),
        vec3( 0.5, -0.5, -0.5), vec3( 0.5,  0.5,  0.5), vec3( 0.5, -0.5,  0.5),
        // Bottom face
        vec3(-0.5, -0.5, -0.5), vec3( 0.5, -0.5, -0.5), vec3( 0.5, -0.5,  0.5),
        vec3( 0.5, -0.5,  0.5), vec3(-0.5, -0.5,  0.5), vec3(-0.5, -0.5, -0.5),
        // Top face
        vec3(-0.5,  0.5, -0.5), vec3( 0.5,  0.5,  0.5), vec3( 0.5,  0.5, -0.5),
        vec3( 0.5,  0.5,  0.5), vec3(-0.5,  0.5, -0.5), vec3(-0.5,  0.5,  0.5)
    );
    const vec3 colors[6] = vec3[](
        vec3(1.0, 0.0, 0.0), // Red (Back)
        vec3(0.0, 1.0, 0.0), // Green (Front)
        vec3(0.0, 0.0, 1.0), // Blue (Left)
        vec3(1.0, 1.0, 0.0), // Yellow (Right)
        vec3(1.0, 0.0, 1.0), // Magenta (Bottom)
        vec3(0.0, 1.0, 1.0)  // Cyan (Top)
    );

	gl_Position = uProjectionView * uModel * vec4(positions[gl_VertexID], 1.0);
	vColor = colors[gl_VertexID / 6];
}
