#ifndef solar_math_vector3_hxx
#define solar_math_vector3_hxx

#include "Solar/Types.hxx"
#include <glm/vec3.hpp>

namespace Solar
{
    namespace Math
    {
        namespace Vector3
        {
            template <typename VectorType> struct BaseVector3
            {
                VectorType x;
                VectorType y;
                VectorType z;
                glm::vec3 ToGLM() {
                    glm::vec3 __result = {(float)this->x, (float)this->y, (float)this->z};
                    return __result;
                }
            };
            typedef BaseVector3<Solar::Types::U8>   U8; typedef BaseVector3<Solar::Types::I8> I8;
            typedef BaseVector3<Solar::Types::U16> U16; typedef BaseVector3<Solar::Types::I16> I16;
            typedef BaseVector3<Solar::Types::U32> U32; typedef BaseVector3<Solar::Types::I32> I32;
            typedef BaseVector3<Solar::Types::U64> U64; typedef BaseVector3<Solar::Types::I64> I64;
            typedef BaseVector3<Solar::Types::D32> D32; typedef BaseVector3<Solar::Types::D64> D64;
        }
    };
};

#endif
// Solar/Math/Vector3.hxx: