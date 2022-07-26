#pragma once
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "Image.h"
#include "Vertex.h"
#include "Triangle.h"
class Triangle;
namespace graphics
{
    namespace
    {
        bool comp_x(const glm::vec3& a, const glm::vec3& b);

        bool comp_y(const glm::vec3& a, const glm::vec3& b);
    }
    // constants
    const float M_PI{ 3.14159 };

    const double RANDOM_COLORS[10][3] = {
        {0.0000,    0.4470,    0.7410},
        {0.8500,    0.3250,    0.0980},
        {0.9290,    0.6940,    0.1250},
        {0.4940,    0.1840,    0.5560},
        {0.4660,    0.6740,    0.1880},
        {0.3010,    0.7450,    0.9330},
        {0.2000,    0.0780,    0.1840},
        {0.6350,    0.2000,    0.1840},
        {0.6350,    0.0780,    0.4000},
        {0.7000,    0.8000,    0.0050},
    };
    void draw_line(glm::vec3 point_A, glm::vec3 point_B, std::shared_ptr<Image> Image, unsigned char r, unsigned char g, unsigned char b);

    void gluPerspective(const float& angleOfView, const float& imageAspectRatio, const float& n, const float& f,
        float& b, float& t, float& l, float& r);

    glm::mat4 glFrustum(const float& b, const float& t, const float& l, const float& r,
        const float& n, const float& f);

    glm::mat4 get_view(int width, int height);

    glm::vec4 per_divide(glm::vec4& input);

    //modified from https://github.com/Maxrod98/CSCE441-A1/
    std::shared_ptr<std::vector<std::shared_ptr<Vertex>>> conv_verts(std::vector<float>& buff);

    std::shared_ptr<std::vector<std::shared_ptr<Vertex>>> conv_cart(std::shared_ptr<std::vector<std::shared_ptr<Vertex>>> vertBuf);

    std::shared_ptr<std::vector<std::shared_ptr<Triangle>>> conv_tri(std::shared_ptr<std::vector<std::shared_ptr<Vertex>>> vertBuf);

    void transbuff(glm::mat4& M, std::shared_ptr<std::vector<std::shared_ptr<Vertex>>> vert_buff);

    void drawtrianglesbox(std::shared_ptr<std::vector<std::shared_ptr<Triangle>>> buff, std::shared_ptr<Image> Image);
    void drawtriangles(std::shared_ptr<std::vector<std::shared_ptr<Triangle>>> buff, std::shared_ptr<Image> Image);

    void scaleandtranslate(std::shared_ptr<std::vector<std::shared_ptr<Vertex>>> desiredWidth, std::shared_ptr<Image> desiredHeight);
}
#endif
