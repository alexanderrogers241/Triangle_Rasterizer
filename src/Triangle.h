#pragma once
#ifndef _Triangle_H_
#define _Triangle_H_
#include "Shape_base.h"
#include "Image.h"
class Triangle : public Shape_base
{
private:
	int m_num_verts;
	float f_line_ac(float x, float y)
	{
		//counter clockwise to match book
		// fac(x, y) = (ya - yc)x + (xc - xa)y + xayc - xcya = 0.
		glm::vec3 a = p_list_vertex[0].coord();
		glm::vec3 c = p_list_vertex[2].coord();
		return ((a[1] - c[1]) * x + (c[0] - a[0]) * y + (a[0] * c[1]) - (c[0] * a[1]));

	}
	float f_line_ab(float x, float y)
	{
		//counter clockwise to match book
		// fab(x, y) = (y_a - y_b)x + (x_b - x_a)y + x_ay_b - x_by_a = 0.
		glm::vec3 a = p_list_vertex[0].coord();
		glm::vec3 b = p_list_vertex[1].coord();
		return ((a[1] - b[1]) * x + (b[0] - a[0]) * y + (a[0] * b[1]) - (b[0] * a[1]));
	}
public:
	std::vector<Vertex> p_list_vertex;

	Triangle(const std::string name)
		:Shape_base{ name, 3 }
	{
		for (size_t i = 0; i < 3; i++)
		{
			p_list_vertex.push_back(Vertex(glm::vec4(0,0,0,0)));
		}
	}
	~Triangle() = default;

	const int example() const override { return 1; }

	void draw(std::shared_ptr<Image> pic)
	{
		// Draw a rectangle
		for (int y = 0; y < pic->getHeight(); ++y) {
			for (int x = 0; x < pic->getWidth(); ++x) {
				for (int i = 0; i < p_list_vertex.size(); ++i) {
					if (x == p_list_vertex[0].x() && y == p_list_vertex[0].y())
					{
						// if a vertex paint red
						unsigned char r2 = 255;
						unsigned char g2 = 0;
						unsigned char b2 = 0;
						pic->setPixel(x, y, r2, g2, b2);
					}
				}
			}
		}
	}
	void draw_color(std::shared_ptr<Image> pic)
	{
		// Vertex Colors
		glm::vec3 colora = p_list_vertex[0].color();
		glm::vec3 colorb = p_list_vertex[1].color();
		glm::vec3 colorc = p_list_vertex[2].color();
		// RGB color red
		unsigned char r = 255;
		unsigned char g = 0;
		unsigned char b = 0;
		// Draw a rectangle color if its within the bary coords of 1 which means its inside the triangle
		glm::vec3 point_bary;
		for (int y = 0; y < pic->getHeight(); ++y) {
			for (int x = 0; x < pic->getWidth(); ++x) {
				point_bary = bary_coord(glm::vec4(x, y, 0, 0));
				if (point_bary.x <= 1 && point_bary.x > 0 && point_bary.y <= 1 && point_bary.y > 0 
					&& point_bary.z <= 1 && point_bary.z > 0)
				{
					glm::vec3 color_final = (point_bary.x) * colora + (point_bary.y) * colorb + (point_bary.z) * colorc;
					pic->setPixel(x, y, color_final[0], color_final[1], color_final[2]);
				}
			}
		}
	}
	void draw_box(std::shared_ptr<Image> pic)
	{
		int max_x{ 0 };
		int max_y{ 0 };
		int min_x{ 512 };
		int min_y{ 512 };
		// find max vertex
		for (int i = 0; i < p_list_vertex.size(); ++i) {
			if (p_list_vertex[i].x() > max_x) {
				max_x = p_list_vertex[i].x();
			}

			if (p_list_vertex[i].y() > max_y) {
				max_y = p_list_vertex[i].y();
			}
		}
		// find min vertex
		for (int i = 0; i < p_list_vertex.size(); ++i) {
			if (p_list_vertex[i].x() < min_x) {
				min_x = p_list_vertex[i].x();
			}

			if (p_list_vertex[i].y() < min_y) {
				min_y = p_list_vertex[i].y();
			}
		}
		// draw bound box
		// Draw a rectangle
		for (int y = min_y + 1; y < max_y; ++y) {
			for (int x = min_x + 1; x < max_x -1; ++x) {
				// default color background
				unsigned char r = 0;
				unsigned char g = 0;
				unsigned char b = 255;
				unsigned char r2 = 0;
				unsigned char g2 = 255;
				unsigned char b2 = 0;
				if ( y % 2 == 0 && x % 2 == 0) {
					pic->setPixel(x, y, r2, g2, b2);
				}
				else {
					pic->setPixel(x, y, r, g, b);
				}

			}
		}
	}

	glm::vec4 bary_coord(glm::vec4 point)
	{
		//counter clockwise to match book
		// vertex[0] = a
		// vertex[1] = b
		// vertex[2] = c

		// determine beta coord
		glm::vec4 b = p_list_vertex[1].coord();
		float beta = (f_line_ac(point.x, point.y) / f_line_ac(b.x, b.y) );
		// determine theta coord
		glm::vec4 c = p_list_vertex[2].coord();
		float theta = (f_line_ab(point.x, point.y) / f_line_ab(c.x, c.y));
		// determine alpha coord
		float alpha = 1 - beta - theta;
		return glm::vec4(alpha, beta, theta, 0);
	}
};
#endif

