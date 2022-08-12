#include "ZBuffer.h"

ZBuffer::ZBuffer(int width, int height):
image_height_(height),
image_width_(width),
z_buff_(height*width,-3.4E38)
{
}

bool ZBuffer::Check(int x, int y, float z)
{

    // First check for bounds
    if (y < 0 || y >= image_height_) {
        //cout << "Row " << y << " is out of bounds" << endl;
        return false;
    }
    if (x < 0 || x >= image_width_) {
        //cout << "Col " << x << " is out of bounds" << endl;
        return false;
    }
    //hardcoded needs to be fix
    y = 1080 - y - 1;
    int index = (y*image_width_)+x;
    if (z > z_buff_[index]) {
        //replace
        z_buff_[index] = z;
        //return
        return true;
    }
    else {
        return false;
    }
}
