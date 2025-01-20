#ifndef SolarValidator_hpp
#define SolarValidator_hpp

namespace Solar
{
    /// @brief All the validator errors.
    namespace ValidatorCodes
    {
        enum ValidatorCodes
        {
            /// @brief When there is no error.
            Ok = 0,

            /// @brief For impossible errors.
            Unknown = UINT8_MAX
        };
    };
};

#endif