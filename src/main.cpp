#define TINYOBJLOADER_IMPLEMENTATION
#include <iostream>
#include <string>
#include <cassert>
#include "tiny_obj_loader.h"
#include "graphics.h"
#include "camera.h"
// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

void PrintMatrix(glm::mat4 M, std::string name)
{

	std::cout << "\n";
	std::cout << name;
	std::cout << "\n"; 
	std::cout << M[0][0] <<"\t" << M[1][0] << "\t" << M[2][0] <<"\t" << M[3][0] << "\n" ;
	std::cout << M[0][1] << "\t" << M[1][1] << "\t" << M[2][1] << "\t" << M[3][1] << "\n";
	std::cout << M[0][2] << "\t" << M[1][2] << "\t" << M[2][2] << "\t" << M[3][2] << "\n";
	std::cout << M[0][3] << "\t" << M[1][3] << "\t" << M[2][3] << "\t" << M[3][3] << "\n";
	std::cout << "\n";
}
void PrintVertexs(std::shared_ptr<std::vector<std::shared_ptr<Vertex>>> V)
{

	std::cout << "\n";
	
	for each (auto v in *V)
	{
		
		std::cout << "vertex:\n";
		glm::vec4 vector = v->coord();
		std::cout << float(vector[0])<< "\n";
		std::cout << float(vector[1]) << "\n";
		std::cout << float(vector[2]) << "\n";
		std::cout << float(vector[3]) << "\n";
		std::cout << "\n";
	}
	
}
int main(int argc, char **argv)
{
	bool test_ref{ false };

	//if(test_ref)
	//{
	//	cout << "Usage: A1 meshfile" << endl;
	//	cout << "Starting triangle test..." << endl;
	//	cout << "Outputing to pic_test1.png" << endl;
	//	string filename_test("pic_test1.png");
	//	// Width of image
	//	int width = 512;
	//	// Height of image
	//	int height = 512;
	//	auto image = make_shared<Image>(width, height);
	//	//	generate view matrix
	//	glm::mat4 view{ 0.0 };
	//	view = graphics::get_view(width, height);
	//	// generate perspective matrix
	//	glm::mat4 persp{ 0.0 };
	//	float angleOfView = 90;
	//	float near = 0.1;
	//	float far = 100;
	//	float imageAspectRatio = width / (float)height;
	//	float b, t, l, r;
	//	graphics::gluPerspective(angleOfView, imageAspectRatio, near, far, b, t, l, r);
	//	persp = graphics::glFrustum(b, t, l, r, near, far);
	//	// generate camera matrix
	//	glm::mat4 worldToCamera(1.0);
	//	worldToCamera[3][1] = 0;
	//	worldToCamera[3][2] = -30;
	//	// Create Triangle
	//	Triangle tri("tri");
	//	tri.p_list_vertex[0] = Vertex(glm::vec4(0, 4, 0, 1), glm::vec4(255, 0, 0, 0));
	//	tri.p_list_vertex[1] = Vertex(glm::vec4(4, 0, 0, 1), glm::vec4(0, 255, 0, 0));
	//	tri.p_list_vertex[2] = Vertex(glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 255, 0));
	//	//apply transformations

	//	glm::vec4 result_a = view * persp * worldToCamera * tri.p_list_vertex[0].coord();
	//	glm::vec4 result_b = view * persp * worldToCamera * tri.p_list_vertex[1].coord();
	//	glm::vec4 result_c = view * persp * worldToCamera * tri.p_list_vertex[2].coord();
	//	graphics::draw_line(graphics::per_divide(result_a), graphics::per_divide(result_b), image, 255, 0, 0);
	//	graphics::draw_line(graphics::per_divide(result_b), graphics::per_divide(result_c), image, 0, 255, 0);
	//	graphics::draw_line(graphics::per_divide(result_c), graphics::per_divide(result_a), image, 0, 0, 255);
	//	image->setPixel(graphics::per_divide(result_a).x, graphics::per_divide(result_a).y, 255, 255, 0); // yellow
	//	image->setPixel(graphics::per_divide(result_b).x, graphics::per_divide(result_b).y, 0, 255, 255); // light blue
	//	image->setPixel(graphics::per_divide(result_c).x, graphics::per_divide(result_c).y, 255, 0, 255); // pink
	//	image->writeToFile(filename_test);
	//	return 0;
	//}

	string meshName("../resources/tri.obj");
	// Load geometry
	vector<float> posBuf; // list of vertex positions
	vector<float> norBuf; // list of vertex normals
	vector<float> texBuf; // list of vertex texture coords
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	string errStr;
	bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
	if(!rc) {
		cerr << errStr << endl;
	} else {
		// Some OBJ files have different indices for vertex positions, normals,
		// and texture coordinates. For example, a cube corner vertex may have
		// three different normals. Here, we are going to duplicate all such
		// vertices.
		// Loop over shapes
		for(size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces (polygons)
			size_t index_offset = 0;
			for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				size_t fv = shapes[s].mesh.num_face_vertices[f];
				// Loop over vertices in the face.
				for(size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+0]);
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+1]);
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+2]);
					if(!attrib.normals.empty()) {
						norBuf.push_back(attrib.normals[3*idx.normal_index+0]);
						norBuf.push_back(attrib.normals[3*idx.normal_index+1]);
						norBuf.push_back(attrib.normals[3*idx.normal_index+2]);
					}
					if(!attrib.texcoords.empty()) {
						texBuf.push_back(attrib.texcoords[2*idx.texcoord_index+0]);
						texBuf.push_back(attrib.texcoords[2*idx.texcoord_index+1]);
					}
				}
				index_offset += fv;
				// per-face material (IGNORE)
				shapes[s].mesh.material_ids[f];
			}
		}
	}
	cout << "Number of vertices: " << posBuf.size()/3 << endl;

	// Set Up Camera
	// Width of image
	int width = 1920;
	// Height of image
	int height = 1080;
	auto image = make_shared<Image>(width, height);
	Camera Cam(width, height);
	// for the tri.obj
	Cam.camera_coord(glm::vec4(0, 0, -15, 0));
	// for the sphere.obj
	// Cam.camera_coord(glm::vec4(0, 0, -2, 0));
	// for the teapot.obj
	//Cam.camera_coord(glm::vec4(0, 0, -2, 0));

	// convert posBuff into a vertex buffer
	using  cmplx_ptr_vert = std::shared_ptr<std::vector<std::shared_ptr<Vertex>>>;
	cmplx_ptr_vert vertBuf = graphics::conv_verts(posBuf);

	// apply matrix transformation step by step

	// Apply world to camera transformation matrix
	// PrintVertexs(vertBuf);
	graphics::transbuff(Cam.GetCameraMatrix(), vertBuf);
	PrintMatrix(Cam.GetCameraMatrix(), "Camera");
	//PrintVertexs(vertBuf);
	// Apply perspective transformation matrix
	graphics::transbuff(Cam.GetPerspMatrix(), vertBuf);
	PrintMatrix(Cam.GetPerspMatrix(), "Perspective");
	//PrintVertexs(vertBuf);
	// Apply ortho transformation matrix
	graphics::transbuff(Cam.GetOrthoMatrix(), vertBuf);
	PrintMatrix(Cam.GetOrthoMatrix(), "Ortho");
	//PrintVertexs(vertBuf);
	// Apply view transformation matrix
	graphics::transbuff(Cam.GetViewMatrix(), vertBuf);
	PrintMatrix(Cam.GetViewMatrix(), "View");
	//PrintVertexs(vertBuf);
	// perspective divide the vertexs to get acutaly pixal coordinates
	using  cmplx_ptr_pixal = std::shared_ptr<std::vector<std::shared_ptr<Vertex>>>;
	cmplx_ptr_pixal pixal_buffer = graphics::conv_cart(vertBuf);
	PrintVertexs(pixal_buffer);
	// convert vertex buffer into triangle buffer
	std::shared_ptr<std::vector<std::shared_ptr<Triangle>>> triBuf = graphics::conv_tri(pixal_buffer);

	// draw each triangle in triangle buffer
	graphics::drawtriangles(triBuf, image);
	image->writeToFile("output.png");
	return 0;
}
