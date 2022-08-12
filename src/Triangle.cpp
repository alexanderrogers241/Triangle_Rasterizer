#include "Triangle.h"

	float Triangle::FLine20(float x, float y)
	{
		//counter-clockwise to match book
		// fac(x, y) = (ya - yc)x + (xc - xa)y + xayc - xcya = 0.
		glm::vec4 c = m_list_vertex[2].coord();
		glm::vec4 a = m_list_vertex[0].coord();
		return ((c[1] - a[1]) * x + (a[0] - c[0]) * y + (c[0] * a[1]) - (a[0] * c[1]));
	}

	float Triangle::FLine12(float x, float y)
	{
		//counter-clockwise to match book
		glm::vec4 b = m_list_vertex[1].coord();
		glm::vec4 c = m_list_vertex[2].coord();
		return ((b[1] - c[1]) * x + (c[0] - b[0]) * y + (b[0] * c[1]) - (c[0] * b[1]));
	}
	float Triangle::FLine01(float x, float y)
	{
		//counter-clockwise to match book
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

	glm::vec3 Triangle::bary_coord(glm::vec3 point)
		// returns barycentric cordinates
	{	// barycentric coordinates -> Fund Of Comp Graphics pg. 45
		//counter clockwise to match book
		// vertex[0] = a
		// vertex[1] = b
		// vertex[2] = c

		// determine beta coord
		glm::vec3 b = m_list_vertex[1].coord();
		float beta = (FLine20(point.x, point.y) / FLine20(b.x, b.y));
		// determine theta coord
		glm::vec3 c = m_list_vertex[2].coord();
		float theta = (FLine01(point.x, point.y) / FLine01(c.x, c.y));
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
		float beta = (FLine20(point.x, point.y) / FLine20(b.x, b.y));
		// determine theta coord
		glm::vec3 c = m_xy_coord[2];
		float theta = (FLine01(point.x, point.y) / FLine01(c.x, c.y));
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
	bool Triangle::BaryCoordPointInside2(glm::vec3 point)
		// returns barycentric cordinates
	{	// barycentric coordinates -> Fund Of Comp Graphics pg. 45
		//counter clockwise to match book
		// vertex[0] = a
		// vertex[1] = b
		// vertex[2] = c

		// determine beta coord
		glm::vec4 b = m_list_vertex[1].coord();
		float beta = (FLine20(point.x, point.y) / FLine20(b.x, b.y));
		// round to 2 decimal place
		//beta = (std::round(beta * 100))/ 100;
		// determine theta coord
		glm::vec4 c = m_list_vertex[2].coord();
		float theta = (FLine01(point.x, point.y) / FLine01(c.x, c.y));
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

	void Triangle::DrawTri2(std::shared_ptr<Image> pic, glm::vec3 color, std::shared_ptr<ZBuffer> z_buff)
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

				glm::vec3 point(x, y, 0);
				// barycentric coordinates -> Fund Of Comp Graphics pg. 45
				//counter-clockwise to match book
				// vertex[0] = a
				// vertex[1] = b		
				// vertex[2] = c
				// books redefines variables in algorithms
				// Beta = f_ac(x,y)/f_ac(x_b,y_b) FOCG pg. 47 -> Beta = f_20(x,y)/f_20(x_b,y_b) FOCG pg. 169
				// f_20 means "line from vertex 2 to vertex 0" 
				float f_alpha = FLine12(m_list_vertex[0].m_x, m_list_vertex[0].m_y);
				float f_beta = FLine20(m_list_vertex[1].m_x, m_list_vertex[1].m_y);
				float f_theta = FLine01(m_list_vertex[2].m_x, m_list_vertex[2].m_y);
				/*assert(f_alpha != 0, "barycentric error: divide by zero");
				assert(f_beta != 0, "barycentric error: divide by zero");
				assert(f_theta != 0, "barycentric error: divide by zero");*/
				// determine beta coord
				float beta = (FLine20(point.x, point.y) / f_beta);
				// determine theta coord
				float theta = (FLine01(point.x, point.y) / f_theta);
				// determine alpha coord
				float alpha = 1 - beta - theta;
				//debugging 
				int x_pixal_debug = 0;
				int y_pixal_debug = 0;

				if (alpha >= 0 && beta >= 0 && theta >=0) {
					// pg. 169 FOCG
					if ((alpha > 0 || (f_alpha*FLine12(-1,-1))>0) && (beta > 0 || (f_beta * FLine20(-1, -1)) > 0) && (theta > 0 || (f_theta * FLine01(-1, -1)) > 0)) {
						// implemention of color interpolation between barycentric coordinates
						// glm::vec4 color_not_impl = (alpha * m_list_vertex[0].m_color) + (beta * m_list_vertex[1].m_color) + (alpha * m_list_vertex[2].m_color);
						float z_float = (alpha * m_list_vertex[0].m_z) + (beta * m_list_vertex[1].m_z) + (alpha * m_list_vertex[2].m_z);
						
						if (x == 912 && y == 564)
						{
							std::cout << "\ndebugstep\n";
						}

						// Check Z-bufer FOCG pg. 175
						if (z_buff->Check(x, y, z_float)) 
						{
							
							pic->setPixel(x, y,color.x * 255, color.y * 255, color.z * 255);
							// debugging by marking next pixal
							if (x == 912 && y == 564)
							{
								std::cout << "\n" << (color.x * 255) << "\t"<< (color.y * 255) << "\t" << (color.z * 255);
							}
							
						}
					}
				}
			}
		}
	}