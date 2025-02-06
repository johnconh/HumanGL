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
        static inline Matrix4 ConvertMatrixToMatrix4Format(const aiMatrix4x4& from) {
            Matrix4 to;
            to[0] = from.a1; to[4] = from.a2; to[8] = from.a3; to[12] = from.a4;
            to[1] = from.b1; to[5] = from.b2; to[9] = from.b3; to[13] = from.b4;
            to[2] = from.c1; to[6] = from.c2; to[10] = from.c3; to[14] = from.c4;
            to[3] = from.d1; to[7] = from.d2; to[11] = from.d3; to[15] = from.d4;
            return to;
        }

        static inline glm::vec3 GetGLMVec(const aiVector3D& from)
        {
            return glm::vec3(from.x, from.y, from.z);
        }

        static inline Vec3 GetVec3(const aiVector3D& from)
        {
            return Vec3(from.x, from.y, from.z);
        }

        static inline glm::quat GetGLMQuat(const aiQuaternion& from)
        {
            return glm::quat(from.w, from.x, from.y, from.z);
        }
};