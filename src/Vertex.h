#pragma once
#ifndef _VERTEX_H_
#define _VERTEX_H_
#include <glm/glm.hpp>
class Vertex
{
public:
	glm::vec4 m_color;
	glm::vec4 m_position;

	Vertex() {
		m_color = glm::vec4(0);
		m_position = glm::vec4(0.0f);
	}

	Vertex(float x, float y, float z );

	Vertex(float x, float y, float z, int r, int g, int b);

	Vertex(const glm::vec4& coord);

	Vertex(const glm::vec4& coord, const glm::vec4& color);


	~Vertex() = default;

	float x() { return m_position[0]; }
	void x(float x) { m_position[0] = x; }
	float y() { return m_position[1]; }
	void y(float y) { m_position[1] = y; }
	float z() { return m_position[2]; }
	void z(float z) { m_position[2] = z; }
	glm::vec4 coord() { return m_position; }
	glm::ivec3 color() { return m_color; }

	void coord(glm::vec4 coord);

	void color(int red, int green, int blue);
};
#endif

