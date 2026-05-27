#include "krxpch.h"
#include "Math.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

namespace Krux {

    namespace Math {

        bool DecomposeTransform(const glm::mat4 transform, glm::vec3& outTranslation, glm::vec3& outRotation, glm::vec3& outScale)
        {
            outTranslation = glm::vec3(transform[3]);

            outScale.x = glm::length(glm::vec3(transform[0]));
            outScale.y = glm::length(glm::vec3(transform[1]));
            outScale.z = glm::length(glm::vec3(transform[2]));

            if (outScale.x < 0.0001f || outScale.y < 0.0001f || outScale.z < 0.0001f)
                return false;

            glm::mat3 rotMatrix;
            rotMatrix[0] = glm::vec3(transform[0]) / outScale.x;
            rotMatrix[1] = glm::vec3(transform[1]) / outScale.y;
            rotMatrix[2] = glm::vec3(transform[2]) / outScale.z;

            glm::quat orientation = glm::quat_cast(rotMatrix);
            outRotation = glm::degrees(glm::eulerAngles(orientation));

            return true;
        }
    }
}