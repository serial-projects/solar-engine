#ifndef FeraBackendsOBJDecode_hpp
#define FeraBackendsOBJDecode_hpp

#include "Logica/Logica.hpp"

#include "Fera/Types.hpp"
#include "Fera/Backends/OBJ/Globals.hpp"

namespace Fera
{
    namespace Backends
    {
        namespace OBJ
        {
            /**
             * How does Decode and the Fera's OBJ Backend Functions?
             * It is rather simple actually, the OBJ is perfect for Solar Engine with the reason that
             *  1-) It doesn't have any fancy parsing;
             *  2-) It is barebones.
             * 
             * Solar Engine in Models does NOT care for animation or any material property, what
             * the engine looks for is the RAW float point mesh data, meaning the MESH itself is
             * what we look for, in this way, the Fera OBJ Backend has the certain specifications:
             *  1-) It uses 'G' for the group and 'O' for the object in the way that:
             *      'G' contains 'O's, those 'O's are units, the most basic state of any group.
             *      So, take an example of a OBJ file, an Cube, there can have: 
             *          g Cube
             *          o LeftSide
             *          ...
             *          o RightSide
             *          ...
             *      We can reference a side of the cube using the key: 'Cube.LeftSide' for example,
             *      on the mesh, use: mesh->Get("Cube.LeftSide"), it will return the Value for the
             *      LeftSide, or express: mesh->Extract("Cube.LeftSide"), it will return the series
             *      of floats that builds the mesh.
             *      
             *      This also allows for: 'Cube.*', in this very case, all the Groups and Objects
             *      are returned in a single series of floats using mesh->Extract("Cube.*"), this
             *      and mesh->Extract("Cube") are interchangeable.
             * 2-) MTL are completely ignored.
             * 3-) We only accept F/V/VN/VT and several basic opcodes.
             */
            class Decode
            {
                public:
                    Decode();
                    ~Decode();

                    /**
                     * \brief The decoder needs an buffer to decode the OBJ raw file, this is done
                     * by setting using this function.
                     */
                    void SetBuffer(Logica::Types::Stream::Buffer* buffer);

                    /**
                     * \brief Returns the constructed mesh.
                     */
                    Fera::Types::Mesh* GetMesh();

                    /**
                     * \brief Enumerates all the states the OBJ decoder can be.
                     */
                    enum States
                    {
                        /**
                         * \brief When the state was not initialized/buffer not set.
                         */
                        NOTHING             = 0,

                        /**
                         * \brief The state the decoder is when parsing content.
                         */
                        RUNNING,

                        /** 
                         * \brief The state the decoder is when finished without any problems.
                         */
                        FINISHED,

                        /**
                         * \brief The state the decoder is when finished with problems.
                         */
                        DIED
                    };
                    
                    /**
                     * \brief The current state the decode is found on.
                     */
                    Fera::Backends::OBJ::Decode::States state =
                        Fera::Backends::OBJ::Decode::States::NOTHING;
                private:
                    /** Tokenizer:  */
                    Logica::Texting::Tokenizer::Rules       tokenizer_rules;
                    Logica::Texting::Tokenizer::Instance    tokenizer;
                    
                    /** Internals of the machine: */
                    Fera::Backends::OBJ::Globals            globals;
                    Fera::Types::Mesh*                      building_mesh;
                    Fera::Types::Basic::String              current_group;
                    Fera::Types::Basic::String              current_object;
            };
        };
    };
};

#endif