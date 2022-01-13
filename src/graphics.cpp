#include "graphics.h"

namespace graphics
{
	namespace  //private namespace functions and variables
	{
		bool comp_x(const glm::vec4& a, const glm::vec4& b)
		{
			return (a.x < b.x);
		}
		bool comp_y(const glm::vec4& a, const glm::vec4& b)
		{
			return (a.y < b.y);
		}
	}
	// constants
	// Functions
	void draw_line(glm::vec4 point_A, glm::vec4 point_B, std::shared_ptr<Image> Image, unsigned char r, unsigned char g, unsigned char b)
	{
		// drawing right to left
		float slope{ 0 };
		if (std::min(point_A, point_B, comp_x) == point_A)
		{
			slope = (point_B.y - point_A.y) / (point_B.x - point_A.x);
		}
		else
		{
			slope = (point_A.y - point_B.y) / (point_A.x - point_B.x);
		}

		float y_intercept = point_A.y - slope * point_A.x;

		// y = slope * x + y_intercept
		// check for straight vertical line with infinit slope
		if (slope != INFINITY)
		{
			for (size_t x = std::min(point_A, point_B, comp_x).x; x < std::max(point_A, point_B, comp_x).x; x++)
			{
				int y = slope * x + y_intercept;
				// set pixals to red
				Image->setPixel(x, y, r, g, b);

			}
		}
		else
		{
			for (size_t y = std::min(point_A, point_B, comp_y).y; y < std::max(point_A, point_B, comp_y).y; y++)
			{
				// draw straight vertical line
				// x is constant
				Image->setPixel(point_A.x, y, r, g, b);

			}
		}
	}

	// compute screen coordinates first
	// from scratchapixal.com
	void gluPerspective( const float& angleOfView, const float& imageAspectRatio, const float& n, const float& f,
						float& b, float& t, float& l, float& r)
	{
		float scale = tan(angleOfView * 0.5 * M_PI / 180) * n;
		r = imageAspectRatio * scale, l = -r;
		t = scale, b = -t;
	}

	// set the OpenGL perspective projection matrix
	// from scratchapixal.com
	glm::mat4 glFrustum(const float& b, const float& t, const float& l, const float& r,
						const float& n, const float& f)
	{
		glm::mat4 M{ 0.0 };

		// set OpenGL perspective projection matrix
		M[0][0] = 2 * n / (r - l);
		M[0][1] = 0;
		M[0][2] = 0;
		M[0][3] = 0;

		M[1][0] = 0;
		M[1][1] = 2 * n / (t - b);
		M[1][2] = 0;
		M[1][3] = 0;

		M[2][0] = (r + l) / (r - l);
		M[2][1] = (t + b) / (t - b);
		M[2][2] = -(f + n) / (f - n);
		M[2][3] = -1;

		M[3][0] = 0;
		M[3][1] = 0;
		M[3][2] = -2 * f * n / (f - n);
		M[3][3] = 0;
		return M;
	}

	glm::mat4 get_view(int width, int height) 
	{
		//	generate view matrix
		glm::mat4 view{ 0.0 };
		// columns indexed before rows
		view[0] = glm::vec4(width / 2, 0, 0, 0);
		view[1] = glm::vec4(0, height / 2, 0, 0);
		view[2] = glm::vec4(0, 0, 1, 0);
		view[3] = glm::vec4((width - 1) / 2, (height - 1) / 2, 0, 1);
		return view;
	}

}