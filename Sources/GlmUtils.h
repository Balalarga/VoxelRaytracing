#pragma once

#include <glm/glm.hpp>
#include <iostream>



inline std::ostream& operator<<(std::ostream& stream, const glm::vec3& vec)
{
    stream << "(" << vec.x << ", "<< vec.y << ", " << vec.z << ")";
    return stream;
}

inline std::ostream& operator<<(std::ostream& stream, const glm::vec2& vec)
{
    stream << "(" << vec.x << ", "<< vec.y << ")";
    return stream;
}