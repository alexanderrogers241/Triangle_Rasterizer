#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include <glm/glm.hpp>
#include <iostream>
class Camera
{
private:
	// output image settings
	int m_scrn_width_;
	int m_scrn_height_;
	// render volume settings
	float m_angleOfView_;
	float m_near_;
	float m_far_;
	float m_imageAspectRatio_;
	float m_b_;
	float m_t_;
	float m_l_;
	float m_r_;
	// matrixes for transformations
	glm::mat4 m_view_;
	glm::mat4 m_persp_;
	glm::mat4 m_ortho_;
	glm::mat4 m_worldtocamera_;
	// Camera parameters
	glm::vec4 camera_location_;

	glm::mat4 GenViewMatrix(int width, int height);
	// compute screen coordinates first
	// from scratchapixal.com
	void gluPerspective(const float & VertAngleOfView, const float& imageAspectRatio, const float& n, const float& f,
		float& b, float& t, float& l, float& r);
	// from scratchapixal.com
	glm::mat4 glFrustum(const float& b, const float& t, const float& l, const float& r,
		const float& n, const float& f);
	// from FOCG
	glm::mat4 GenOrthoMat(const float& b, const float& t, const float& l, const float& r,
		const float& n, const float& f);
	// from FOCG
	glm::mat4 GenPerMat(const float& n, const float& f);
	// from FOCG
	glm::mat4 GenCameraMat(const glm::vec4 location);
	

public:
	Camera(int scr_width, int scr_height);
	~Camera() = default;
	// access functions;
	void camera_coord(glm::vec4 coords);
	// functions
	glm::mat4 GetAllMatrixs();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetOrthoMatrix();
	glm::mat4 GetPerspMatrix();
	glm::mat4 GetCameraMatrix();
};
#endif
