#include "graphics.h"

namespace graphics
{
	namespace  //private namespace functions and variables
	{
		bool comp_x(const glm::vec3& a, const glm::vec3& b)
		{
			return (a.x < b.x);
		}
		bool comp_y(const glm::vec3& a, const glm::vec3& b)
		{
			return (a.y < b.y);
		}
	}
	// Functions
	void draw_line(glm::vec3 point_A, glm::vec3 point_B, std::shared_ptr<Image> Image, unsigned char r, unsigned char g, unsigned char b)
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

	glm::vec3 per_divide(glm::vec4& input)
	{
		glm::vec3 output{ 0.0 };
		output[0] = input[0] / input[3];
		output[1] = input[1] / input[3];
		output[2] = input[2];
		return output;
	}

	//modified from https://github.com/Maxrod98/CSCE441-A1/
	std::shared_ptr<std::vector<std::shared_ptr<Vertex>>> conv_verts(std::vector<float>& buff)
	{  
		using  cmplx_ptr = std::shared_ptr<std::vector<std::shared_ptr<Vertex>>>;

		cmplx_ptr vert_list = std::make_shared<std::vector<std::shared_ptr<Vertex>>>();

		std::vector<float>::iterator it;

		for (std::vector<float>::iterator it = buff.begin(); it < buff.end(); it = it + 3)
		{

			// vertex[3] = 1 because it is a location
			vert_list->push_back(std::make_shared<Vertex>(glm::vec4(*it, *(it + 1), *(it + 2), 1)));
		}
		return vert_list;
	}

	std::shared_ptr<std::vector<std::shared_ptr<Triangle>>> conv_tri(std::shared_ptr<std::vector<std::shared_ptr<Vertex>>> vertBuf)
	{
		using  cmplx_ptr = std::shared_ptr<std::vector<std::shared_ptr<Triangle>>>;

		cmplx_ptr tri_list = std::make_shared<std::vector<std::shared_ptr<Triangle>>>();

		for (auto it = vertBuf->begin(); it < vertBuf->end(); it = it + 3)
		{
			tri_list->push_back(std::make_shared<Triangle>(*(*it), *(*(it + 1)), *(*(it + 2))));
		}
		return tri_list;
	}
	void transbuff(glm::mat4& M, std::shared_ptr<std::vector<std::shared_ptr<Vertex>>> vert_buff)
	{
		for each  (auto v in *vert_buff)
		{
			v->coord( M * v->coord());
		}
	}
	void drawtrianglesbox(std::shared_ptr<std::vector<std::shared_ptr<Triangle>>> buff, std::shared_ptr<Image> Image)
	{
		int count{ 0 };
		for each (auto tri in *buff)
		{
			 //get random color
			glm::vec3 color = glm::vec3(RANDOM_COLORS[count % 7][0], RANDOM_COLORS[count % 7][1], RANDOM_COLORS[count % 7][2]);
			tri->draw_box(Image, color);
			count++;
		}
	}
}