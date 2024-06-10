#ifndef solar_math_vector2_hxx
#define solar_math_vector2_hxx

#include "Solar/Types.hxx"
#include <glm/vec2.hpp>

namespace Solar
{
    namespace Math
    {
        namespace Vector2
        {
            template <typename VectorType> struct BaseVector2
            {
                VectorType x;
                VectorType y;
                glm::vec2 ToGLM()
                {
                    glm::vec3 __result = {(float)this->x, (float)this->y};
                    return __result;
                }
            };
            typedef BaseVector2<Solar::Types::U8>   U8; typedef BaseVector2<Solar::Types::I8> I8;
            typedef BaseVector2<Solar::Types::U16> U16; typedef BaseVector2<Solar::Types::I16> I16;
            typedef BaseVector2<Solar::Types::U32> U32; typedef BaseVector2<Solar::Types::I32> I32;
            typedef BaseVector2<Solar::Types::U64> U64; typedef BaseVector2<Solar::Types::I64> I64;
            typedef BaseVector2<Solar::Types::D32> D32; typedef BaseVector2<Solar::Types::D64> D64;
        }
    };
};

#endif
// Solar/Math/Vector2.hxx: