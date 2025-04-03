#ifndef FeraTypesMesh_hpp
#define FeraTypesMesh_hpp

#include "Fera/Types/Basic.hpp"

namespace Fera
{
    namespace Types
    {
        class Mesh
        {
            public:
                /**
                 * \brief An Mesh Unit is the smallest data list containing all the floats with the
                 * mesh information, this is usually the result from the construction from the backends
                 * and can be used to Draw 3D directly.
                 */
                struct Unit
                {
                    std::vector<Fera::Types::Basic::F32>    data;
                    Fera::Types::Basic::U32                 faces;
                };

                /**
                 * \brief An Value contains either an Unit or a Group.
                 */
                struct Value
                {
                    /**
                     * \brief The pointer to the dynamically allocated value.
                     */
                    void*                                   value;

                    /**
                     * \brief The definition of a group is.
                     */
                    typedef std::unordered_map<Fera::Types::Basic::String, Fera::Types::Mesh::Value*> Group;

                    /**
                     * \brief The definition of a Unit is.
                     */
                    typedef Fera::Types::Mesh::Unit* Unit;
                    
                    /**
                     * \brief Contains the enumerator for the values.
                     */
                    enum Types
                    {
                        NOTHING         = 0,
                        GROUP,
                        UNIT
                    };
                    
                    /**
                     * \brief The type the value is currently.
                     */
                    Fera::Types::Mesh::Value::Types         type = Fera::Types::Mesh::Value::Types::NOTHING;
                };

                /**
                 * \brief It is the root of the mesh itself.
                 */
                Fera::Types::Mesh::Value* root;
                Mesh();
                ~Mesh();
                
                /**
                 * \brief Gets an value from an split result.
                 * \note THIS IS USED BY GET(CH8*) and GET(STRING&)!
                 */
                Fera::Types::Mesh::Value* Get(const Logica::Texting::SplitResult& result);
                
                /**
                 * \brief Gets an value from the Key.
                 */
                Fera::Types::Mesh::Value* Get(const Fera::Types::Basic::CH8* key);
                Fera::Types::Mesh::Value* Get(const Fera::Types::Basic::String& key);
            };
    };
};

#endif