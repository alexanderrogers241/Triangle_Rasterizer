#pragma once
#ifndef _Vertex_H_
#define _Vertex_H_
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Vertex
{
private:
	glm::vec4 m_color;
	glm::vec4 m_position;
public:
	Vertex() {
		m_color = glm::vec4(0);
		m_position = glm::vec4(0.0f);
	}
	Vertex(float x, float y, float z = 0)
	{
		m_position = glm::vec4(x, y, z, 0);
		m_color = glm::ivec4(0.0f);
	}

	Vertex(float x, float y, float z , int r, int g, int b)
	{
		m_position = glm::vec4(x, y, z, 0);
		m_color = glm::ivec4(r,g,b, 0);
	}

	Vertex(const glm::vec4& coord)
	{
		m_position = coord;
		m_color = glm::ivec4(0.0f);
	}

	Vertex(const glm::vec4& coord, const glm::vec4& color)
	{
		m_position = coord;
		m_color = color;
	}

	~Vertex() = default;
	float x() { return m_position[0]; }
	void x(float x) { m_position[0] = x; }
	float y() { return m_position[1]; }
	void y(float y) { m_position[1] = y; }
	float z() { return m_position[2]; }
	void z(float z) { m_position[2] = z; }

	glm::vec4 coord() { return m_position; }
	void coord(glm::vec4 coord)
	{
		m_position = coord;
	}

	glm::ivec3 color() { return m_color; }

	void color(int red, int green, int blue) {
		m_color = glm::vec4(red, green, blue, 0);
	}
};


#endif

