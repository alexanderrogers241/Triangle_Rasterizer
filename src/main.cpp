#define TINYOBJLOADER_IMPLEMENTATION
#include <iostream>
#include <string>
#include <cassert>
#include "glm/glm.hpp"
#include "tiny_obj_loader.h"
#include "Image.h"
#include "Triangle.h"
#include "Shape_base.h"
#include "Vertex.h"
#include "graphics.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;


double RANDOM_COLORS[7][3] = {
	{0.0000,    0.4470,    0.7410},
	{0.8500,    0.3250,    0.0980},
	{0.9290,    0.6940,    0.1250},
	{0.4940,    0.1840,    0.5560},
	{0.4660,    0.6740,    0.1880},
	{0.3010,    0.7450,    0.9330},
	{0.6350,    0.0780,    0.1840},
};

int main(int argc, char **argv)
{
	//if(argc < 2) {
	//	cout << "Usage: A1 meshfile" << endl;
	//	return 0;
	//}
	//string meshName(argv[1]);

	//// Load geometry
	//vector<float> posBuf; // list of vertex positions
	//vector<float> norBuf; // list of vertex normals
	//vector<float> texBuf; // list of vertex texture coords
	//tinyobj::attrib_t attrib;
	//std::vector<tinyobj::shape_t> shapes;
	//std::vector<tinyobj::material_t> materials;
	//string errStr;
	//bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
	//if(!rc) {
	//	cerr << errStr << endl;
	//} else {
	//	// Some OBJ files have different indices for vertex positions, normals,
	//	// and texture coordinates. For example, a cube corner vertex may have
	//	// three different normals. Here, we are going to duplicate all such
	//	// vertices.
	//	// Loop over shapes
	//	for(size_t s = 0; s < shapes.size(); s++) {
	//		// Loop over faces (polygons)
	//		size_t index_offset = 0;
	//		for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
	//			size_t fv = shapes[s].mesh.num_face_vertices[f];
	//			// Loop over vertices in the face.
	//			for(size_t v = 0; v < fv; v++) {
	//				// access to vertex
	//				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
	//				posBuf.push_back(attrib.vertices[3*idx.vertex_index+0]);
	//				posBuf.push_back(attrib.vertices[3*idx.vertex_index+1]);
	//				posBuf.push_back(attrib.vertices[3*idx.vertex_index+2]);
	//				if(!attrib.normals.empty()) {
	//					norBuf.push_back(attrib.normals[3*idx.normal_index+0]);
	//					norBuf.push_back(attrib.normals[3*idx.normal_index+1]);
	//					norBuf.push_back(attrib.normals[3*idx.normal_index+2]);
	//				}
	//				if(!attrib.texcoords.empty()) {
	//					texBuf.push_back(attrib.texcoords[2*idx.texcoord_index+0]);
	//					texBuf.push_back(attrib.texcoords[2*idx.texcoord_index+1]);
	//				}
	//			}
	//			index_offset += fv;
	//			// per-face material (IGNORE)
	//			shapes[s].mesh.material_ids[f];
	//		}
	//	}
	//}
	//cout << "Number of vertices: " << posBuf.size()/3 << endl;
	// string filename(argv[1]);
	string filename("pic_test1.png");
	// Width of image
	int width = 512;
	// Height of image
	int height = 512;
	auto image = make_shared<Image>(width, height);
	//	generate view matrix
	glm::mat4 view{ 0.0 };
	view = graphics::get_view(width, height);
	// generate perspective matrix
	glm::mat4 persp{ 0.0 };
	float angleOfView = 90;
	float near = 0.1;
	float far = 100;
	float imageAspectRatio = width / (float)height;
	float b, t, l, r;
	graphics::gluPerspective(angleOfView, imageAspectRatio, near, far, b, t, l, r);
	persp = graphics::glFrustum(b, t, l, r, near, far);
	// generate camera matrix
	glm::mat4 worldToCamera(1.0);
	worldToCamera[3][1] = 0;
	worldToCamera[3][2] = -30;
	// Create Triangle
	Triangle tri("tri");
	tri.p_list_vertex[0] = Vertex(glm::vec4(0, 4, 0, 1), glm::vec4(255, 0, 0, 0));
	tri.p_list_vertex[1] = Vertex(glm::vec4(4, 0, 0, 1), glm::vec4(0, 255, 0, 0));
	tri.p_list_vertex[2] = Vertex(glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 255, 0));
	//apply transformations
	
	glm::vec4 result_a = view * persp * worldToCamera * tri.p_list_vertex[0].coord();
	glm::vec4 result_b = view * persp * worldToCamera * tri.p_list_vertex[1].coord();
	glm::vec4 result_c = view * persp * worldToCamera * tri.p_list_vertex[2].coord();
	graphics::draw_line(graphics::per_divide(result_a), graphics::per_divide( result_b), image, 255, 0 ,0 );
	graphics::draw_line(graphics::per_divide(result_b), graphics::per_divide( result_c), image, 0, 255, 0);
	graphics::draw_line(graphics::per_divide(result_c), graphics::per_divide( result_a), image, 0, 0, 255);
	image->setPixel(graphics::per_divide(result_a).x, graphics::per_divide(result_a).y, 255, 255, 0); // yellow
	image->setPixel(graphics::per_divide(result_b).x, graphics::per_divide(result_b).y, 0, 255, 255); // light blue
	image->setPixel(graphics::per_divide(result_c).x, graphics::per_divide(result_c).y, 255, 0, 255); // pink
	image->writeToFile(filename);
	return 0;
}
