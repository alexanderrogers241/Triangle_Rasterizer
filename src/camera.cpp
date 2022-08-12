#include "camera.h"
#include "graphics.h"


glm::mat4 Camera::GenViewMatrix(int width, int height)
{
	//	generate view matrix
	glm::mat4 view{ 0.0 };
	// columns indexed before rows
	view[0][0] = width / 2;
	view[0][1] = 0;
	view[0][2] = 0;
	view[0][3] = 0;

	view[1][0] = 0;
	view[1][1] = height / 2;
	view[1][2] = 0;
	view[1][3] = 0;

	view[2][0] = 0;
	view[2][1] = 0;
	view[2][2] = 1;
	view[2][3] = 0;

	view[3][0] = (width-1)/2;
	view[3][1] = (height-1)/2;
	view[3][2] = 0;
	view[3][3] = 1;
	return view;
}

// compute screen coordinates first
	// from scratchapixal.com https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/opengl-perspective-projection-matrix
void Camera::gluPerspective(const float & VertAngleOfView, const float& imageAspectRatio, const float& n,
 const float& f,
	float& b, float& t, float& l, float& r)
{
	float scale = tan(VertAngleOfView * 0.5 * graphics::M_PI / 180) * n;
	r = imageAspectRatio * scale;
	l = -r;
	t = scale;
	b = -scale;
}

glm::mat4 Camera::glFrustum(const float& b, const float& t, const float& l, const float& r,
	const float& n, const float& f)
{
	glm::mat4 M{ 0.0 };
	// Column Major order
	// set OpenGL perspective projection matrix pg. 155 fundamentals of computer graphics
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
	M[3][2] = -(2 * f * n )/ (f - n);
	M[3][3] = 0;
	return M;
}

glm::mat4 Camera::GenOrthoMat(const float& b, const float& t, const float& l, const float& r, const float& n, const float& f)
{
	glm::mat4 M{ 0.0 };
	// Column Major order
	// Set Orthographics to cannoncal transformation matrix pg. 145 Fundamentals Of Computer Graphics
	// Camera facing down the negative z axis so n > f and f tends to be a larger negative number

	M[0][0] = 2/(r-l);
	M[0][1] = 0;
	M[0][2] = 0;
	M[0][3] = 0;

	M[1][0] = 0;
	M[1][1] = 2/(t-b);
	M[1][2] = 0;
	M[1][3] = 0;

	M[2][0] = 0;
	M[2][1] = 0;
	M[2][2] = 2/(n-f);
	M[2][3] = 0;

	M[3][0] = (-1)*(r+l)/(r-l);
	M[3][1] = (-1)*(t+b)/(t-b);
	M[3][2] = (-1)*(n+f)/(n-f);
	M[3][3] = 1;
	return M;
}

glm::mat4 Camera::GenPerMat(const float& n, const float& f)
{
	glm::mat4 M{ 0.0 };
	// Column Major order
	// Set basis ( frustum) to orthographic view volume ( rectangle)transformation matrix pg. 154 Fundamentals Of Computer Graphics
	// Camera facing down the negative z axis so n > f and f tends to be a larger negative number

	M[0][0] = n;
	M[0][1] = 0;
	M[0][2] = 0;
	M[0][3] = 0;

	M[1][0] = 0;
	M[1][1] = n;
	M[1][2] = 0;
	M[1][3] = 0;

	M[2][0] = 0;
	M[2][1] = 0;
	M[2][2] = n + f;
	M[2][3] = 1;

	M[3][0] = 0;
	M[3][1] = 0;
	M[3][2] = -(f*n);
	M[3][3] = 0;
	return M;
}

glm::mat4 Camera::GenCameraMat(const glm::vec4 location)
{
	glm::mat4 M1{ 0.0 };
	glm::mat4 M2{ 0.0 };
	// Column Major order
	// Set World(cannocal) to camera (basis) transformation matrix pg. 147 Fundamentals Of Computer Graphics
	// Camera facing down the negative z axis.


	// orthogonoal basis vectors for camera orientation
	M1[0][0] = 1;
	M1[0][1] = 0;
	M1[0][2] = 0;
	M1[0][3] = 0;

	M1[1][0] = 0;
	M1[1][1] = 1;
	M1[1][2] = 0;
	M1[1][3] = 0;

	M1[2][0] = 0;
	M1[2][1] = 0;
	M1[2][2] = 1;
	M1[2][3] = 0;

	M1[3][0] = 0;
	M1[3][1] = 0;
	M1[3][2] = 0;
	M1[3][3] = 1;

	// basis origin from world origin
	// placing camera at 10 positive z. facing down the -z axis
	M2[0][0] = 1;
	M2[0][1] = 0;
	M2[0][2] = 0;
	M2[0][3] = 0;

	M2[1][0] = 0;
	M2[1][1] = 1;
	M2[1][2] = 0;
	M2[1][3] = 0;

	M2[2][0] = 0;
	M2[2][1] = 0;
	M2[2][2] = 1;
	M2[2][3] = 0;

	M2[3][0] = -location[0];
	M2[3][1] = -location[1];
	M2[3][2] = -location[2];
	M2[3][3] = 1; 
	// want to place it at positive 10 z. Matrix actually negates this and transforms vertex -10 z units down the line of sight of the camera.

	return M1*M2;
}

Camera::Camera(int scr_width, int scr_height)
	:m_scrn_width_(scr_width), m_scrn_height_(scr_height)
{	
	
	// places the camera 10 z units in front of the origin
	camera_location_=glm::vec4(0, 0, 10, 0);
	m_worldtocamera_ = GenCameraMat(camera_location_);
	m_angleOfView_ = 90;
	//m_near = 14.9; // important remaps each time camera moves
	//m_far = -20;// important camera facing down the negative z axsis
	m_near_ = camera_location_.z;
	//negative number moved down field of view
	m_far_ = camera_location_.z - 20;
	m_imageAspectRatio_ = (float) m_scrn_width_ / (float) m_scrn_height_;
	m_b_ = 0;
	m_t_ = 0;
	m_l_ = 0;
	m_r_ = 0;
	// adjusts the variables
	gluPerspective(m_angleOfView_, m_imageAspectRatio_, m_near_, m_far_, m_b_, m_t_, m_l_, m_r_);
	// calculate the transformation matrixes
	m_view_ = GenViewMatrix(m_scrn_width_, m_scrn_height_);
	m_persp_ = GenPerMat(m_near_, m_far_);
	m_ortho_ = GenOrthoMat(m_b_, m_t_, m_l_, m_r_, m_near_, m_far_);
	
}

void Camera::camera_coord(glm::vec4 coords)
{

	camera_location_ = coords;
	m_worldtocamera_ = GenCameraMat(camera_location_);
	m_near_ = camera_location_.z;
	//negative number moved down field of view
	m_far_ = camera_location_.z - 0.005;
	m_imageAspectRatio_ = (float)m_scrn_width_ / (float)m_scrn_height_;
	m_b_ = 0;
	m_t_ = 0;
	m_l_ = 0;
	m_r_ = 0;
	// adjusts the variables
	gluPerspective(m_angleOfView_, m_imageAspectRatio_, m_near_, m_far_, m_b_, m_t_, m_l_, m_r_);
	// calculate the transformation matrixes
	m_view_ = GenViewMatrix(m_scrn_width_, m_scrn_height_);
	m_persp_ = GenPerMat(m_near_, m_far_);
	m_ortho_ = GenOrthoMat(m_b_, m_t_, m_l_, m_r_, m_near_, m_far_);
	
}

glm::mat4 Camera::GetAllMatrixs()
{
	return m_view_*m_ortho_*m_persp_*m_worldtocamera_;
}

glm::mat4 Camera::GetViewMatrix()
{
	return m_view_;
}

glm::mat4 Camera::GetOrthoMatrix()
{
	return m_ortho_;
}

glm::mat4 Camera::GetPerspMatrix()
{
	return m_persp_;
}

glm::mat4 Camera::GetCameraMatrix()
{
	return m_worldtocamera_;
}
