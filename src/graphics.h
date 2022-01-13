#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "Image.h"

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

namespace graphics
{
    namespace 
    {
        bool comp_x(const glm::vec4& a, const glm::vec4& b);

        bool comp_y(const glm::vec4& a, const glm::vec4& b);
    }
    // constants
    const float M_PI{ 3.14159 };

    void draw_line(glm::vec4 point_A, glm::vec4 point_B, std::shared_ptr<Image> Image, unsigned char r, unsigned char g, unsigned char b);
    
    void gluPerspective(const float& angleOfView, const float& imageAspectRatio, const float& n, const float& f,
        float& b, float& t, float& l, float& r);

    glm::mat4 glFrustum(const float& b, const float& t, const float& l, const float& r,
        const float& n, const float& f);
    
    glm::mat4 make_view(int width, int height);

}


#endif