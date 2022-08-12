#pragma once
#ifndef _ZBUFFER_H_
#define _ZBUFFER_H_
#include <vector>
class ZBuffer
{
private:
	int image_height_;
	int image_width_;
	std::vector<float> z_buff_;
public:
	ZBuffer(int width, int height);
	bool Check(int x, int y, float z);
};
#endif
