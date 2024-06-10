#ifndef solar_math_color3_hxx
#define solar_math_color3_hxx

#include "Solar/Types.hxx"

namespace Solar
{
    namespace Math
    {
        struct Color4
        {
            Solar::Types::U8 r = 0;
            Solar::Types::U8 g = 0;
            Solar::Types::U8 b = 0;
            Solar::Types::U8 a = 0;
            Solar::Types::U32 ConvertToRGBA() { return (Solar::Types::U32)( (this->r << 24) | (this->g << 16) | (this->b << 8) | this->a ); };
        };
    };
};

#endif
// Solar/Math/Color3.hxx