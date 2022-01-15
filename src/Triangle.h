#pragma once
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_
#include <glm/glm.hpp>
#include <algorithm>
#include <memory>
#include "Shape_base.h"
#include "Vertex.h"
#include "Image.h"
#include "graphics.h"
class Triangle : public Shape_base
{
private:
	float f_line_ac(float x, float y);

	float f_line_ab(float x, float y);
	
	bool comp_x(const glm::vec3& a, const glm::vec3& b);

	bool comp_y(const glm::vec3& a, const glm::vec3& b);

	std::vector<Vertex> m_list_vertex;
public:
	// old implementation as a vector of vertexes


	Triangle(const std::string name)
		:Shape_base{name}
	{}

	Triangle(Vertex A, Vertex B, Vertex C);
	Triangle() = default;
	~Triangle() = default;

	const int example() const override { return 1; }

	void draw(std::shared_ptr<Image> pic);

	void draw_color(std::shared_ptr<Image> pic);

	void draw_box(std::shared_ptr<Image> pic, glm::vec3 color);

	glm::vec4 bary_coord(glm::vec4 point);

};
#endif

