#pragma once
#ifndef _SHAPEBASE_H_
#define _SHAPEBASE_H_
#include <string>
#include <memory>
#include <vector>
#include "Vertex.h"
class Shape_base // This Shape_base is an abstract base class
{
protected:
    std::string m_name;
    int m_number_vertex;
    
public:

    Shape_base(const std::string name, const int numvert)
        : m_name { name }, m_number_vertex { numvert}   {}
    
    const std::string getName() { return m_name; }
    virtual const int example() const = 0; // The = 0 means this function is pure virtual
    virtual ~Shape_base() = default;
};

#endif