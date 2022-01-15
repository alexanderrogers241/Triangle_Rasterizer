#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include <glm/glm.hpp>
class Camera
{
private:
	// output image settings
	int m_scrn_width;
	int m_scrn_height;
	// render volume settings
	float m_angleOfView;
	float m_near;
	float m_far;
	float m_imageAspectRatio;
	float m_b;
	float m_t;
	float m_l;
	float m_r;
	// matrixes for transformations
	glm::mat4 m_view;
	glm::mat4 m_persp;
	glm::mat4 m_worldtocamera;
	glm::mat4 p_transmatrix;
	glm::mat4 get_view(int width, int height);
	// compute screen coordinates first
	// from scratchapixal.com
	void gluPerspective(const float& angleOfView, const float& imageAspectRatio, const float& n, const float& f,
		float& b, float& t, float& l, float& r);
	// from scratchapixal.com
	glm::mat4 glFrustum(const float& b, const float& t, const float& l, const float& r,
		const float& n, const float& f);
public:
	Camera(int scr_width, int scr_height);
	~Camera() = default;
	// access functions;
	void camera_coord(glm::vec4 coords);
	// functions
	glm::mat4 get_transmatrix();

};
#endif