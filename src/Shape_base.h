#pragma once
#ifndef _SHAPEBASE_H_
#define _SHAPEBASE_H_

#include <string>
#include <vector>
class Shape_base // This Shape_base is an abstract base class
{
protected:
    std::string m_name;
    
public:

    Shape_base(const std::string name)
        : m_name { name }   {}

    Shape_base() = default;
    const std::string getName() { return m_name; }
    virtual const int example() const = 0; // The = 0 means this function is pure virtual
    virtual ~Shape_base() = default;
};

#endif