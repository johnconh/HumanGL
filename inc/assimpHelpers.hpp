#pragma once

#include "../libs/include/assimp/quaternion.h"
#include "../libs/include/assimp/vector3.h"
#include "../libs/include/assimp/matrix4x4.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "quaternion.hpp"

class AssimpHelpers
{
    public:
        static inline Matrix4 ConvertMatrixToGLMFormat(const aiMatrix4x4& from)
        {
            std::array<float, 16> data = {
                from.a1, from.b1, from.c1, from.d1,
                from.a2, from.b2, from.c2, from.d2,
                from.a3, from.b3, from.c3, from.d3,
                from.a4, from.b4, from.c4, from.d4
            };
            return Matrix4(data);
        }
        static inline Vec3 GetGLMVec(const aiVector3D& from)
        {
            return Vec3(from.x, from.y, from.z);
        }
        static inline Quaternion GetGLMQuat(const aiQuaternion& from)
        {
            return Quaternion(from.w, from.x, from.y, from.z);
        }
};