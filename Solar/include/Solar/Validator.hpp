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

            /// @brief When an invalid site is inserted.
            WarehouseInvalidSite,

            /// @brief For when the Load::Datafile function has found no file.
            WarehouseLoadDataFileNoFile,

            /// @brief For when the Load::DataFile found an error on the Sojson parsing stage.
            WarehouseLoadDataFileSojsonSyntaxError,

            /// @brief For impossible errors.
            Unknown = UINT8_MAX
        };
    };
};

#endif