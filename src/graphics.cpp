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

	glm::vec4 per_divide(glm::vec4& input)
	{
		// also known as normalize
		glm::vec4 output{ 0.0 };
		output[0] = ( input[0]) / input[3];
		output[1] = ( input[1]) / input[3];
		output[2] = ( input[2]) / input[3];
		output[3] = ( input[3]) / input[3];
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

	std::shared_ptr<std::vector<std::shared_ptr<Vertex>>> conv_cart(std::shared_ptr<std::vector<std::shared_ptr<Vertex>>> vertBuf)
	{
		// INPUT: Vertexbuffer
		// OUTPUT: Pixalbuffer
		using  cmplx_ptr = std::shared_ptr<std::vector<std::shared_ptr<Vertex>>>;

		cmplx_ptr pixal_buffer = std::make_shared<std::vector<std::shared_ptr<Vertex>>>();

		for each (auto c in *vertBuf)
		{
			pixal_buffer->push_back(std::make_shared<Vertex>(graphics::per_divide(c->coord())));
		}
		return pixal_buffer;
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
			glm::vec4 new_cord = M * v->coord();
			v->coord( M * v->coord());
		}
	}

	void drawtriangles(std::shared_ptr<std::vector<std::shared_ptr<Triangle>>> buff, std::shared_ptr<Image> Image, std::shared_ptr<ZBuffer> z_buff)
	{
		int count{ 0 };
		for each (auto tri in *buff)
		{
			//get random color
			glm::vec3 color = glm::vec3(RANDOM_COLORS[count % 10][0], RANDOM_COLORS[count % 10][1], RANDOM_COLORS[count % 10][2]);
			tri->DrawTri2(Image, color, z_buff);
			count++;

		}
	}

	//void scaleandtranslate(std::shared_ptr<std::vector<std::shared_ptr<Vertex>>> vertBuf, std::shared_ptr<Image> Image) {
	//	// Normalize ....get minimum X and Y vertexes and subtract so we start at [0,0]
	//	// this way we use full range or screen

	//	std::pair output = std::minmax_element(vertBuf->begin(), vertBuf->end(), [](const std::shared_ptr<Vertex> a, const std::shared_ptr<Vertex> b) { return a->m_position[0] < b->m_position[0];});
	//	double min_x = (*output.first)->x();
	//	double max_x = (*output.second)->x();
	//	double x_width = max_x - min_x;
	//	output = std::minmax_element(vertBuf->begin(), vertBuf->end(), [](const std::shared_ptr<Vertex> a, const std::shared_ptr<Vertex> b) { return a->m_position[1] < b->m_position[1];});
	//	double min_y = (*output.first)->y();
	//	double max_y = (*output.second)->y();
	//	double y_height = max_y - min_y;


	//	// subtracting min x and min yso we start at [0,0]
	//	for each (auto v in *vertBuf)
	//	{
	//		v->m_position = v->m_position - glm::vec4(min_x, min_y, 0, 0);
	//	}

	//	double  ratio = std::min(((double)Image->getWidth() / x_width), ((double)Image->getHeight() / y_height));

	//	for each (auto v in *vertBuf)
	//	{
	//		v->m_position[0] = v->m_position[0] * ratio;
	//		v->m_position[1] = v->m_position[1] * ratio;
	//		v->m_position[2] = v->m_position[2] * ratio;
	//	}

	//	output = std::minmax_element(vertBuf->begin(), vertBuf->end(), [](const std::shared_ptr<Vertex> a, const std::shared_ptr<Vertex> b) { return a->m_position[0] < b->m_position[0]; });
	//	min_x = (*output.first)->x();
	//	max_x = (*output.second)->x();
	//	x_width = max_x - min_x;
	//	output = std::minmax_element(vertBuf->begin(), vertBuf->end(), [](const std::shared_ptr<Vertex> a, const std::shared_ptr<Vertex> b) { return a->m_position[1] < b->m_position[1]; });
	//	min_y = (*output.first)->y();
	//	max_y = (*output.second)->y();
	//	y_height = max_y - min_y;

	//	double translationY = (((double) Image->getHeight() - y_height) / 2.0);
	//	double translationX = (((double)Image ->getWidth() - x_width)/ 2.0);

	//	for each (auto v in *vertBuf)
	//	{
	//		v->m_position[0] = v->m_position[0] + translationX;
	//		v->m_position[1] = v->m_position[1] + translationY;
	//	}
	//}
}
