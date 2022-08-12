#pragma once
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_
#include <glm/glm.hpp>
#include <algorithm>
#include <memory>
#include <cmath>
#include "Shape_base.h"
#include "Vertex.h"
#include "Image.h"
#include "graphics.h"
#include "ZBuffer.h"
#include <iostream>
class Triangle : public Shape_base
{
private:
	float FLine20(float x, float y);

	float FLine12(float x, float y);

	float FLine01(float x, float y);
	
	bool comp_x(const glm::vec3& a, const glm::vec3& b);

	bool comp_y(const glm::vec3& a, const glm::vec3& b);

	float RoundBaryCoord(float in);
	std::vector<Vertex> m_list_vertex;
	std::vector<glm::vec3> m_xy_coord;
public:
	// old implementation as a vector of vertexes


	Triangle(const std::string name)
		:Shape_base{name}
	{}

	Triangle(Vertex A, Vertex B, Vertex C);
	Triangle() = default;
	~Triangle() = default;

	const int example() const override { return 1; }
	glm::vec3 bary_coord(glm::vec3 point);
	void DrawTri2(std::shared_ptr<Image> pic, glm::vec3 color, std::shared_ptr<ZBuffer> z_buff);
	bool Triangle::bary_coord_point_inside(glm::vec3 point);
	bool BaryCoordPointInside2(glm::vec3 point);
};
#endif

