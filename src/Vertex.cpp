#include "Vertex.h"

Vertex::Vertex(float x, float y, float z)
{
	m_position = glm::vec4(x, y, z, 0);
	m_x = x;
	m_y = y;
	m_z = z;
	m_w = 0;
	m_color = glm::ivec4(0.0f);
}

Vertex::Vertex(float x, float y, float z, int r, int g, int b)
{
	m_position = glm::vec4(x, y, z, 0);
	m_x = x;
	m_y = y;
	m_z = z;
	m_w = 0;
	m_color = glm::ivec4(r, g, b, 0);
}

Vertex::Vertex(const glm::vec4& coord)
{
	m_position = coord;
	m_x = m_position[0];
	m_y = m_position[1];
	m_z = m_position[2];
	m_w = m_position[3];
	m_color = glm::ivec4(0.0f);
}

Vertex::Vertex(const glm::vec4& coord, const glm::vec4& color)
{
	m_position = coord;
	m_x = m_position[0];
	m_y = m_position[1];
	m_z = m_position[2];
	m_w = m_position[3];
	m_color = color;
}

void Vertex::coord(glm::vec4 coord)
{
	m_position = coord;
	m_x = m_position[0];
	m_y = m_position[1];
	m_z = m_position[2];
	m_w = m_position[3];
}

void Vertex::color(int red, int green, int blue) {
	m_color = glm::vec4(red, green, blue, 0);
}