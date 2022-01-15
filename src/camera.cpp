#include "camera.h"
#include "graphics.h"

glm::mat4 Camera::get_view(int width, int height)
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

// compute screen coordinates first
	// from scratchapixal.com
void Camera::gluPerspective(const float& angleOfView, const float& imageAspectRatio, const float& n, const float& f,
	float& b, float& t, float& l, float& r)
{
	float scale = tan(angleOfView * 0.5 * graphics::M_PI / 180) * n;
	r = imageAspectRatio * scale, l = -r;
	t = scale, b = -t;
}

glm::mat4 Camera::glFrustum(const float& b, const float& t, const float& l, const float& r,
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

Camera::Camera(int scr_width, int scr_height)
	:m_scrn_width(scr_height), m_scrn_height(scr_height)
{
	m_angleOfView = 90;
	m_near = 0.1;
	m_far = 100;
	m_imageAspectRatio = m_scrn_width / (float) m_scrn_height;
	m_b = 0;
	m_t = 0;
	m_l = 0;
	m_r = 0;
	// adjusts the variables
	gluPerspective(m_angleOfView, m_imageAspectRatio, m_near, m_far, m_b, m_t, m_l, m_r);
	// calculate the transformation matrixes
	m_view = get_view(m_scrn_width, m_scrn_height);
	m_persp = glFrustum(m_b, m_t, m_l, m_r, m_near, m_far);
	m_worldtocamera = glm::mat4(1.0);
	m_worldtocamera[3][1] = 0;
	m_worldtocamera[3][2] = -30; // camera is 30 unit_z down the positive z axsis;
}

void Camera::camera_coord(glm::vec4 coords)
{
	coords[3] = 1;
	m_worldtocamera[3] = coords;
}

glm::mat4 Camera::get_transmatrix()
{
	return m_view * m_persp * m_worldtocamera;
}
