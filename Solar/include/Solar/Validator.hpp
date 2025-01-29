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

            /// @brief In case the requested unit to load something is not found.
            WarehouseInvalidRenderingUnit,

            /// @brief For when the Load::Datafile function has found no file.
            WarehouseLoadDataFileNoFile,

            /// @brief For when the Load::DataFile found an error on the Sojson parsing stage.
            WarehouseLoadDataFileSojsonSyntaxError,

            /// @brief Accounts for many errors on the shader files like missing sections or data.
            WarehouseMalformedShaderFile,

            /// @brief Failed to compile shader.
            WarehouseFailedCompileShader,

            /// @brief In case your mesh file is not valid or is missing something.
            WarehouseInvalidMeshRecipe,

            /// @brief The mesh file not found.
            WarehouseMeshFileNotFound,

            /// @brief The mesh file is not a valid OBJ file.
            WarehouseMeshInvalidOBJ,

            /// @brief Some syntax error with the OBJ (anything that Fera got stuck).
            WarehouseMeshBadOBJFile,

            /// @brief When a mesh is not found (Surf function).
            WarehouseMeshNotFound,

            /// @brief For impossible errors.
            Unknown = UINT8_MAX
        };
    };
};

#endif