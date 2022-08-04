#include "Triangle.h"

	float Triangle::f_line_ac(float x, float y)
	{
		//counter clockwise to match book
		// fac(x, y) = (ya - yc)x + (xc - xa)y + xayc - xcya = 0.
		glm::vec4 a = m_list_vertex[0].coord();
		glm::vec4 c = m_list_vertex[2].coord();
		return ((a[1] - c[1]) * x + (c[0] - a[0]) * y + (a[0] * c[1]) - (c[0] * a[1]));

	}

	float Triangle::f_line_ab(float x, float y)
	{
		//counter clockwise to match book
		// fab(x, y) = (y_a - y_b)x + (x_b - x_a)y + x_ay_b - x_by_a = 0.
		glm::vec4 a = m_list_vertex[0].coord();
		glm::vec4 b = m_list_vertex[1].coord();
		return ((a[1] - b[1]) * x + (b[0] - a[0]) * y + (a[0] * b[1]) - (b[0] * a[1]));
	}

	bool Triangle::comp_x(const glm::vec3& a, const glm::vec3& b)
	{
		return (a.x < b.x);
	}

	bool Triangle::comp_y(const glm::vec3& a, const glm::vec3& b)
	{
		return (a.y < b.y);
	}

	float Triangle::RoundBaryCoord(float in)
	{

		// doesnt work here for historical reasons
		float epsilon = 0.03;



		if ((in < (0 - epsilon)) && (in < 0)) {
			return 0;
		}
		else{
			//round to second decimal place
			return (std::round(in * 100)) / 100;
		}

	}

	Triangle::Triangle(Vertex A, Vertex B, Vertex C)
	{
		m_list_vertex.push_back(A);
		m_list_vertex.push_back(B);
		m_list_vertex.push_back(C);
	}

	void Triangle::draw(std::shared_ptr<Image> pic)
	{
		// perspective divide
		std::vector<glm::vec3> m_xy_coord;
		for each (auto c in m_list_vertex)
		{
			m_xy_coord.push_back(graphics::per_divide(c.coord()));
		}
		// Draw a rectangle
		for (int y = 0; y < pic->getHeight(); ++y) {
			for (int x = 0; x < pic->getWidth(); ++x) {
				for (int i = 0; i < m_xy_coord.size(); ++i) {
					if (x == m_xy_coord[i].x && y == m_xy_coord[i].y)
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

	void Triangle::draw_color(std::shared_ptr<Image> pic)
	{
		// Vertex Colors
		glm::vec3 colora = m_list_vertex[0].color();
		glm::vec3 colorb = m_list_vertex[1].color();
		glm::vec3 colorc = m_list_vertex[2].color();
		// RGB color red
		unsigned char r = 255;
		unsigned char g = 0;
		unsigned char b = 0;
		// Draw a rectangle color if its within the bary coords of 1 which means its inside the triangle
		glm::vec3 point_bary;
		for (int y = 0; y < pic->getHeight(); ++y) {
			for (int x = 0; x < pic->getWidth(); ++x) {
				point_bary = bary_coord(glm::vec3(x, y, 0));
				if (point_bary.x <= 1 && point_bary.x > 0 && point_bary.y <= 1 && point_bary.y > 0
					&& point_bary.z <= 1 && point_bary.z > 0)
				{
					glm::vec3 color_final = (point_bary.x) * colora + (point_bary.y) * colorb + (point_bary.z) * colorc;
					pic->setPixel(x, y, color_final[0], color_final[1], color_final[2]);
				}
			}
		}
	}

	void Triangle::draw_box(std::shared_ptr<Image> pic, glm::vec3 color)
	{

		// perspective divide

		for each (auto c in m_list_vertex)
		{
			m_xy_coord.push_back(graphics::per_divide(c.coord()));
		}
		std::vector<glm::vec3>::iterator output;
		output = std::max_element(m_xy_coord.begin(), m_xy_coord.end(), [](const glm::vec3 a, const glm::vec3 b) { return a.x < b.x; });
		float max_x = output->x;

		output = std::max_element(m_xy_coord.begin(), m_xy_coord.end(), [](const glm::vec3 a, const glm::vec3 b) { return a.y < b.y; });
		float max_y = output->y;

		output = std::min_element(m_xy_coord.begin(), m_xy_coord.end(), [](const glm::vec3 a, const glm::vec3 b) { return a.x < b.x; });
		float min_x = output->x;

		output = std::min_element(m_xy_coord.begin(), m_xy_coord.end(), [](const glm::vec3 a, const glm::vec3 b) { return a.y < b.y; });
		float min_y = output->y;

		// draw bound box
		// Draw a rectangle
		for (int y = min_y; y < max_y; ++y) {
			for (int x = min_x; x < max_x; ++x) {
				// default color background

				pic->setPixel(x, y, color[0] * 255, color[1] * 255, color[2] * 255);
			}
		}
	}

	glm::vec3 Triangle::bary_coord(glm::vec3 point)
		// returns barycentric cordinates
	{	// barycentric coordinates -> Fund Of Comp Graphics pg. 45
		//counter clockwise to match book
		// vertex[0] = a
		// vertex[1] = b
		// vertex[2] = c

		// determine beta coord
		glm::vec3 b = m_list_vertex[1].coord();
		float beta = (f_line_ac(point.x, point.y) / f_line_ac(b.x, b.y));
		// determine theta coord
		glm::vec3 c = m_list_vertex[2].coord();
		float theta = (f_line_ab(point.x, point.y) / f_line_ab(c.x, c.y));
		// determine alpha coord
		float alpha = 1 - beta - theta;
		return glm::vec3(alpha, beta, theta);
	}

	bool Triangle::bary_coord_point_inside(glm::vec3 point)
		// returns barycentric cordinates
	{	// barycentric coordinates -> Fund Of Comp Graphics pg. 45
		//counter clockwise to match book
		// vertex[0] = a
		// vertex[1] = b
		// vertex[2] = c

		// determine beta coord
		glm::vec3 b = m_xy_coord[1];
		float beta = (f_line_ac(point.x, point.y) / f_line_ac(b.x, b.y));
		// determine theta coord
		glm::vec3 c = m_xy_coord[2];
		float theta = (f_line_ab(point.x, point.y) / f_line_ab(c.x, c.y));
		// determine alpha coord
		float alpha = 1 - beta - theta;


		if (beta > 1 || beta < 0)
			return false;
		if (alpha > 1 || alpha < 0)
			return false;
		if (theta > 1 || theta < 0)
			return false;

		return true;
	}
	bool Triangle::bary_coord_point_inside2(glm::vec3 point)
		// returns barycentric cordinates
	{	// barycentric coordinates -> Fund Of Comp Graphics pg. 45
		//counter clockwise to match book
		// vertex[0] = a
		// vertex[1] = b
		// vertex[2] = c

		// determine beta coord
		glm::vec4 b = m_list_vertex[1].coord();
		float beta = (f_line_ac(point.x, point.y) / f_line_ac(b.x, b.y));
		// round to 2 decimal place
		//beta = (std::round(beta * 100))/ 100;
		// determine theta coord
		glm::vec4 c = m_list_vertex[2].coord();
		float theta = (f_line_ab(point.x, point.y) / f_line_ab(c.x, c.y));
		// round to 2 decimal place
		//theta = (std::round(theta * 100)) / 100;
		// determine alpha coord
		float alpha = 1 - beta - theta;


		if (beta > 1 || beta < 0)
			return false;
		if (alpha > 1 || alpha < 0)
			return false;
		if (theta > 1 || theta < 0)
			return false;

		return true;
	}

	void Triangle::draw_tri(std::shared_ptr<Image> pic, glm::vec3 color)
	{

		// perspective divide
		for each (auto c in m_list_vertex)
		{

			m_xy_coord.push_back(graphics::per_divide(c.coord()));
		}
		std::vector<glm::vec3>::iterator output;
		output = std::max_element(m_xy_coord.begin(), m_xy_coord.end(), [](const glm::vec3 a, const glm::vec3 b) { return a.x < b.x; });
		float max_x = output->x;

		output = std::max_element(m_xy_coord.begin(), m_xy_coord.end(), [](const glm::vec3 a, const glm::vec3 b) { return a.y < b.y; });
		float max_y = output->y;

		output = std::min_element(m_xy_coord.begin(), m_xy_coord.end(), [](const glm::vec3 a, const glm::vec3 b) { return a.x < b.x; });
		float min_x = output->x;

		output = std::min_element(m_xy_coord.begin(), m_xy_coord.end(), [](const glm::vec3 a, const glm::vec3 b) { return a.y < b.y; });
		float min_y = output->y;



		//draw triangle
		for (int y = min_y; y <= max_y; ++y) {
			for (int x = min_x; x <= max_x; ++x) {
				// default color background
				if (bary_coord_point_inside(glm::vec3(x,y,0)))
				{
				  pic->setPixel(x, y, color[0] * 255, color[1] * 255, color[2] * 255);
				}

			}
		}
	}
	void Triangle::draw_tri_2(std::shared_ptr<Image> pic, glm::vec3 color)
	{

		// vertexes have allready been perspective divided?
		

		std::vector<Vertex>::iterator output;
		output = std::max_element(m_list_vertex.begin(), m_list_vertex.end(), [](const Vertex a, const Vertex b) { return a.m_x < b.m_x; });
		float max_x = output->m_x;

		output = std::max_element(m_list_vertex.begin(), m_list_vertex.end(), [](const Vertex a, const Vertex b) { return a.m_y < b.m_y; });
		float max_y = output->m_y;

		output = std::min_element(m_list_vertex.begin(), m_list_vertex.end(), [](const Vertex a, const Vertex b) { return a.m_x < b.m_x; });
		float min_x = output->m_x;

		output = std::min_element(m_list_vertex.begin(), m_list_vertex.end(), [](const Vertex a, const Vertex b) { return a.m_y < b.m_y; });
		float min_y = output->m_y;
		

		//draw triangle
		for (int y = min_y; y <= max_y; ++y) {
			for (int x = min_x; x <= max_x; ++x) {
				// default color background
				if (bary_coord_point_inside2(glm::vec3(x, y, 0)))
				{
					pic->setPixel(x, y, color[0] * 255, color[1] * 255, color[2] * 255);
				}

			}
		}
	}